# Usage:
# make -f MSL_Extras.NITRO.mak
#
# Required Environment Variables
#
# Environment variable CWINSTALL must be set to the root of your current installation
#
# Example:
# CWINSTALL = C:/Program Files/Freescale/CW for NINTENDO DSi V1.3
#
# Reset environment vars you explicitly want to override
#
MWCIncludes =
export MWCIncludes


# CWINSTALL
#
ifndef CWINSTALL
errornotdefined1:
	@echo "CWINSTALL not defined"
endif

TOOLS = "$(CWINSTALL)"/ARM_Tools/Command_Line_Tools
CC = $(TOOLS)/mwccarm.exe
LD = $(TOOLS)/mwldarm.exe


# Local variable definitions
#
# Compile and Link command variables
COMPILE = $(CC)
LINK = $(LD) 

# Library file suffix
#
LIBTYPE = .a

# Library file output path
#
LIBOUT = ../Lib

# Object file suffix
#
OBJTYPE = .o

# Object file output path (relative to target directory)
#
OBJOUT = obj

# Root directory for all generated command line output
#
OBJDATA_ROOT = MSL_Extras.ARM_CmdLineData


# Common include directories, note -I- required if system directories are to
# be searched ( <> type includes )
#
INCLUDE_ROOT = ../../../../msl
INCLUDE = -I- -I$(INCLUDE_ROOT)/MSL_C/MSL_Common/Include 
INCLUDE += -I$(INCLUDE_ROOT)/MSL_C/MSL_ARM/Include 
INCLUDE += -I$(INCLUDE_ROOT)/MSL_Extras/MSL_Common/Include 
INCLUDE += -I$(INCLUDE_ROOT)/MSL_Extras/MSL_ARM/Include 

# Build ARM ABI compliant C libs if make specified with ABI=1
#
ifeq ($(ABI),1)
ABISPEC=-D_AEABI_PORTABILITY_LEVEL=1
else
ABISPEC=
endif

# Tiny IO
#
ifeq ($(TINY),1)
TINYSPEC=-D_MSL_C_TINY_IO=1 -D_MSL_TINY_FILE_IO=1 -D_MSL_TESTING_TINY_IO=1
else
TINYSPEC=
endif


# Common build flags
#
CXFLAGS	= -warnings on,nocmdline -opt level=4,speed -inline smart,bottomup -ipa file -noconstpool -char unsigned  -Cpp_exceptions off -str reuse $(INCLUDE) -c $(ABISPEC) $(TINYSPEC)
LXFLAGS	= -warnings on,nocmdline  -library 

# Target name definition and target specific build flags
#
T01 = MSL_Extras_NITRO_A_LE 
T01CFLAGS = -proc arm946e -little -nointerworking -prefix PREFIX_NITRO.h
T01LFLAGS = -proc arm946e -little -nointerworking

T02 = MSL_Extras_NITRO_Ai_LE
T02CFLAGS = -proc arm946e -little -interworking -prefix PREFIX_NITRO.h
T02LFLAGS = -proc arm946e -little -interworking

T03 = MSL_Extras_NITRO_T_LE 
T03CFLAGS = -proc arm946e -little -thumb -interworking -prefix PREFIX_NITRO.h
T03LFLAGS = -proc arm946e -little -thumb -interworking

T04 = MSL_Extras_NITRO_A_BE
T04CFLAGS = -proc arm946e -big -nointerworking -prefix PREFIX_NITRO.h
T04LFLAGS = -proc arm946e -big -nointerworking

T05 = MSL_Extras_NITRO_Ai_BE
T05CFLAGS = -proc arm946e -big -interworking -prefix PREFIX_NITRO.h
T05LFLAGS = -proc arm946e -big -interworking

T06 = MSL_Extras_NITRO_T_BE 
T06CFLAGS = -proc arm946e -big -thumb -interworking -prefix PREFIX_NITRO.h
T06LFLAGS = -proc arm946e -big -thumb -interworking

T07 = MSL_Extras_NITRO_A_LE_PIC_PID
T07CFLAGS = -proc arm946e -little -nointerworking -pic -pid -prefix PREFIX_NITRO.h
T07LFLAGS = -proc arm946e -little -nointerworking -pic -pid

T08 = MSL_Extras_NITRO_Ai_LE_PIC_PID
T08CFLAGS = -proc arm946e -little -interworking -pic -pid -prefix PREFIX_NITRO.h
T08LFLAGS = -proc arm946e -little -interworking -pic -pid

T09 = MSL_Extras_NITRO_T_LE_PIC_PID 
T09CFLAGS = -proc arm946e -little -thumb -interworking -pic -pid -prefix PREFIX_NITRO.h
T09LFLAGS = -proc arm946e -little -thumb -interworking -pic -pid

