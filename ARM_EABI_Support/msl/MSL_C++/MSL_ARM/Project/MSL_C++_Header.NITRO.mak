# Usage:
# make -f MSL_C++_Header.NITRO.mak
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
	@echo "tools.mak: CWINSTALL not defined"
endif

TOOLS = "$(CWINSTALL)"/ARM_Tools/Command_Line_Tools
CC = $(TOOLS)/mwccarm.exe
LD = $(TOOLS)/mwldarm.exe


# Local variable definitions
#
# Compile and Link command variables
COMPILE = $(CC)
LINK = $(LD) 

INCLUDE = -I- -I../../MSL_Precompiled_Headers/Src 
INCLUDE += -I../../../MSL_C++/MSL_ARM/Include
INCLUDE += -I../../../MSL_C++/MSL_Common/Include
INCLUDE += -ir ../../../../msl/MSL_C

# Build ARM ABI compliant C libs if make specified with ABI=1
#
ifeq ($(ABI),1)
ABISPEC=-D_AEABI_PORTABILITY_LEVEL=1
else
ABISPEC=
endif

# Tiny IO Libs
#
ifeq ($(TINY),1)
TINYSPEC=-D_MSL_C_TINY_IO=1 -D_MSL_TINY_FILE_IO=1 -D_MSL_TESTING_TINY_IO=1
else
TINYSPEC=
endif


# Common build flags
#
CXFLAGS	= -warnings on,nocmdline -opt level=4,speed -inline level=8,bottomup -ipa file -noconstpool -char unsigned  -Cpp_exceptions on -str reuse  $(INCLUDE) -c $(ABISPEC) $(TINYSPEC)

# Target name definition and target specific build flags
#
T01 = MSLHeaders_NITRO_A_LE 
T01CFLAGS = -proc arm946e -little -nointerworking 
T01LFLAGS = -proc arm946e -little -nointerworking

T04 = MSLHeaders_NITRO_A_BE
T04CFLAGS = -proc arm946e -big -nointerworking 
T04LFLAGS = -proc arm946e -big -nointerworking

T08 = MSLHeaders_NITRO_T_LE 
T08CFLAGS = -proc arm946e -little -thumb -interworking 
T08LFLAGS = -proc arm946e -little -thumb -interworking

T12 = MSLHeaders_NITRO_T_BE 
T12CFLAGS = -proc arm946e -big -thumb -interworking 
T12LFLAGS = -proc arm946e -big -thumb -interworking


V4T = $(T01) $(T04) $(T08) $(T12)


# List of targets
#
TARGETS = $(V4T)
TARGETFILES = $(addprefix ../MSL_Precompiled_Headers/,$(addsuffix .mch,$(TARGETS))) 

# Define target specific variables (arm - thumb)
#
../MSL_Precompiled_Headers/$(addsuffix .mch,$(T01)) : CFLAGS=$(CXFLAGS) $(T01CFLAGS) 
../MSL_Precompiled_Headers/$(addsuffix .mch,$(T04)) : CFLAGS=$(CXFLAGS) $(T04CFLAGS) 
../MSL_Precompiled_Headers/$(addsuffix .mch,$(T08)) : CFLAGS=$(CXFLAGS) $(T08CFLAGS) 
../MSL_Precompiled_Headers/$(addsuffix .mch,$(T12)) : CFLAGS=$(CXFLAGS) $(T12CFLAGS) 

all : $(TARGETFILES)

$(TARGETFILES) : ../MSL_Precompiled_Headers/NITRO_A_MSL.pch++ ../../MSL_Precompiled_Headers/Src/MSLHeaders++.cp
	$(COMPILE) $(CFLAGS) ../MSL_Precompiled_Headers/NITRO_A_MSL.pch++

clean:
	rm -f ../MSL_Precompiled_Headers/*.mch
