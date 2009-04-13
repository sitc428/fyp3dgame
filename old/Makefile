#############################################################################
# Makefile for building: FYP
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
CFLAGS        = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -fpermissive -g -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I. -I../include
LINK          = g++
LFLAGS        = -Wl
LIBS          = $(SUBLIBS) -lfreetype -L../lib -lIrrlicht -lboost_date_time-gcc42-mt-s-1_37 -lboost_thread-gcc42-mt-s-1_37
AR            = ar cqs
RANLIB        = 
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -sf
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = ./CGUITTFont.cpp \
		./ConcurrentQueue.cpp \
		./GameObjectCollection.cpp \
		./InputEventHandler.cpp \
		./main.cpp \
		./Player.cpp \
		./ProgressCircle.cpp \
		./RenderingHandler.cpp 
OBJECTS       = CGUITTFont.o \
		ConcurrentQueue.o \
		GameObjectCollection.o \
		InputEventHandler.o \
		main.o \
		Player.o \
		ProgressCircle.o \
		RenderingHandler.o
QMAKE_TARGET  = uFYP
DESTDIR       = 
TARGET        = uFYP

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

clean: 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


####### Compile

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

