# Possible problems:
# 1.  The definition of uchar in p2c.h
# 2.  System routines: access, isatty, snprintf, system, random, srandom, time
# 3.  The size of int
# 4.  Memory availability during execution.

# System-dependent parameters.  These may need tweaking:

# Uncomment this to force the use of rand() and srand() respectively instead of
# random() and srandom(). This is necessary for some linux systems.
# DEFINEA=-DRAND

# If snprintf is not available then type `make clean',
# uncomment this line, and try again:
# DEFINEB=-DNO_SNPRINTF

# Server operation: Use the -z option of dpic.o dpic2.or uncomment the following to
# compile dpic with sh and copy commands disabled to prevent access to system
# files.
# SAFEMODE= -DSAFE_MODE

# For DJGPP compilation:
# DEFINEB=
# CFLAGS= $(DEFINEA) -DNO_SNPRINTF $(SAFEMODE) -mcpu=pentium -march=i386 -O

# MinGW
# LIBS = -liberty

# Ultrix mips
# CFLAGS = $(DEFINEA) $(DEFINEB) $(SAFEMODE) -O -Olimit 1600

# AIX
# CC=xlc

# other.  cc usually works too.
CFLAGS = -O
CC=gcc

OBJECTS = dpic.o dpic2.o p2clib.o

# If debug is enabled:
# OBJECTS = dpic.o dpic2.o p2clib.o sysdep.o

######################################


dpic: $(OBJECTS)
	$(CC) -o dpic $(OBJECTS) -lm $(LIBS)

clean:
	-rm -f *.o dpic dpic.exe *.LOG
