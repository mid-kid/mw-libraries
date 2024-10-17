install_sub = install_base / 'Runtime'

sources = [
  'Runtime_ARM/(Common_Source)/rt_div0.c',
  'Runtime_ARM/(Common_Source)/semihosted_console_io.c',
  'Runtime_ARM/(Common_Source)/setjmp.c',
  'Runtime_ARM/(Common_Source)/startup.c',
  '(RISC_Common)/CompressedNumbers.cpp',
  '(RISC_Common)/ExceptionHandler.cpp',
  '(Runtime_Common)/New.cpp',
  '(RISC_Common)/StaticInitializers.cpp',
  'Runtime_ARM/(Common_Source)/_rt_fp_status_addr.c',
  'Runtime_ARM/(Common_Source)/_rt_fp_env_addr.c',
  '(Runtime_Common)/vla_alloc.c',
  '(Runtime_Common)/cxxabi/cxxabi_alloc.cpp',
  '(Runtime_Common)/cxxabi/cxxabi_badeh.cpp',
  '(Runtime_Common)/cxxabi/cxxabi_onetimeinit.cpp',
  '(Runtime_Common)/cxxabi/cxxabi_ptmf.cpp',
  '(Runtime_Common)/cxxabi/cxxabi_rtti.cpp',
  '(Runtime_Common)/MWException.cpp',
  'Runtime_ARM/(Common_Source)/ExceptionHandlerTS.cpp',
  'Runtime_ARM/(Common_Source)/__NITRO_eabi_init.c',
  '(Runtime_Common)/cxxabi/cxxabi_clear.c'
]
sources_t = [
  'Runtime_ARM/(Common_Source)/rt_div0.c',
  'Runtime_ARM/(Common_Source)/semihosted_console_io.c',
  'Runtime_ARM/(Common_Source)/setjmp.c',
  'Runtime_ARM/(Common_Source)/startup.c',
  'Runtime_ARM/(Common_Source)/Thumb_interworking.c',
  '(RISC_Common)/CompressedNumbers.cpp',
  '(RISC_Common)/ExceptionHandler.cpp',
  '(Runtime_Common)/New.cpp',
  '(RISC_Common)/StaticInitializers.cpp',
  'Runtime_ARM/(Common_Source)/_rt_fp_status_addr.c',
  'Runtime_ARM/(Common_Source)/_rt_fp_env_addr.c',
  '(Runtime_Common)/vla_alloc.c',
  '(Runtime_Common)/cxxabi/cxxabi_alloc.cpp',
  '(Runtime_Common)/cxxabi/cxxabi_badeh.cpp',
  '(Runtime_Common)/cxxabi/cxxabi_onetimeinit.cpp',
  '(Runtime_Common)/cxxabi/cxxabi_ptmf.cpp',
  '(Runtime_Common)/cxxabi/cxxabi_rtti.cpp',
  '(Runtime_Common)/MWException.cpp',
  'Runtime_ARM/(Common_Source)/ExceptionHandlerTS.cpp',
  'Runtime_ARM/(Common_Source)/__NITRO_eabi_init.c',
  '(Runtime_Common)/cxxabi/cxxabi_clear.c'
]

dependencies = [
  MSL_C_NITRO_dep,
  MSL_CPP_NITRO_dep
]

include_dirs = [
  '(Runtime_Common)',
  '(Runtime_Common)/MWRuntime',
  '(Runtime_Common)/cxxabi',
  '(RISC_Common)',
  'Runtime_ARM/(Common_Source)',
  '../../NitroSDK/include'
]

args_ver = ['-DNO_RUNTIME_BASIC_TYPEINFO']
if libver <= libvers['dsi/1.2']
  args_ver = []
endif

args = [
  args_base,
  '-Cpp_exceptions', 'on',
  args_ver
]

NITRO_Runtime_libs = []
foreach var_suff, var_args : lib_variants
  var_sources = sources
  if var_suff.startswith('T_')
    var_sources = sources_t
  endif

  lib_in = static_library('NITRO_Runtime_' + var_suff, var_sources,
    c_args: [args, var_args],
    cpp_args: [args, var_args],
    dependencies: dependencies,
    include_directories: include_dirs,
    build_by_default: false,
    pic: false,
    name_prefix: '',
    name_suffix: 'a.in')

  NITRO_Runtime_libs += custom_target(
    input: lib_in,
    output: 'NITRO_Runtime_' + var_suff + '.a',
    command: [fixar, '@OUTPUT@', '@INPUT@', var_sources],
    install: true,
    install_dir: install_sub / 'Runtime_ARM/Runtime_NITRO/Lib')
endforeach

install_headers(
  'Runtime_ARM/Runtime_NITRO/Common_Includes/alloca.h',
  install_dir: install_sub / 'Runtime_ARM/Runtime_NITRO/Common_Includes')
