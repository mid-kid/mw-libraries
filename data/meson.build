args = [libver_dir, libver_dir + '/lib']
foreach ver_comp, ver : libvers_compat
  if ver != libver_dir
    continue
  endif
  args += [libver_dir, ver_comp + '/lib']
endforeach

custom_target(
  output: 'sdk',
  command: ['sdk.sh', '@OUTPUT@', args],
  install: true,
  install_dir: proj_datadir)
