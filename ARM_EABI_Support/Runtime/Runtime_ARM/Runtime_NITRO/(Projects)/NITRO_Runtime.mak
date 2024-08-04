# Usage: 
# make -f NITRO_Runtime.mak
#
# Required Environment Variables
#
# Environment variable CWINSTALL must be set to the root of your installation.
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
AS = $(TOOLS)/mwasmarm.exe
ASSEMBLE = $(AS)


# Local variable definitions
#
# Compile and Link command variables
COMPILE = $(CC)
LINK = $(LD) 
ASSEMBLER = $(AS)

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
OBJDATA_ROOT = Runtime_ARM_CmdLineData

ABI=0



# Common include directories, note -I- required if system directories are to
# be searched ( <> type includes )
#
INCLUDE_ROOT_RUNTIME = ../..
INCLUDE_ROOT_MSL = ../../../../msl
INCLUDE_ROOT_MATH = ../../../../Mathlib/lib


INCLUDE = -I- -I$(INCLUDE_ROOT_MSL)/MSL_C/MSL_Common/Include
INCLUDE += -I$(INCLUDE_ROOT_MSL)/MSL_C/MSL_ARM/Include
INCLUDE += -I$(INCLUDE_ROOT_MSL)/MSL_C++/MSL_Common/Include
INCLUDE += -I$(INCLUDE_ROOT_MSL)/MSL_C++/MSL_ARM/Include
INCLUDE += -I$(INCLUDE_ROOT_MSL)/MSL_Extras/MSL_Common/Include
INCLUDE += -I$(INCLUDE_ROOT_MATH)
INCLUDE += -I$(INCLUDE_ROOT_RUNTIME)/../"(Runtime_Common)"
INCLUDE += -I$(INCLUDE_ROOT_RUNTIME)/../"(Runtime_Common)"/MWRuntime 
INCLUDE += -I$(INCLUDE_ROOT_RUNTIME)/../"(Runtime_Common)"/cxxabi 
INCLUDE += -I$(INCLUDE_ROOT_RUNTIME)/../"(RISC_Common)" 
INCLUDE += -I$(INCLUDE_ROOT_RUNTIME)/"(Common_Source)"
INCLUDE += -ir "$(NITROSDK_ROOT)"/include


# Build ARM ABI compliant C libs if make specified with ABI=1
#
ifeq ($(ABI),1)
ABISPEC=-D_AEABI_PORTABILITY_LEVEL=1 -D_CPPABI
else
ABISPEC=
endif

# Do not build typeinfo objects for basic types in runtime.
# For 'typeid(obj).name()' to return unmangled obj/type name for standard types.
#
RUNTIME_TYPEINFO=-DNO_RUNTIME_BASIC_TYPEINFO

# Common build flags
#
CXFLAGS	= -warnings on,nocmdline -opt level=4,speed -inline smart,bottomup -ipa file -noconstpool -char unsigned  -Cpp_exceptions on -str reuse  $(INCLUDE) -c $(ABISPEC) $(RUNTIME_TYPEINFO)
LXFLAGS	= -warnings on,nocmdline  -library 
AXFLAGS =

# Target name definition and target specific build flags
#
T01 = NITRO_Runtime_A_LE 
T01CFLAGS = -proc arm946e -little -nointerworking 
T01LFLAGS = -proc arm946e -little -nointerworking
T01AFLAGS = -proc arm4t -little

T02 = NITRO_Runtime_Ai_LE
T02CFLAGS = -proc arm946e -little -interworking 
T02LFLAGS = -proc arm946e -little -interworking
T02AFLAGS = -proc arm4t -little

T03 = NITRO_Runtime_T_LE 
T03CFLAGS = -proc arm946e -little -thumb -interworking 
T03LFLAGS = -proc arm946e -little -thumb -interworking
T03AFLAGS = -proc arm4t -little -16

T04 = NITRO_Runtime_A_BE
T04CFLAGS = -proc arm946e -big -nointerworking 
T04LFLAGS = -proc arm946e -big -nointerworking
T04AFLAGS = -proc arm4t -big

T05 = NITRO_Runtime_Ai_BE
T05CFLAGS = -proc arm946e -big -interworking 
T05LFLAGS = -proc arm946e -big -interworking
T05AFLAGS = -proc arm4t -big

