install_sub = install_base / 'Mathlib'

libdir = 'lib'
if libver <= libvers['dsi/1.3']
  libdir = 'lib_dsi_1.3'
endif

readme = 'readme.txt'
if libver <= libvers['dsi/1.1p1']
  readme = 'readme_dsi_1.1p1.txt'
endif

# Not decompiling/building these libraries for now
install_subdir(libdir,
  install_dir: install_sub / 'lib',
  strip_directory: true)
install_data(readme,
  install_dir: install_sub,
  rename: 'readme.txt')
