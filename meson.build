project('mw-libraries', ['c', 'cpp'],
  meson_version: '>=1.2.0')
fs = import('fs')

proj_libdir = get_option('libdir') / 'metroskrew'
proj_datadir = get_option('datadir') / 'metroskrew'

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
libvers_compat = {
  'dsi/1.6sp2': 'dsi/1.6sp1',
  'dsi/1.3p1': 'dsi/1.3',
  'dsi/1.2p2': 'dsi/1.2',
  'dsi/1.2p1': 'dsi/1.2',
  'ds/2.0/sp2p4': 'ds/2.0/sp2p3',
  'ds/2.0/sp2p2': 'ds/2.0/sp2',
  'ds/2.0/sp1p7': 'ds/2.0/sp1p5',
  'ds/2.0/sp1p6': 'ds/2.0/sp1p5',
  'ds/2.0/sp1p1': 'ds/2.0/sp1',
  'ds/1.2/sp4p1': 'ds/1.2/sp4',
  'ds/1.2/sp3p2': 'ds/1.2/sp3',
  'ds/1.2/sp2p3': 'ds/1.2/sp2',
}

libver_dir = get_option('libver')
if libver_dir in libvers_compat
  libver_dir = libvers_compat[libver_dir]
endif
if libver_dir in libvers
  libver = libvers[libver_dir]
else
  error('Unknown libver:', libver)
endif

install_base = proj_libdir / 'sdk' / libver_dir

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
  error('Cannot build ds/2.0/sp1p5 yet!')
elif libver >= libvers['ds/2.0/sp1p2']
  mwccarm_ver = '3.0-126'
elif libver >= libvers['ds/2.0/sp1']
  mwccarm_ver = '3.0-123'
elif libver >= libvers['ds/2.0/p4']
  mwccarm_ver = '3.0-122'
elif libver >= libvers['ds/2.0/p2']
  mwccarm_ver = '3.0-118'
elif libver >= libvers['ds/2.0/base']
  mwccarm_ver = '3.0-114'
elif libver >= libvers['ds/1.2/sp4']
  mwccarm_ver = '2.0-87'
elif libver >= libvers['ds/1.2/sp3']
  mwccarm_ver = '2.0-84'
elif libver >= libvers['ds/1.2/sp2']
  mwccarm_ver = '2.0-79'
elif libver >= libvers['ds/1.2/base_b73']
  mwccarm_ver = '2.0-73'
elif libver >= libvers['ds/1.2/base']
  mwccarm_ver = '2.0-72'
endif

subdir('tools')

if libver >= libvers['ds/2.0/sp1p5']
  hdrconv_cmd = unix2dos_cmd
elif libver >= libvers['ds/2.0/base']
  hdrconv_cmd = dos2unix_cmd
else
  hdrconv_cmd = unix2dos_cmd
endif

args_base = [
  '-wrap:ver', mwccarm_ver,
  '-sym', 'off',
  '-opt', 'level=4,speed',
  '-Cpp_exceptions', 'off',
  '-iso_templates', 'on',
  libver >= libvers['ds/2.0/base']
    ? ['-ipa', 'file']
    : ['-flag', 'c99'],
  '-I-',
  libver_arg
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
args_strb = [
  '-include', 'PREFIX_NITRO_strb.h'
]
lib_variants = {
  'A_LE': args_a_le,
  'Ai_LE': args_ai_le,
  'T_LE': args_t_le
}
foreach var_name, var_args : lib_variants
  lib_variants += {var_name + '_PIC_PID': var_args + args_pic_pid}
endforeach
if libver <= libvers['ds/1.2/sp4']
  foreach var_name, var_args : lib_variants
    lib_variants += {var_name + '_strb': var_args + args_strb}
  endforeach
endif

NITROSDK_dep = declare_dependency(
  include_directories: 'NitroSDK/include')

if libver >= libvers['dsi/1.1']
  subdir('ARM_EABI_Support/msl/MSL_C')
  subdir('ARM_EABI_Support/msl/MSL_C++')
  subdir('ARM_EABI_Support/msl/MSL_Extras')
  subdir('ARM_EABI_Support/Runtime')
elif libver >= libvers['ds/2.0/base']
  subdir('ARM_EABI_Support_DS2.0/msl/MSL_C')
  subdir('ARM_EABI_Support_DS2.0/msl/MSL_C++')
  subdir('ARM_EABI_Support_DS2.0/msl/MSL_Extras')
  subdir('ARM_EABI_Support_DS2.0/Runtime')
else
  subdir('ARM_EABI_Support_DS1.2/msl/MSL_C')
  subdir('ARM_EABI_Support_DS1.2/msl/MSL_C++')
  subdir('ARM_EABI_Support_DS1.2/msl/MSL_Extras')
  subdir('ARM_EABI_Support_DS1.2/Runtime')
endif

subdir('ARM_EABI_Support/Mathlib')
subdir('ARM_EABI_Support/Profiler')
subdir('data')
