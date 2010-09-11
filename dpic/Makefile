# Installation shortcuts: change the following and type "make install"

# For Fedora Linux (expects "make DESTDIR=xxx PREFIX=yyy install"):
DESTDIR = $${HOME}
PREFIX = .
DEST = ${DESTDIR}/${PREFIX}/bin

# For manual installation (uncomment and change as necessary):
# DEST = $${HOME}/bin

#-----------------------------------------------------------------------

# Possible problems:
# 1.  The definition of uchar in p2c.h
# 2.  System routines: access, isatty, snprintf, system, random, srandom, time
# 3.  The size of int
# 4.  Memory availability during execution.

# System-dependent parameters.  These may need tweaking:

# Uncomment this to force the use of rand() and srand() respectively instead of
# random() and srandom(). This is necessary for some Linux systems.
# DEFINEA=-DRAND

# If snprintf is unavailable then uncomment the following, type "make clean",
# and try again:
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
CFLAGS = $(DEFINEA) $(DEFINEB) $(SAFEMODE) -O
CC=gcc

OBJECTS = dpic.o dpic2.o p2clib.o

# If debug is enabled:
# OBJECTS = dpic.o dpic2.o p2clib.o sysdep.o

#-----------------------------------------------------------------------


dpic: $(OBJECTS)
	$(CC) -o dpic $(OBJECTS) -lm $(LIBS)

install: dpic
	mkdir -p $(DEST)
	if test -x dpic.exe ; then \
      strip dpic.exe; install dpic.exe $(DEST) ; \
    else \
      strip dpic; install -m 755 dpic $(DEST) ; \
    fi

clean:
	-rm -f *.o dpic dpic.exe *.LOG
