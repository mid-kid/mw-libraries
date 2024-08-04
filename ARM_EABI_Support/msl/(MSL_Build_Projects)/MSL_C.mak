# MSL_C.mak -- Generic makefile for building MSL libraries
#
# This makefile cannot be run alone, it is included by target makefiles
#
#------------- Generic Code Below This Line ---------------------------------
# Requires mkdir -p, rm, gnu make
#
MSL_C_ROOT = ../../../../msl


# Main target and default target, dependencies expand to 
# e.g. ../lib/<targetname>.a
#
ifndef TARGET
all: $(TARGETS)

$(TARGETS) :
	@echo "Making $@"
	make -f $(TARGET_MAK) TARGET=$@
endif


COBJECTS = $(addprefix $(OBJDATA_ROOT)/$(TARGET)/$(OBJOUT)/, $(COBJS))
CPPOBJECTS = $(addprefix $(OBJDATA_ROOT)/$(TARGET)/$(OBJOUT)/, $(CPPOBJS))
ASMOBJECTS = $(addprefix $(OBJDATA_ROOT)/$(TARGET)/$(OBJOUT)/, $(ASMOBJS))
CPOBJECTS = $(addprefix $(OBJDATA_ROOT)/$(TARGET)/$(OBJOUT)/, $(CPOBJS))


# Set up target lib object dependencies, e.g. ../Lib/<target>.a : <object dependencies>
#
$(addprefix $(LIBOUT)/, $(addsuffix $(LIBTYPE),$(TARGET))) : $(COBJECTS) $(CPPOBJECTS) $(ASMOBJECTS) $(CPOBJECTS)
	mkdir -p $(LIBOUT); $(LINK) $(LFLAGS) $(COBJECTS) $(CPPOBJECTS) $(ASMOBJECTS) $(CPOBJECTS) -o $@

# Set up object dependencies, e.g. CmdLine/<target>/obj/file.o : file.c
#
$(COBJECTS) : $(OBJDATA_ROOT)/$(TARGET)/$(OBJOUT)/%.o : %.c 
	mkdir -p $(OBJDATA_ROOT)/$(TARGET)/$(OBJOUT); $(COMPILE) $(CFLAGS) "$<" -o $@ 

$(CPPOBJECTS) : $(OBJDATA_ROOT)/$(TARGET)/$(OBJOUT)/%.o : %.cpp 
	mkdir -p $(OBJDATA_ROOT)/$(TARGET)/$(OBJOUT); $(COMPILE) $(CFLAGS) "$<" -o $@ 

$(ASMOBJECTS) : $(OBJDATA_ROOT)/$(TARGET)/$(OBJOUT)/%.o : %.s 
	mkdir -p $(OBJDATA_ROOT)/$(TARGET)/$(OBJOUT); $(ASSEMBLE) $(AFLAGS) "$<" -o $@ 

$(CPOBJECTS) : $(OBJDATA_ROOT)/$(TARGET)/$(OBJOUT)/%.o : %.cp 
	mkdir -p $(OBJDATA_ROOT)/$(TARGET)/$(OBJOUT); $(COMPILE) $(CFLAGS) "$<" -o $@ 

clean:
	# Remove generated data files, e.g. MSL_C.ARM_CmdLineData/* 
	#
	-rm -rf $(OBJDATA_ROOT)

	# Remove library files, e.g. ../Lib/*
	#
	-rm -f $(LIBOUT)/*

cleanobj:
	# Leave the library files intact,  clean up the object files
	#
	-rm -rf $(COBJECTS) $(CPPOBJECTS) $(ASMOBJECTS)
