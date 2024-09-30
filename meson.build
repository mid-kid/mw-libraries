project('mw-libraries', ['c', 'cpp'],
  meson_version: '>=1.2.0')

fixar = executable('fixar', 'fixar.c', c_args: ['-Wall', '-Wextra'], native: true)

subdir('ARM_EABI_Support/Runtime')
