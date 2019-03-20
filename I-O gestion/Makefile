#-----------------------------------------------------------------------------
# 
# light effects project
#
# this GNU-makefile relies on the GCC toolchain
# nb: on Windows, the Mingw-w64 package provides the mingw32-make.exe command
#     ( see http://www.enib.fr/~harrouet/s4prc/#environ.windows )
#
#	Adapted and widely modified by
#	Hugo Schaaf - ( see https://github.com/hugoschaaf98/ )
# 2019-03-10
#
#-----------------------------------------------------------------------------


#---- control global settings ------------------------------
#
# make opt=1 --> enable optimisation, then disable debug
# make opt=0 --> disable optimisation, then enable debug
opt=0
# make clang=1 --> use clang/clang++, not gcc/g++
# make clang=0 --> use gcc/g++, not clang/clang++
clang=0
# make emcc=1 --> target javascript rather than the native platform
# make emcc=0 --> target the native platform rather than javascript
emcc=0

#---- directories ------------------------------
#
# headers directory
DINC=include/
# source directory
DSRC=src/
# object directory
DOBJ=obj/
# executable directory
DBIN=bin/

#---- build program ------------------------------
#
# ${EXE_PREFIX}* programs will be built
EXE_PREFIX=main

#---- detect operating system ------------------------------
#
ifneq (${OS},Windows_NT)
  ifneq (,${findstring Microsoft,${shell cat /proc/version 2>/dev/null}})
	# Windows-Subsystem-for-Linux
	OS:=WSL
  else ifneq (,${findstring Ubuntu,${shell lsb_release -i 2>/dev/null}})
	OS:=Ubuntu
  else ifneq (,${findstring Raspbian,${shell lsb_release -i 2>/dev/null}})
	# Standard distribution for Raspberry-Pi
	OS:=Raspbian
  else
	OS:=${strip ${shell uname -s}}
  endif
endif

#---- adjust project-specific settings -----------------------------
#
CPPFLAGS=
ifneq (${strip ${DINC}},)
	CPPFLAGS+=-I${DINC}
endif
LDFLAGS=
# LDFLAGS+=-L library/path -Wl,-rpath,library/path -l library_name
CFLAGS=
CXXFLAGS=
VPATH+=${DSRC}:${DOBJ}

#---- adjust platform-specific features (Posix/Windows/Emscripten...) ------------------
#
ifeq (${OS},Windows_NT)
  # nothing special for now
else
  CPPFLAGS+=-fPIC
  ifeq (${OS},Darwin)
	# nothing special for now
  else
	ifeq (${OS},Ubuntu)
	  # sanitizer requires gold-linker on Ubuntu
	  LDFLAGS+=-fuse-ld=gold
	else ifeq (${OS},Raspbian)
	  # some warnings may appear when mixing g++-6 and g++-7 on Raspbian
	  CXXFLAGS+=-Wno-psabi
		else
	  	# nothing special for now
		endif
  endif
endif

ifeq (${OS},Windows_NT)
  EXE_SUFFIX=.exe
  SKIP_LINE=echo.
  REMOVE=del /q
else
  EXE_SUFFIX=
  SKIP_LINE=echo
  REMOVE=rm -rf
endif
ifeq (${strip ${emcc}},1)
  EXE_SUFFIX:=.html
endif

#---- deduce file names ------------------------------------------
#
# find main source file
MAIN_C_FILE=${wildcard ${strip ${DSRC}${EXE_PREFIX}.c}}
MAIN_CXX_FILE=${wildcard ${strip ${DSRC}${EXE_PREFIX}.cpp}}

# find common source files
COMMON_C_FILES=${filter-out ${MAIN_C_FILE},${wildcard ${DSRC}*.c}}
COMMON_CXX_FILES=${filter-out ${MAIN_CXX_FILE},${wildcard ${DSRC}*.cpp}}

# deduce object file names from source file names
MAIN_OBJECT_FILE=${sort ${patsubst ${DSRC}%.c,${DOBJ}%.o,${MAIN_C_FILE}} \
						 ${patsubst ${DSRC}%.cpp,${DOBJ}%.o,${MAIN_CXX_FILE}}}
COMMON_OBJECT_FILES=${sort ${patsubst ${DSRC}%.c,${DOBJ}%.o,${COMMON_C_FILES}} \
						   ${patsubst ${DSRC}%.cpp,${DOBJ}%.o,${COMMON_CXX_FILES}}}
OBJECT_FILES=${MAIN_OBJECT_FILE} ${COMMON_OBJECT_FILES}

# deduce depend file names
DEPEND_FILES=${patsubst %.o,%.d,${OBJECT_FILES}}

# deduce executable file name
EXE_FILE = ${DBIN}${EXE_PREFIX}${EXE_SUFFIX}
# deduce generated file names
GENERATED_FILES=${DEPEND_FILES} ${OBJECT_FILES} ${EXE_FILE}
ifeq (${OS},Darwin)
  GENERATED_FILES+=${wildcard *.dSYM}
