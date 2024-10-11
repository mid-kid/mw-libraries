install_hdr = install_sub / 'MSL_Common/Include'

headers = {
  'string.h.in': 'string.h'
}

foreach src, out : headers
  headers_gen += custom_target(
    input: src,
    output: out,
    command: m4_cmd,
    capture: true,
    install: true,
    install_dir: install_hdr)
endforeach
