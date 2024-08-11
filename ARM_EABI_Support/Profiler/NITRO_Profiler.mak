LIBOUT := Lib
OBJDATA_ROOT := obj
TARGETS := ProfileLibrary_A_LE ProfileLibrary_Ai_LE

OBJ := \
	ProfilerCore.o \
	ProfilerARMMemory.o \
	ProfilerARMIO.o
vpath %.c Source

FLAGS := -warnings on,nocmdline
CFLAGS := $(FLAGS) -wrap:ver 4.0-1034 \
	-lang c++ -opt speed -Cpp_exceptions off -char signed \
	-DLITTLE_ENDIAN \
	-I- -ISource -Iinclude \
	-I../msl/MSL_C/MSL_ARM/Include \
	-I../msl/MSL_C/MSL_Common/Include \
	-I../msl/MSL_C++/MSL_ARM/Include \
	-I../msl/MSL_C++/MSL_Common/Include
LDFLAGS := $(FLAGS) -library

ifndef TARGET
.PHONY: all
all: $(TARGETS)

$(TARGETS):
	$(MAKE) -f NITRO_Profiler.mak TARGET=$@
else
OBJ := $(addprefix $(OBJDATA_ROOT)/$(TARGET)/,$(OBJ))

.PHONY: all
all: $(LIBOUT)/$(TARGET).a

$(LIBOUT)/$(TARGET).a: $(OBJ)
	mkdir -p $(LIBOUT); $(LD) $(LDFLAGS) -o $@ $^

$(OBJDATA_ROOT)/ProfileLibrary_Ai_LE/%.o: CFLAGS += -interworking
$(OBJDATA_ROOT)/$(TARGET)/ProfilerCore.o: CFLAGS += -wrap:hack01 0004

$(OBJDATA_ROOT)/$(TARGET)/%.o: %.c
	mkdir -p $(OBJDATA_ROOT)/$(TARGET); $(COMPILE.c) "$<" -o $@
	sed 's@\(Metrowerks C/C++ for ARM 4\.0\.0\)\.1034@\1.1032@g' -i $@

$(OBJDATA_ROOT)/$(TARGET)/%.o: %.s
	mkdir -p $(OBJDATA_ROOT)/$(TARGET); $(COMPILE.s) "$<" -o $@
endif