endif
ifeq (${strip ${emcc}},1)
  GENERATED_FILES+=${patsubst %.html,%.js,${EXE_FILE}}
  GENERATED_FILES+=${patsubst %.html,%.html.mem,${EXE_FILE}}
endif

# adjustments for the clean target :
# some editors generates files ending by "~"
# and when a program fails core or .<pid> files are sometimes 
# generated where <pid> represents the PID number of the
# process (from 1 up tu 5 characters)
GENERATED_FILES+=${wildcard *~ core}
GENERATED_FILES+=${wildcard .[1-9]}
GENERATED_FILES+=${wildcard .[1-9][0-9]}
GENERATED_FILES+=${wildcard .[1-9][0-9][0-9]}
GENERATED_FILES+=${wildcard .[1-9][0-9][0-9][0-9]}
GENERATED_FILES+=${wildcard .[1-9][0-9][0-9][0-9][0-9]}

#---- compiler/linker settings ------------------------------
#
CPPFLAGS+=-pedantic -Wall -Wextra -Wconversion -MMD
CFLAGS+=-std=c99 -Wc++-compat -Wwrite-strings -Wold-style-definition
CXXFLAGS+=-std=c++1z
# sign-conversion is too restrictive on standard C++ library usage
CXXFLAGS+=-Wno-sign-conversion
# clang warns about missing double-braces on std::array
CXXFLAGS+=-Wno-missing-braces
LDFLAGS+=
ifeq (${strip ${emcc}},1)
  CC=emcc
  CXX=em++
else ifeq (${strip ${clang}},1)
  CC=clang
  CXX=clang++
else
  CC=gcc
  CXX=g++
endif
#
ifneq (${strip ${MAIN_CXX_FILE} ${COMMON_CXX_FILES}},)
  # force c++ usage if there is at least one c++ source file
  CC:=${CXX}
  CFLAGS:=${CXXFLAGS}
endif
#
LD:=${CC}

#---- debug/optimisation settings ------------------------------
ifeq (${strip ${opt}},1)
  CPPFLAGS+=-O3 -DNDEBUG -fomit-frame-pointer
  CPPFLAGS+=-ffast-math
  CPPFLAGS+=-march=native
  # CPPFLAGS+=-fopt-info-vec-optimized
else
  CPPFLAGS+=-g -O0 -UNDEBUG
  ifeq (${strip ${emcc}},1)
	# sanitizer is not available yet with Emscripten
  else ifeq (${OS},Windows_NT)
	# sanitizer is not available yet on Windows
  else ifeq (${OS},WSL)
	# sanitizer is not available yet on Windows-Subsystem-for-Linux
  else ifeq (${OS},Darwin)
	# sometimes sanitizer produces linker warnings on MacOSX
  else
	CPPFLAGS+=-fsanitize=address,undefined
	ifeq (${OS},Raspbian)
	  # dynamic sanitizer libraries may not be found on Raspbian
	  CPPFLAGS+=-static-libasan -static-libubsan
	endif
  endif
endif

#---- main target ------------------------------
#
all : ${EXE_FILE}
rebuild : clean all

.SUFFIXES:
.SECONDARY:
.PHONY: all clean rebuild printfilenames

# linker command to produce the executable files (if any) ----
${EXE_FILE} : ${MAIN_OBJECT_FILE} ${COMMON_OBJECT_FILES}
	@echo ==== linking $@ ====
	${LD} -o $@ $^ ${CPPFLAGS} ${LDFLAGS}
	@${SKIP_LINE}

# compiler command for every source file ----
${DOBJ}%.o : ${DSRC}%.c
	@echo ==== compiling [opt=${opt}] $< ====
	${CC} -o $@ $< -c ${CPPFLAGS} ${CFLAGS}
	${REMOVE} ${DEPEND_FILES}
	@${SKIP_LINE}

${DOBJ}%.o : ${DSRC}%.cpp
	@echo ==== compiling [opt=${opt}] $< ====
	${CXX} -o $@ $< -c ${CPPFLAGS}
	${CXXFLAGS}
	@${SKIP_LINE}

-include ${DEPEND_FILES}

# remove generated files ----
clean :
	@echo ==== cleaning ====
	${REMOVE} ${GENERATED_FILES}
	@${SKIP_LINE}

printfilenames :
	@echo source file names : ${MAIN_C_FILE} ${COMMON_C_FILES}
	@echo object file names : ${MAIN_OBJECT_FILE} ${COMMON_OBJECT_FILES}
	@echo depend file names : ${DEPEND_FILES}
	@echo generated files : ${GENERATED_FILES}
	@${SKIP_LINE}

#-----------------------------------------------------------------------------