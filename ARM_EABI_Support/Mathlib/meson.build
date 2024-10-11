install_sub = install_base / 'Mathlib'

libdir = 'lib'
if libver == 'dsi/1.3' or libver == 'dsi/1.2'
  libdir = 'lib_dsi_1.3'
endif

# Not decompiling/building these libraries for now
install_subdir(libdir,
  install_dir: install_sub / 'lib',
  strip_directory: true)
install_data('readme.txt',
  install_dir: install_sub)