T06 = NITRO_Runtime_T_BE 
T06CFLAGS = -proc arm946e -big -thumb -interworking 
T06LFLAGS = -proc arm946e -big -thumb -interworking
T06AFLAGS = -proc arm4t -big -16

T07 = NITRO_Runtime_A_LE_PIC_PID
T07CFLAGS = -proc arm946e -little -nointerworking -pic -pid 
T07LFLAGS = -proc arm946e -little -nointerworking -pic -pid
T07AFLAGS = -proc arm4t -little

T08 = NITRO_Runtime_Ai_LE_PIC_PID
T08CFLAGS = -proc arm946e -little -interworking -pic -pid 
T08LFLAGS = -proc arm946e -little -interworking -pic -pid
T08AFLAGS = -proc arm4t -little

T09 = NITRO_Runtime_T_LE_PIC_PID 
T09CFLAGS = -proc arm946e -little -thumb -interworking -pic -pid 
T09LFLAGS = -proc arm946e -little -thumb -interworking -pic -pid
T09AFLAGS = -proc arm4t -little -16

T10 = NITRO_Runtime_A_BE_PIC_PID
T10CFLAGS = -proc arm946e -big -nointerworking -pic -pid 
T10LFLAGS = -proc arm946e -big -nointerworking -pic -pid
T10AFLAGS = -proc arm4t -big

T11 = NITRO_Runtime_Ai_BE_PIC_PID
T11CFLAGS = -proc arm946e -big -interworking -pic -pid 
T11LFLAGS = -proc arm946e -big -interworking -pic -pid
T11AFLAGS = -proc arm4t -big

T12 = NITRO_Runtime_T_BE_PIC_PID 
T12CFLAGS = -proc arm946e -big -thumb -interworking -pic -pid 
T12LFLAGS = -proc arm946e -big -thumb -interworking -pic -pid
T12AFLAGS = -proc arm4t -big -16

V4T = $(T01) $(T02) $(T03) $(T04) $(T05) $(T06) $(T07) $(T08) $(T09) $(T10) $(T11) $(T12)

# Target specific variables, note the scope of the setting follows the
# dependencies. So whatever objs are required to build this target, the object requiring a
# build will get this setting. E.g. ../lib/t1.a : compiler flags = common flags plus t1 flags 
#
settargetvars=$(addprefix $(LIBOUT)/, $(addsuffix $(LIBTYPE),$($1))) : $2FLAGS=$($2XFLAGS) $($1$2FLAGS) 

# As an example, the first two macro calls expand to :
# $(addprefix $(LIBOUT), $(addsuffix $(LIBTYPE),$(T1))) : CFLAGS=$(CXFLAGS) $(T1CFLAGS) 
# $(addprefix $(LIBOUT), $(addsuffix $(LIBTYPE),$(T1))) : LFLAGS=$(LXFLAGS) $(T1LFLAGS) 
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
$(call settargetvars,T01,A)
$(call settargetvars,T02,C)
$(call settargetvars,T02,L)
$(call settargetvars,T02,A)
$(call settargetvars,T03,C)
$(call settargetvars,T03,L)
$(call settargetvars,T03,A)
$(call settargetvars,T04,C)
$(call settargetvars,T04,L)
$(call settargetvars,T04,A)
$(call settargetvars,T05,C)
$(call settargetvars,T05,L)
$(call settargetvars,T05,A)
$(call settargetvars,T06,C)
$(call settargetvars,T06,L)
$(call settargetvars,T06,A)
$(call settargetvars,T07,C)
$(call settargetvars,T07,L)
$(call settargetvars,T07,A)
$(call settargetvars,T08,C)
$(call settargetvars,T08,L)
$(call settargetvars,T08,A)
$(call settargetvars,T09,C)
$(call settargetvars,T09,L)
$(call settargetvars,T09,A)
$(call settargetvars,T10,C)
$(call settargetvars,T10,L)
$(call settargetvars,T10,A)
$(call settargetvars,T11,C)
$(call settargetvars,T11,L)
$(call settargetvars,T11,A)
$(call settargetvars,T12,C)
$(call settargetvars,T12,L)
$(call settargetvars,T12,A)

