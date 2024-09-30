sources = [
  '(Runtime_Common)/vla_alloc.c',
  '(Runtime_Common)/cxxabi/cxxabi_clear.c',
  'Runtime_ARM/(Common_Source)/__NITRO_eabi_init.c',
  'Runtime_ARM/(Common_Source)/_rt_fp_env_addr.c',
  'Runtime_ARM/(Common_Source)/_rt_fp_status_addr.c',
  'Runtime_ARM/(Common_Source)/nitro_console_io.c',
  'Runtime_ARM/(Common_Source)/rt_div0.c',
  'Runtime_ARM/(Common_Source)/setjmp.c',
  'Runtime_ARM/(Common_Source)/startup.c',
  '(RISC_Common)/CompressedNumbers.cpp',
  '(RISC_Common)/ExceptionHandler.cpp',
  '(RISC_Common)/StaticInitializers.cpp',
  '(Runtime_Common)/MWException.cpp',
  '(Runtime_Common)/New.cpp',
  '(Runtime_Common)/cxxabi/cxxabi_alloc.cpp',
  '(Runtime_Common)/cxxabi/cxxabi_badeh.cpp',
  '(Runtime_Common)/cxxabi/cxxabi_onetimeinit.cpp',
  '(Runtime_Common)/cxxabi/cxxabi_ptmf.cpp',
  '(Runtime_Common)/cxxabi/cxxabi_rtti.cpp',
  'Runtime_ARM/(Common_Source)/aeabi_alloca.cpp',
  'Runtime_ARM/(Common_Source)/ExceptionHandlerTS.cpp'
]

include_dirs = [
  '../msl/MSL_C/MSL_Common/Include',
  '../msl/MSL_C/MSL_ARM/Include',
  '../msl/MSL_C++/MSL_Common/Include',
  '../msl/MSL_C++/MSL_ARM/Include',
  '../msl/MSL_Extras/MSL_Common/Include',
  '../Mathlib/lib',
  '(Runtime_Common)',
  '(Runtime_Common)/MWRuntime',
  '(Runtime_Common)/cxxabi',
  '(RISC_Common)',
  'Runtime_ARM/(Common_Source)',
  '../../NitroSDK/include'
]

args = [
  '-sym', 'off',
  '-opt', 'level=4,speed',
  '-inline', 'smart,bottomup',
  '-ipa', 'file',
  '-noconstpool',
  '-char', 'unsigned',
  '-Cpp_exceptions', 'on',
  '-str', 'reuse',
  '-I-',
  '-DNO_RUNTIME_BASIC_TYPEINFO',
  '-proc', 'arm946e',
  '-little',
  '-nointerworking'
]

lib = static_library('NITRO_Runtime_A_LE', sources,
  c_args: args,
  cpp_args: args,
  include_directories: include_dirs,
  build_by_default: false,
  pic: false,
  name_prefix: '',
  name_suffix: 'a.in')

custom_target(
  input: lib,
  output: 'NITRO_Runtime_A_LE.a',
  command: [fixar, '@OUTPUT@', '@INPUT@', sources],
  build_by_default: true)
