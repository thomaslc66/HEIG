/*
 *
 * ----- SO3 Smart Object Oriented (SOO) Operating System -----
 *
 * Copyright (c) 2016,2017 Sootech SA, Switzerland
 * Copyright (c) 2014, 2015, 2016, 2017 REDS Institute, HEIG-VD, Switzerland
 * 
 * This software is released under the MIT License whose terms are defined hereafter.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), 
 * to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR 
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Contributors:
 *
 * - 2014: Romain Bornet
 *
 * Standard string manipulation functions defined in standard strings.h header
 * All implementations based on http://clc-wiki.net/wiki/C_standard_library:string.h
 *
 */

#include <stddef.h>     /* size_t */
#include <ctype.h>

void uppercase(char *str, int len)
{
	int i;

	for (i = 0; i < len; i++) {
		*str = toupper(*str);
		str++;
	}
}

/*
 * Convert a string to lowercase.
 */
void downcase(char *str)
{
	while (*str != '\0') {
		*str = tolower(*str);
		str++;
	}
}

/* http://clc-wiki.net/wiki/memchr#Implementation */
void *memchr(const void *s, int c, size_t n)
{
    unsigned char *p = (unsigned char*)s;
    while( n-- )
        if( *p != (unsigned char)c )
            p++;
        else
            return p;
    return 0;
}

/* http://clc-wiki.net/wiki/memcmp#Implementation */
int memcmp(const void* s1, const void* s2,size_t n)
{
    const unsigned char *p1 = s1, *p2 = s2;
    while(n--)
        if( *p1 != *p2 )
            return *p1 - *p2;
        else
            p1++,p2++;
    return 0;
}

/* http://clc-wiki.net/wiki/memcpy#Implementation */
void *memcpy(void *dest, const void *src, size_t n)
{
    char *dp = dest;
    const char *sp = src;
    while (n--)
        *dp++ = *sp++;
    return dest;
}

/* http://clc-wiki.net/wiki/memmove#Implementation
 * using naive and non-portable '__np_anyptrlt' macro: see website for info */
#define __np_anyptrlt(p1, p2) ((p1) < (p2))

void *memmove(void *dest, const void *src, size_t n)
{
    unsigned char *pd = dest;
    const unsigned char *ps = src;
    if (__np_anyptrlt(ps, pd))
        for (pd += n, ps += n; n--;)
            *--pd = *--ps;
    else
        while(n--)
            *pd++ = *ps++;
    return dest;
}

/* http://clc-wiki.net/wiki/memset#Implementation */
void *memset(void *s, int c, size_t n)
{
    unsigned char* p=s;
    while(n--)
        *p++ = (unsigned char)c;
    return s;
}

/* http://clc-wiki.net/wiki/strchr#Implementation */
char *strchr(const char *s, int c)
{
    while (*s != (char)c)
        if (!*s++)
            return 0;
    return (char *)s;    
}

/* http://clc-wiki.net/wiki/strcmp#Implementation */
int strcmp(const char* s1, const char* s2)
{
    while(*s1 && (*s1==*s2))
        s1++,s2++;
    return *(const unsigned char*)s1-*(const unsigned char*)s2;
}

/**
 * strncmp - Compare two length-limited strings
 * @cs: One string
 * @ct: Another string
 * @count: The maximum number of bytes to compare
 */
int strncmp(const char * cs,const char * ct,size_t count)
{
        register signed char __res = 0;

        while (count) {
                if ((__res = *cs - *ct++) != 0 || !*cs++)
                        break;
                count--;
        }

        return __res;
}


/* http://clc-wiki.net/wiki/strcpy#Implementation */
char *strcpy(char *dest, const char* src)
{
    char *ret = dest;
    while ((*dest++ = *src++))
        ;
    return ret;
}

size_t strnlen(const char * s, size_t count)
{
	const char *sc;

	for (sc = s; count-- && *sc != '\0'; ++sc)
		/* nothing */;
	return sc - s;
}

/* http://clc-wiki.net/wiki/strlen#Implementation */
size_t strlen(const char *s) {
    size_t i;
    for (i = 0; s[i] != '\0'; i++) ;
    return i;
}

/* http://clc-wiki.net/wiki/strncpy#Implementation */
char *strncpy(char *dest, const char *src, size_t n)
{
    char *ret = dest;
    do {
        if (!n--)
            return ret;
    } while ( (*dest++ = *src++) );
    while (n--)
        *dest++ = 0;
    return ret;
}
