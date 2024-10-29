install_sub = install_base / 'Mathlib'

if libver >= libvers['dsi/1.6sp1']
  libdir = 'lib'
elif libver >= libvers['dsi/1.1']
  libdir = 'lib_dsi_1.3'
elif libver >= libvers['ds/2.0/sp1p5']
  libdir = 'lib_ds_2.0_sp2p3'
elif libver >= libvers['ds/2.0/sp1']
  libdir = 'lib_ds_2.0_sp1p2'
elif libver >= libvers['ds/2.0/base']
  libdir = 'lib_ds_2.0_p4'
elif libver >= libvers['ds/1.2/sp2']
  libdir = 'lib_ds_1.2_sp4'
elif libver >= libvers['ds/1.2/base_b73']
  libdir = 'lib_ds_1.2_base_b73'
else
  libdir = 'lib_ds_1.2_base'
endif

if libver >= libvers['dsi/1.2']
  readme = 'readme.txt'
elif libver >= libvers['ds/2.0/sp1p5']
  readme = 'readme_dsi_1.1p1.txt'
elif libver >= libvers['ds/2.0/base']
  readme = 'readme_ds_2.0_sp1p2.txt'
elif libver >= libvers['ds/1.2/sp2']
  readme = 'readme_ds_1.2_sp4.txt'
else
  readme = 'readme_ds_1.2_base_b73.txt'
endif

# Not decompiling/building these libraries for now
install_subdir(libdir,
  install_dir: install_sub / 'lib',
  strip_directory: true)
install_data(readme,
  install_dir: install_sub,
  rename: 'readme.txt')
