install_sub = install_base / 'Mathlib'

if libver >= libvers['dsi/1.6sp1']
  libdir = 'lib'
elif libver >= libvers['dsi/1.1']
  libdir = 'lib_dsi_1.3'
else
  libdir = 'lib_ds_2.0_sp2p3'
endif

if libver >= libvers['dsi/1.2']
  readme = 'readme.txt'
else
  readme = 'readme_dsi_1.1p1.txt'
endif

# Not decompiling/building these libraries for now
install_subdir(libdir,
  install_dir: install_sub / 'lib',
  strip_directory: true)
install_data(readme,
  install_dir: install_sub,
  rename: 'readme.txt')
