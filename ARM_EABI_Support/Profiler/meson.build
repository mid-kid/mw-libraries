install_sub = install_base / 'Profiler'

# This library is matched by running the following command on the library:
#     arm-none-eabi-strip -vgD -R .comment file.a
# The debug information can't easily be matched.

sources = [
  'Source/ProfilerCore.c',
  'Source/ProfilerARMMemory.c',
  'Source/ProfilerARMIO.c'
]

include_dirs = [
  'include',
  '../msl/MSL_C/MSL_ARM/Include',
  '../msl/MSL_C/MSL_Common/Include',
  '../msl/MSL_C++/MSL_ARM/Include',
  '../msl/MSL_C++/MSL_Common/Include'
]

args = [
  '-sym', 'off',
  '-wrap:ver', '4.0-1034',
  '-wrap:hack01', '0004',
  '-lang', 'c++',
  '-opt', 'level=0,speed',
  '-Cpp_exceptions', 'off',
  '-char', 'signed',
  '-DLITTLE_ENDIAN',
  '-I-'
]

args_a_le = [
  #'-proc', 'arm946e'
]
args_ai_le = [
  #'-proc', 'arm946e',
  '-interworking'
]
variants = {
  'A_LE': args_a_le,
  'Ai_LE': args_ai_le
}

ProfileLibrary_lib = []
foreach var_suff, var_args : variants
  var_sources = sources

  lib_in = static_library('ProfileLibrary_' + var_suff, var_sources,
    c_args: [args, var_args],
    cpp_args: [args, var_args],
    include_directories: include_dirs,
    build_by_default: false,
    pic: false,
    name_prefix: '',
    name_suffix: 'a.in')

  NITRO_Runtime_libs += custom_target(
    input: lib_in,
    output: 'ProfileLibrary_' + var_suff + '.a',
    command: [fixar, '@OUTPUT@', '@INPUT@', var_sources],
    install: true,
    install_dir: install_sub / 'Lib')
endforeach

install_headers(
  'include/Profiler.h',
  install_dir: install_sub / 'include')
