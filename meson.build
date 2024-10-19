project('mw-libraries', ['c', 'cpp'],
  meson_version: '>=1.2.0')

m4 = find_program('m4')

fixar = executable('fixar', 'fixar.c', c_args: ['-Wall', '-Wextra'], native: true)

libver = 17
libvers = {
  'dsi/1.6sp1': 17,
  'dsi/1.3': 16,
  'dsi/1.2': 15,
  'dsi/1.1p1': 14,
  'dsi/1.1': 13,
  'ds/2.0/sp2p3': 12,
  'ds/2.0/sp2': 11,
  'ds/2.0/sp1p5': 10,
  'ds/2.0/sp1p2': 9,
  'ds/2.0/sp1': 8,
  'ds/2.0/p4': 7,
  'ds/2.0/p2': 6,
  'ds/2.0/base': 5,
  'ds/1.2/sp4': 4,
  'ds/1.2/sp3': 3,
  'ds/1.2/sp2': 2,
  'ds/1.2/base_b73': 1,
  'ds/1.2/base': 0
}
libver_dir = get_option('libver')
if libver_dir in libvers
  libver = libvers[libver_dir]
endif

libver_defs = ['-DLIBVER=' + libver.to_string()]
foreach name, vers : libvers
  libver_defs += [
    '-DLIBVER_' + name.replace('/', '_').replace('.', '_') +
    '=' + vers.to_string()]
endforeach

m4_cmd = [m4, libver_defs, '@INPUT@']
unix2dos_cmd = ['sh', '-c',
  'sed "$(echo cy8NJC8vO3MvJC8NLw | base64 -d)" < "$1" > "$2"; '
  + 'if [ -n "$(tail -c -1 "$1")" ]; then '
  + 'sed -e "$(echo JHMvDSQvLw | base64 -d)" -i "$2"; '
  + 'fi',
  '--', '@INPUT@', '@OUTPUT@']
dos2unix_cmd = ['sh', '-c',
  'sed "$(echo cy8NJC8v | base64 -d)" < "$1" > "$2"',
  '--', '@INPUT@', '@OUTPUT@']

install_base = get_option('libdir') / 'metroskrew/sdk/' + libver_dir

if libver >= libvers['dsi/1.6sp1']
  mwccarm_ver = '4.0-1051'
elif libver >= libvers['dsi/1.3']
  mwccarm_ver = '4.0-1034'
elif libver >= libvers['dsi/1.2']
  mwccarm_ver = '4.0-1026'
elif libver >= libvers['dsi/1.1p1']
  mwccarm_ver = '4.0-1024'
elif libver >= libvers['dsi/1.1']
  mwccarm_ver = '4.0-1018'
elif libver >= libvers['ds/2.0/sp2p3']
  mwccarm_ver = '3.0-138'
elif libver >= libvers['ds/2.0/sp2']
  mwccarm_ver = '3.0-136'
elif libver >= libvers['ds/2.0/sp1p5']
  #mwccarm_ver = '3.0-127'  # Missing compiler
  #mwccarm_ver = '3.0-126'  # Close match but not complete
elif libver >= libvers['ds/2.0/sp1p2']
  mwccarm_ver = '3.0-126'
elif libver >= libvers['ds/2.0/sp1']
  mwccarm_ver = '3.0-123'
endif

if libver >= libvers['ds/2.0/sp1p5']
  hdrconv_cmd = unix2dos_cmd
else
  hdrconv_cmd = dos2unix_cmd
endif

args_base = [
  '-wrap:ver', mwccarm_ver,
  '-sym', 'off',
  '-opt', 'level=4,speed',
  '-ipa', 'file',
  '-Cpp_exceptions', 'off',
  '-iso_templates', 'on',
  '-I-',
  libver_defs
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
  libver >= libvers['dsi/1.1p1'] ? '-interworking' : []
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

NITROSDK_dep = declare_dependency(
  include_directories: 'NitroSDK/include')

if libver >= libvers['dsi/1.1']
  subdir('ARM_EABI_Support/msl/MSL_C')
  subdir('ARM_EABI_Support/msl/MSL_C++')
  subdir('ARM_EABI_Support/msl/MSL_Extras')
  subdir('ARM_EABI_Support/Runtime')
else
  subdir('ARM_EABI_Support_DS2.0SP2/msl/MSL_C')
  subdir('ARM_EABI_Support_DS2.0SP2/msl/MSL_C++')
  subdir('ARM_EABI_Support_DS2.0SP2/msl/MSL_Extras')
  subdir('ARM_EABI_Support_DS2.0SP2/Runtime')
endif

subdir('ARM_EABI_Support/Mathlib')
subdir('ARM_EABI_Support/Profiler')
