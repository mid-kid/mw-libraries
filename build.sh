#!/bin/sh
set -e

build="$PWD/build"
mkdir -p build

export LC_COLLATE=C
export PATH="$PWD/metroskrew/bin:$PATH"
export MAKEFLAGS="${MAKEFLAGS:--j$(nproc)}"

_make() {
    make \
        CC=mwccarm LD=mwldarm AS=mwasmarm \
        CWINSTALL="$PWD" \
        NITROSDK_ROOT="$PWD/NitroSDK" \
        V4T='$(T01) $(T02) $(T03) $(T07) $(T08) $(T09)' \
        "$@"
}

# Clean out the original libraries
rm -rf ARM_EABI_Support/Runtime/Runtime_ARM/Runtime_NITRO/Lib
rm -rf ARM_EABI_Support/msl/MSL_C++/MSL_ARM/Lib
rm -rf ARM_EABI_Support/msl/MSL_C/MSL_ARM/Lib
rm -rf ARM_EABI_Support/msl/MSL_Extras/MSL_ARM/Lib
rm -rf ARM_EABI_Support/Profiler/Lib
test "$1" = clean && exit

_make -C ARM_EABI_Support/msl/MSL_C/MSL_ARM/Project \
    -f MSL_C.NITRO.mak \
    OBJDATA_ROOT="$build/MSL_C.ARM_CmdLineData"

_make -C ARM_EABI_Support/msl/MSL_C++/MSL_ARM/Project \
    -f MSL_C++.NITRO.mak \
    OBJDATA_ROOT="$build/MSL_C++.ARM_CmdLineData"

_make -C ARM_EABI_Support/msl/MSL_Extras/MSL_ARM/Project \
    -f MSL_Extras.NITRO.mak \
    OBJDATA_ROOT="$build/MSL_Extras.ARM_CmdLineData"

_make -C ARM_EABI_Support/Runtime/Runtime_ARM/Runtime_NITRO/\(Projects\) \
    -f NITRO_Runtime.mak \
    OBJDATA_ROOT="$build/Runtime_ARM_CmdLineData"

_make -C ARM_EABI_Support/Profiler \
    -f NITRO_Profiler.mak \
    OBJDATA_ROOT="$build/Profiler_ARM_CmdLineData"

_make -C ARM_EABI_Support/Profiler \
    -f NITRO_Profiler.mak \
    OBJDATA_ROOT="$build/Profiler_ARM_CmdLineData"
