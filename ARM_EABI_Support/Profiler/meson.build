install_sub = install_base / 'Profiler'

# This library is matched by running the following command on the library:
#     arm-none-eabi-strip -vgD -R .comment file.a
# The debug information can't easily be matched.

sources = [
  'Source/ProfilerCore.c',
  'Source/ProfilerARMMemory.c',
  'Source/ProfilerARMIO.c'
]

dependencies = [
  MSL_C_NITRO_dep,
  MSL_CPP_NITRO_dep
]

include_dirs = [
  'include'
]

if libver >= libvers['dsi/1.3']
  wrap_ver = '4.0-1034'
  wrap_hack01 = '0004'
elif libver >= libvers['dsi/1.1']
  wrap_ver = '4.0-1018'
  wrap_hack01 = '0'
else
  wrap_ver = '3.0-114'
  wrap_hack01 = '0014'
endif

args = [
  '-wrap:ver', wrap_ver,
  '-wrap:hack01', wrap_hack01,
  '-lang', 'c++',
  '-sym', 'off',
  '-opt', 'level=0,speed',
  '-Cpp_exceptions', 'off',
  '-warnings', 'off',
  '-char', 'signed',
  '-I-',
  '-DLITTLE_ENDIAN',
  libver_defs
]

args_a_le = [
  '-proc', 'arm7tdmi'
]
args_ai_le = [
  '-proc', 'arm7tdmi',
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
    dependencies: dependencies,
    include_directories: include_dirs,
    implicit_include_directories: false,
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

headers = [
  ['include', 'Profiler.h'],
]

if libver >= libvers['dsi/1.1']
  cmd = unix2dos_cmd
elif libver >= libvers['ds/2.0/p4']
  cmd = dos2unix_cmd
else
  cmd = unix2dos_cmd
endif

foreach hdr : headers
  custom_target(
    input: hdr[0] / hdr[1],
    output: '@PLAINNAME@',
    command: cmd,
    install: true,
    install_dir: install_sub / hdr[0])
endforeach
