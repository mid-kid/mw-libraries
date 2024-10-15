install_sub = install_base / 'msl/MSL_C++'

sources = [
  'MSL_Common/Src/MSLstring.cpp',
  'MSL_Common/Src/complex.cpp',
  'MSL_Common/Src/ios.cpp',
  'MSL_Common/Src/iostream.cpp',
  'MSL_Common/Src/locale.cpp',
  'MSL_Common/Src/msl_condition.cpp',
  'MSL_Common/Src/msl_mutex.cpp',
  'MSL_Common/Src/msl_thread.cpp',
  'MSL_Common/Src/msl_time.cpp',
  'MSL_Common/Src/strstream.cpp'
]

headers_gen = []
subdir('MSL_Common/Include')

MSL_CPP_NITRO_dep = declare_dependency(
  sources: headers_gen,
  include_directories: [
    'MSL_Common/Include',
    'MSL_ARM/Include'
  ]
)

dependencies = [
  MSL_C_NITRO_dep,
  MSL_CPP_NITRO_dep
]

include_dirs = [
  '../MSL_C/MSL_Common/Include',
  '../MSL_C/MSL_ARM/Include'
]

args = [
  args_base,
  '-Cpp_exceptions', 'on'
]

MSL_CPP_NITRO_libs = []
foreach var_suff, var_args : lib_variants
  var_sources = sources

  lib_in = static_library('MSL_CPP_NITRO_' + var_suff, var_sources,
    c_args: [args, var_args],
    cpp_args: [args, var_args],
    dependencies: dependencies,
    include_directories: include_dirs,
    build_by_default: false,
    pic: false,
    name_prefix: '',
    name_suffix: 'a.in')

  MSL_CPP_NITRO_libs += custom_target(
    input: lib_in,
    output: 'MSL_CPP_NITRO_' + var_suff + '.a',
    command: [fixar, '@OUTPUT@', '@INPUT@', var_sources],
    install: true,
    install_dir: install_sub / 'MSL_ARM/Lib')
endforeach

install_headers(
  'MSL_ARM/Include/mslconfig_ARM',
  install_dir: install_sub / 'MSL_ARM/Include')

install_headers(
  'MSL_Common/Include/MSLstring.h',
  'MSL_Common/Include/RefCountedPtrArray.h',
  'MSL_Common/Include/algorithm',
  'MSL_Common/Include/algorithm.h',
  'MSL_Common/Include/array',
  'MSL_Common/Include/bind',
  'MSL_Common/Include/bitset',
  'MSL_Common/Include/bitset.h',
  'MSL_Common/Include/bitvector',
  'MSL_Common/Include/cdeque',
  'MSL_Common/Include/cdeque.h',
  'MSL_Common/Include/char_traits',
  'MSL_Common/Include/codecvt',
  'MSL_Common/Include/codecvt_byname',
  'MSL_Common/Include/codecvt_ext',
  'MSL_Common/Include/collate',
  'MSL_Common/Include/complex',
  'MSL_Common/Include/ctype',
  'MSL_Common/Include/ctype_byname',
  'MSL_Common/Include/deque',
  'MSL_Common/Include/deque.h',
  'MSL_Common/Include/exception',
  'MSL_Common/Include/exception.h',
  'MSL_Common/Include/fstream',
  'MSL_Common/Include/fstream.h',
  'MSL_Common/Include/functional',
  'MSL_Common/Include/functional.h',
  'MSL_Common/Include/functional_ext',
  'MSL_Common/Include/functional_ext.h',
  'MSL_Common/Include/hash_fun',
  'MSL_Common/Include/hash_fun.h',
  'MSL_Common/Include/hash_map',
  'MSL_Common/Include/hash_map.h',
  'MSL_Common/Include/hash_set',
  'MSL_Common/Include/hash_set.h',
  'MSL_Common/Include/hash_table',
  'MSL_Common/Include/iomanip',
  'MSL_Common/Include/iomanip.h',
  'MSL_Common/Include/ios',
  'MSL_Common/Include/ios.h',
  'MSL_Common/Include/iosfwd',
  'MSL_Common/Include/iosfwd.h',
  'MSL_Common/Include/iostream',
  'MSL_Common/Include/iostream.h',
  'MSL_Common/Include/istream',
  'MSL_Common/Include/istream.h',
  'MSL_Common/Include/iterator.h',
  'MSL_Common/Include/limits',
  'MSL_Common/Include/list',
  'MSL_Common/Include/list.h',
  'MSL_Common/Include/locale',
  'MSL_Common/Include/localeimp',
  'MSL_Common/Include/map',
  'MSL_Common/Include/map.h',
  'MSL_Common/Include/memory',
  'MSL_Common/Include/messagefacet',
  'MSL_Common/Include/moneyfacet',
  'MSL_Common/Include/msl_bufferedbuf',
  'MSL_Common/Include/msl_c_filebuf',
  'MSL_Common/Include/msl_condition',
  'MSL_Common/Include/msl_consolebuf',
  'MSL_Common/Include/msl_int_limits',
  'MSL_Common/Include/msl_mutex',
  'MSL_Common/Include/msl_posixbuf',
  'MSL_Common/Include/msl_smart_pointers',
  'MSL_Common/Include/msl_thread',
  'MSL_Common/Include/msl_time',
  'MSL_Common/Include/mslconfig',
  'MSL_Common/Include/mslconfig_gcc',
  'MSL_Common/Include/new',
  'MSL_Common/Include/new.h',
  'MSL_Common/Include/niostream',
  'MSL_Common/Include/numeric',
  'MSL_Common/Include/numeric.h',
  'MSL_Common/Include/numfacet',
  'MSL_Common/Include/numpunct_byname',
  'MSL_Common/Include/ostream',
  'MSL_Common/Include/ostream.h',
  'MSL_Common/Include/queue',
  'MSL_Common/Include/queue.h',
  'MSL_Common/Include/set',
  'MSL_Common/Include/set.h',
  'MSL_Common/Include/slist',
  'MSL_Common/Include/slist.h',
  'MSL_Common/Include/sstream',
  'MSL_Common/Include/sstream.h',
  'MSL_Common/Include/stack',
  'MSL_Common/Include/stack.h',
  'MSL_Common/Include/stdexcept',
  'MSL_Common/Include/stdexcept.h',
  'MSL_Common/Include/streambuf',
  'MSL_Common/Include/streambuf.h',
  'MSL_Common/Include/string',
  'MSL_Common/Include/stringfwd',
  'MSL_Common/Include/stringfwd.h',
  'MSL_Common/Include/strstream',
  'MSL_Common/Include/strstream.h',
  'MSL_Common/Include/timefacet',
  'MSL_Common/Include/tree',
  'MSL_Common/Include/tuple',
  'MSL_Common/Include/tupleio',
  'MSL_Common/Include/type_traits',
  'MSL_Common/Include/typeinfo',
  'MSL_Common/Include/typeinfo.h',
  'MSL_Common/Include/utility',
  'MSL_Common/Include/utility.h',
  'MSL_Common/Include/valarray',
  'MSL_Common/Include/valarray.h',
  'MSL_Common/Include/vector',
  'MSL_Common/Include/vector.h',
  'MSL_Common/Include/wiostream',
  install_dir: install_sub / 'MSL_Common/Include')
