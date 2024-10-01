install_sub = install_base / 'Runtime'

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
sources_t = [
  '(Runtime_Common)/vla_alloc.c',
  '(Runtime_Common)/cxxabi/cxxabi_clear.c',
  'Runtime_ARM/(Common_Source)/Thumb_interworking.c',
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
]

args_a_le = [
  '-proc', 'arm946e',
  '-little',
  '-nointerworking'
]
args_ai_le = [
  '-proc', 'arm946e',
  '-little',
  '-interworking'
]
args_t_le = [
  '-proc', 'arm946e',
  '-little',
  '-thumb',
  '-interworking'
]
args_a_le_pic_pid = [
  '-proc', 'arm946e',
  '-little',
  '-nointerworking',
  '-pic',
  '-pid'
]
args_ai_le_pic_pid = [
  '-proc', 'arm946e',
  '-little',
  '-interworking',
  '-pic',
  '-pid'
]
args_t_le_pic_pid = [
  '-proc', 'arm946e',
  '-little',
  '-thumb',
  '-interworking',
  '-pic',
  '-pid'
]

variants = {
  'A_LE': args_a_le,
  'Ai_LE': args_ai_le,
  'T_LE': args_t_le,
  'A_LE_PIC_PID': args_a_le_pic_pid,
  'Ai_LE_PIC_PID': args_ai_le_pic_pid,
  'T_LE_PIC_PID': args_t_le_pic_pid
}

NITRO_Runtime_libs = []

foreach var_suff, var_args : variants
  var_sources = sources
  if var_suff.startswith('T_')
    var_sources = sources_t
  endif

  lib_in = static_library('NITRO_Runtime_' + var_suff, var_sources,
    c_args: [args, var_args],
    cpp_args: [args, var_args],
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