T10 = MSL_Extras_NITRO_A_BE_PIC_PID
T10CFLAGS = -proc arm946e -big -nointerworking -pic -pid -prefix PREFIX_NITRO.h
T10LFLAGS = -proc arm946e -big -nointerworking -pic -pid

T11 = MSL_Extras_NITRO_Ai_BE_PIC_PID
T11CFLAGS = -proc arm946e -big -interworking -pic -pid -prefix PREFIX_NITRO.h
T11LFLAGS = -proc arm946e -big -interworking -pic -pid

T12 = MSL_Extras_NITRO_T_BE_PIC_PID 
T12CFLAGS = -proc arm946e -big -thumb -interworking -pic -pid -prefix PREFIX_NITRO.h
T12LFLAGS = -proc arm946e -big -thumb -interworking -pic -pid

V4T = $(T01) $(T02) $(T03) $(T04) $(T05) $(T06) $(T07) $(T08) $(T09) $(T10) $(T11) $(T12)

# Target specific variables, note the scope of the setting follows the
# dependencies. So whatever objs are required to build this target, the object requiring a
# build will get this setting. E.g. ../lib/t1.a : compiler flags = common flags plus t1 flags 
#
settargetvars=$(addprefix $(LIBOUT)/, $(addsuffix $(LIBTYPE),$($1))) : $2FLAGS=$($2XFLAGS) $($1$2FLAGS) 

# As an example, the first two macro calls expand to :
# $(addprefix $(LIBOUT)/, $(addsuffix $(LIBTYPE),$(T1))) : CFLAGS=$(CXFLAGS) $(T1CFLAGS) 
# $(addprefix $(LIBOUT)/, $(addsuffix $(LIBTYPE),$(T1))) : LFLAGS=$(LXFLAGS) $(T1LFLAGS) 
#
# and utimately to rule such as:
#
# ../lib/<target>.a	: 	CFLAGS=$(CXFLAGS) $(T1CFLAGS)
# ../lib/<target>.a	: 	LFLAGS=$(LXFLAGS) $(T1LFLAGS)
#
#
# This sets the CFLAGS and LFLAGS variables according to the target being built. The CFLAGS
# and LFLAGS settings is carried to the dependencies of this target also. So any objects
# that need to get built to make the target library get these CFLAGS and LFLAGS settings, also.
#
$(call settargetvars,T01,C)
$(call settargetvars,T01,L)
$(call settargetvars,T02,C)
$(call settargetvars,T02,L)
$(call settargetvars,T03,C)
$(call settargetvars,T03,L)
$(call settargetvars,T04,C)
$(call settargetvars,T04,L)
$(call settargetvars,T05,C)
$(call settargetvars,T05,L)
$(call settargetvars,T06,C)
$(call settargetvars,T06,L)
$(call settargetvars,T07,C)
$(call settargetvars,T07,L)
$(call settargetvars,T08,C)
$(call settargetvars,T08,L)
$(call settargetvars,T09,C)
$(call settargetvars,T09,L)
$(call settargetvars,T10,C)
$(call settargetvars,T10,L)
$(call settargetvars,T11,C)
$(call settargetvars,T11,L)
$(call settargetvars,T12,C)
$(call settargetvars,T12,L)

# List of targets
#
V4T_TARGETS = $(V4T)

TARGETS = $(V4T_TARGETS)


# Search paths for files
#
vpath %.c ../../MSL_Common/Src

# Determine the library components
#
ALLFILES = $(wildcard ../../MSL_Common/Src/*.c)

# Filter ALLFILES for excluded files here
#
CFILES := $(ALLFILES)
CPPFILES :=
ASMFILES :=

# Exclude the files that don't belong in the library
#
CFILES := $(filter-out %/old_posix.c,$(CFILES))
CFILES := $(filter-out %/stat.c,$(CFILES))
CFILES := $(filter-out %/stdio_posix.c,$(CFILES))

# Create the object file names
#
COBJS = $(addsuffix $(OBJTYPE),$(notdir $(basename $(CFILES))))
CPPOBJS = $(addsuffix $(OBJTYPE),$(notdir $(basename $(CPPFILES))))
ASMOBJS = $(addsuffix $(OBJTYPE),$(notdir $(basename $(ASMFILES))))

# Define the target makefile name
#
TARGET_MAK = MSL_Extras.NITRO.mak

# The common makefile will try to make all targets by recursively calling
# make TARGET=<targetname>. This creates a target consisting of the library
# name with dependencies consisting of all the objects from FILES. A static
# pattern rule defines the .c files for the dependencies of the .o files.
#
include ../../../../msl/(MSL_Build_Projects)/MSL_C.mak



