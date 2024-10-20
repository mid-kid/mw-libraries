install_sub = install_base / 'Runtime'

sources_1 = [
  '(Sources)/ARM_Specific_Sources/ExceptionHandlerTS.cpp',
  '(Sources)/ARM_Specific_Sources/rt_div0.c',
  '(Sources)/ARM_Specific_Sources/semihosted_console_io.c',
  '(Sources)/ARM_Specific_Sources/setjmp.c',
  '(Sources)/ARM_Specific_Sources/startup.c'
]
sources_2 = [
  '(Sources)/RISC_Common_Sources/CompressedNumbers.cpp',
  '(Sources)/RISC_Common_Sources/CPlusLib.cpp',
  '(Sources)/RISC_Common_Sources/ExceptionHandler.cpp',
  '(Sources)/RISC_Common_Sources/NewDelete.cpp',
  '(Sources)/RISC_Common_Sources/StaticInitializers.cpp',
  '(Sources)/Common_Sources/NMWException.cpp',
  '(Sources)/ARM_Specific_Sources/_rt_fp_status_addr.c',
  '(Sources)/ARM_Specific_Sources/_rt_fp_env_addr.c',
  '(Sources)/ARM_Specific_Sources/vla_alloc.c',
  '(Sources)/Common_Sources/cxxabi_alloc.cpp',
  '(Sources)/Common_Sources/cxxabi_badeh.cpp',
  '(Sources)/Common_Sources/cxxabi_onetimeinit.cpp',
  '(Sources)/Common_Sources/cxxabi_ptmf.cpp',
  '(Sources)/Common_Sources/cxxabi_rtti.cpp'
]

sources = [
  '(Sources)/ARM_Specific_Sources/__NITRO_eabi_init.c',
  sources_1,
  sources_2
]
sources_t = [
  '(Sources)/ARM_Specific_Sources/__NITRO_eabi_init.c',
  sources_1,
  '(Sources)/ARM_Specific_Sources/Thumb_interworking.c',
  sources_2
]
sources_strb = [
  sources_1,
  sources_2,
  '(Sources)/ARM_Specific_Sources/__NITRO_eabi_init.c'
]
sources_t_strb = [
  sources_1,
  '(Sources)/ARM_Specific_Sources/Thumb_interworking.c',
  sources_2,
  '(Sources)/ARM_Specific_Sources/__NITRO_eabi_init.c'
]

dependencies = [
  MSL_C_NITRO_dep,
  MSL_CPP_NITRO_dep,
  NITROSDK_dep
]

include_dirs = [
  '(Sources)/Common_Sources',
  '(Sources)/RISC_Common_Sources',
  '(Sources)/ARM_Specific_Sources',
  '../msl/MSL_Extras/MSL_Common/Include'
]

args = [
  args_base,
  '-Cpp_exceptions', 'on',
]

NITRO_Runtime_libs = []
foreach var_suff, var_args : lib_variants
  var_sources = sources
  if var_suff.startswith('T_')
    if var_suff.endswith('_strb')
      var_sources = sources_t_strb
    else
      var_sources = sources_t
    endif
  elif var_suff.endswith('_strb')
    var_sources = sources_strb
  endif

  lib_in = static_library('NITRO_Runtime_' + var_suff, var_sources,
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
    output: 'NITRO_Runtime_' + var_suff + '.a',
    command: [fixar, '@OUTPUT@', '@INPUT@', var_sources],
    install: true,
    install_dir: install_sub / 'Lib')
endforeach

headers = [
]

headers_ins = []
foreach header : headers
  headers_ins += [[fs.parent(header), header]]
endforeach

foreach hdr : headers_ins + headers_gen_ins
  custom_target(
    input: hdr[1],
    output: '@PLAINNAME@',
    command: hdrconv_cmd,
    install: true,
    install_dir: install_sub / hdr[0])
endforeach
