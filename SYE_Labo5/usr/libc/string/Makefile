
-include $(USR_DIR)/Makefile.common

LIB = strcpy strcmp strncmp strlen memcpy strncpy memset memcmp strcat strchrnul strnlen memchr
LIB += stpncpy stpcpy strchr

all: $(patsubst %,%.o,$(LIB))

clean:
	rm -rf *.o

	