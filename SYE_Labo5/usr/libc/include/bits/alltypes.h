#ifndef ALLTYPES_H
#define ALLTYPES_H

#define _Addr int
#define _Int64 long long
#define _Reg int

typedef __builtin_va_list va_list;
typedef __builtin_va_list __isoc_va_list;

typedef struct _IO_FILE FILE;

typedef unsigned _Addr uintptr_t;

typedef signed char     int8_t;
typedef short           int16_t;
typedef int             int32_t;
typedef _Int64          int64_t;
typedef _Int64          intmax_t;
typedef unsigned char   uint8_t;
typedef unsigned short  uint16_t;
typedef unsigned int    uint32_t;
typedef unsigned _Int64 uint64_t;
typedef unsigned _Int64 u_int64_t;
typedef unsigned _Int64 uintmax_t;

typedef uint16_t u_short;

typedef int pid_t;

#ifndef __cplusplus
typedef unsigned wchar_t;
#endif
typedef unsigned int size_t;
typedef int ssize_t;
typedef unsigned int locale_t;

typedef unsigned int off_t;

typedef float float_t;
typedef double double_t;

typedef unsigned wint_t;
typedef struct __mbstate_t { unsigned __opaque1, __opaque2; } mbstate_t;
typedef unsigned long wctype_t;
typedef _Addr ptrdiff_t;

typedef struct { long long __ll; long double __ld; } max_align_t;

typedef long time_t;
typedef long suseconds_t;

struct iovec { void *iov_base; size_t iov_len; };

typedef struct { union { int __i[9]; volatile int __vi[9]; unsigned __s[9]; } __u; } pthread_attr_t;
typedef struct { union { int __i[6]; volatile int __vi[6]; volatile void *volatile __p[6]; } __u; } pthread_mutex_t;
typedef struct { union { int __i[6]; volatile int __vi[6]; volatile void *volatile __p[6]; } __u; } mtx_t;
typedef struct { union { int __i[12]; volatile int __vi[12]; void *__p[12]; } __u; } pthread_cond_t;
typedef struct { union { int __i[12]; volatile int __vi[12]; void *__p[12]; } __u; } cnd_t;
typedef struct { union { int __i[8]; volatile int __vi[8]; void *__p[8]; } __u; } pthread_rwlock_t;
typedef struct { union { int __i[5]; volatile int __vi[5]; void *__p[5]; } __u; } pthread_barrier_t;

#endif /* ALLTYPES_H */
