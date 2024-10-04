project('mw-libraries', ['c', 'cpp'],
  meson_version: '>=1.2.0')

fixar = executable('fixar', 'fixar.c', c_args: ['-Wall', '-Wextra'], native: true)

install_base = get_option('libdir') / 'metroskrew/sdk/' + get_option('libver')

args_base = [
  '-sym', 'off',
  '-opt', 'level=4,speed',
  '-ipa', 'file',
  '-Cpp_exceptions', 'off',
  '-I-'
]

args_a_le = [
  '-proc', 'arm946e',
]
args_ai_le = [
  '-proc', 'arm946e',
  '-interworking'
]
args_t_le = [
  '-proc', 'arm946e',
  '-thumb',
  '-interworking'
]
args_pic_pid = [
  '-pic',
  '-pid'
]
lib_variants = {
  'A_LE': args_a_le,
  'Ai_LE': args_ai_le,
  'T_LE': args_t_le,
  'A_LE_PIC_PID': [args_a_le, args_pic_pid],
  'Ai_LE_PIC_PID': [args_ai_le, args_pic_pid],
  'T_LE_PIC_PID': [args_t_le, args_pic_pid]
}

subdir('ARM_EABI_Support/msl/MSL_C')
subdir('ARM_EABI_Support/msl/MSL_C++')
subdir('ARM_EABI_Support/msl/MSL_Extras')
subdir('ARM_EABI_Support/Mathlib')
subdir('ARM_EABI_Support/Runtime')
subdir('ARM_EABI_Support/Profiler')