# List of targets
#
V4T_TARGETS = $(V4T)
TARGETS = $(V4T_TARGETS)

# Search paths for files
#
vpath % ../../../(RISC_Common) ../../../(Runtime_Common) ../../../(Runtime_Common)/MWRuntime ../../../(Runtime_Common)/cxxabi ../../(Common_Source)

# Determine the library components
#
ALLCPPFILES = $(wildcard ../../../(RISC_Common)/*.cpp)
ALLCPPFILES += $(wildcard ../../../(Runtime_Common)/*.cpp)
ALLCPPFILES += $(wildcard ../../../(Runtime_Common)/cxxabi/*.cpp)
ALLCPPFILES += $(wildcard ../../(Common_Source)/*.cpp)

ALLCFILES = $(wildcard ../../../(Runtime_Common)/*.c)
ALLCFILES += $(wildcard ../../../(Runtime_Common)/cxxabi/*.c)
ALLCFILES += $(wildcard ../../(Common_Source)/*.c)

ALLCPFILES = $(wildcard ../../(Common_Source)/*.cp)

ALLASMFILES = $(wildcard ../../(Common_Source)/*.s)

# Exclude these files from the library
#
AFILES := $(ALLASMFILES)
CFILES := $(ALLCFILES)

CFILES := $(filter-out %/__arm_eabi_init.c,$(CFILES))
CFILES := $(filter-out %/ROMCopy.c,$(CFILES))
CFILES := $(filter-out %/semihosted_file_io.c,$(CFILES))
CFILES := $(filter-out %/semihosted_console_io.c,$(CFILES))
CFILES := $(filter-out %/semihosted_support.c,$(CFILES))
CFILES := $(filter-out %/abort_exit.c,$(CFILES))

# Filter out Thumb_interworking.c for ARM targets only
#
ifneq (_T_,$(findstring _T_,$(TARGET)))
 CFILES := $(filter-out %/Thumb_interworking.c,$(CFILES))
endif

# Do not include ARM ABI 2 Files
ifneq ($(ABI),1)
ALLCPPFILES := $(filter-out %/cppsemantics.cpp,$(ALLCPPFILES))
ALLCPPFILES := $(filter-out %/derived_to_base_conversion.cpp,$(ALLCPPFILES))
CFILES := $(filter-out %/unwinder.c,$(CFILES))
CFILES := $(filter-out %/unwind_pr.c,$(CFILES))
AFILES := $(filter-out %/memclr.s,$(AFILES))
AFILES := $(filter-out %/memcpy.s,$(AFILES))
AFILES := $(filter-out %/memmove.s,$(AFILES))
AFILES := $(filter-out %/memset.s,$(AFILES))
AFILES := $(filter-out %/exceptionix.s,$(AFILES))
endif


# Workaround for aeabi memclr,memcpy,etc. that don't support Thumb yet.
# Remove from Thumb targets
#
ifeq (_T_,$(findstring _T_,$(TARGET)))
 AFILES := $(filter-out %/memclr.s,$(AFILES))
 AFILES := $(filter-out %/memcpy.s,$(AFILES))
 AFILES := $(filter-out %/memmove.s,$(AFILES))
 AFILES := $(filter-out %/memset.s,$(AFILES))
endif

CPPFILES := $(ALLCPPFILES)
ASMFILES := $(AFILES)
CPFILES := $(ALLCPFILES)


# Create the object file names
#
COBJS = $(addsuffix $(OBJTYPE),$(notdir $(basename $(CFILES))))
CPPOBJS = $(addsuffix $(OBJTYPE),$(notdir $(basename $(CPPFILES))))
ASMOBJS = $(addsuffix $(OBJTYPE),$(notdir $(basename $(ASMFILES))))
CPOBJS = $(addsuffix $(OBJTYPE),$(notdir $(basename $(CPFILES))))


# Define the target makefile name
#
TARGET_MAK = NITRO_Runtime.mak

# The common makefile will try to make all targets by recursively calling
# make TARGET=<targetname>. This creates a target consisting of the library
# name with dependencies consisting of all the objects from FILES. A static
# pattern rule defines the .c files for the dependencies of the .o files.
#
include ../../../../msl/(MSL_Build_Projects)/MSL_C.mak
