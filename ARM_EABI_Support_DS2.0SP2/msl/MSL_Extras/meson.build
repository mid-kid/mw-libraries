install_sub = install_base / 'msl/MSL_Extras'

sources = [
  'MSL_Common/Src/extras.c'
]

dependencies = [
  MSL_C_NITRO_dep
]

include_dirs = [
  'MSL_Common/Include',
  'MSL_ARM/Include'
]

args = [
  args_base,
  '-include', 'PREFIX_NITRO.h'
]

MSL_Extras_NITRO_libs = []
foreach var_suff, var_args : lib_variants
  var_sources = sources

  lib_in = static_library('MSL_Extras_NITRO_' + var_suff, var_sources,
    c_args: [args, var_args],
    cpp_args: [args, var_args],
    dependencies: dependencies,
    include_directories: include_dirs,
    implicit_include_directories: false,
    build_by_default: false,
    pic: false,
    name_prefix: '',
    name_suffix: 'a.in')

  MSL_Extras_NITRO_libs += custom_target(
    input: lib_in,
    output: 'MSL_Extras_NITRO_' + var_suff + '.a',
    command: [fixar, '@OUTPUT@', '@INPUT@', var_sources],
    install: true,
    install_dir: install_sub / 'MSL_ARM/Lib')
endforeach

headers = [
  ['MSL_ARM/Include', 'extras.ARM.h'],
  ['MSL_ARM/Include', 'utime.ARM.h'],
  ['MSL_Common/Include', 'dirent.h'],
  ['MSL_Common/Include', 'extras.h'],
  ['MSL_Common/Include', 'extras_io.h'],
  ['MSL_Common/Include', 'extras_malloc.h'],
  ['MSL_Common/Include', 'extras_stdlib.h'],
  ['MSL_Common/Include', 'extras_string.h'],
  ['MSL_Common/Include', 'extras_time.h'],
  ['MSL_Common/Include', 'extras_wchar.h'],
  ['MSL_Common/Include', 'fcntl.h'],
  ['MSL_Common/Include', 'unistd.h'],
  ['MSL_Common/Include', 'unistd_api.h'],
  ['MSL_Common/Include', 'unix.h'],
  ['MSL_Common/Include', 'utime.h'],
  ['MSL_Common/Include/sys', 'stat.h'],
  ['MSL_Common/Include/sys', 'timeb.h'],
  ['MSL_Common/Include/sys', 'utsname.h']
]

foreach hdr : headers
  custom_target(
    input: hdr[0] / hdr[1],
    output: '@PLAINNAME@',
    command: hdrconv_cmd,
    install: true,
    install_dir: install_sub / hdr[0])
endforeach
