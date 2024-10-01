project('mw-libraries', ['c', 'cpp'],
  meson_version: '>=1.2.0')

fixar = executable('fixar', 'fixar.c', c_args: ['-Wall', '-Wextra'], native: true)

install_base = get_option('libdir') / 'metroskrew/sdk/' + get_option('libver')

subdir('ARM_EABI_Support/Runtime')
