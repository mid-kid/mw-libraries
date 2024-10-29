headers = [
  'ctime.in'
]

foreach header : headers
  headers_gen += custom_target(
    input: header,
    output: '@BASENAME@',
    command: m4_cmd,
    capture: true)
endforeach
