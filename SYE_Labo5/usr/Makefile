# GNU Makefile for building user programs to run on top of Nachos
#
# Modif. 2015
#
# First setup the building environment


-include Makefile.common

LIBC_DIR = $(PWD)/libc

LDFLAGS      = -T libc/arm.lds -N -warn-common -warn-constructors -warn-multiple-gp -L $(LIBGCC_PATH) -lgcc 

.PHONY: all clean

# Our source apps
-include src/Makefile

CFLAGS += -I$(LIBC_DIR)/include

# make executes the first rule it finds in the Makefiles, unless it is specified
# on the comand line
all: $(patsubst %,%.elf,$(TARGETS))
	
src/%.o: src/%.c 
	$(CC) $(CFLAGS) -c $< -o $@
	
# In the following linker options, -lso3 appears twice because of cycle references
%.elf: src/%.o libc/crt0.o libc/crt1.o $(LIBC_DIR)/$(NLIB)  
	$(LD) -o $@ libc/crt0.o libc/crt1.o $< -L$(LIBC_DIR) -lso3 $(LDFLAGS) -L$(LIBC_DIR)/  -lso3

$(LIBC_DIR)/$(NLIB):  
	make -C libc

# Generic targets
clean: 
	rm -f *.o *.elf 
	
