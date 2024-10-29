libver_cfg = {'LIBVER': libver.to_string()}
foreach name, vers : libvers
  libver_cfg += {
    'LIBVER_' + name.replace('/', '_').replace('.', '_'):
    vers.to_string()}
endforeach

libver_hdr = configure_file(
  input: 'libver.h.in',
  output: '@BASENAME@',
  configuration: libver_cfg)
libver_hdr_m4 = configure_file(
  input: 'libver.m4.in',
  output: '@BASENAME@',
  configuration: libver_cfg)

libver_arg = [
  '-I' + meson.current_build_dir(),
  '-include', 'libver.h'
]

m4 = find_program('m4')

m4_cmd = [m4, libver_hdr_m4, '@INPUT@']
unix2dos_cmd = ['sh', '-c',
  'sed "$(echo cy8NJC8vO3MvJC8NLw | base64 -d)" < "$1" > "$2"; '
  + 'if [ -n "$(tail -c -1 "$1")" ]; then '
  + 'sed -e "$(echo JHMvDSQvLw | base64 -d)" -i "$2"; '
  + 'fi',
  '--', '@INPUT@', '@OUTPUT@']
dos2unix_cmd = ['sh', '-c',
  'sed "$(echo cy8NJC8v | base64 -d)" < "$1" > "$2"',
  '--', '@INPUT@', '@OUTPUT@']

fixar = executable('fixar', 'fixar.c', c_args: ['-Wall', '-Wextra'], native: true)
