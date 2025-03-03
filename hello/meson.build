project('hello_world', 'c', 
  version : '1.0',
  default_options : [
    'warning_level=2', 
    'c_std=gnu11', 
    'optimization=s'])

s3k = subproject('s3k')
app0 = subproject('app0')

hexes = [
  s3k.get_variable('hex'),
  app0.get_variable('hex'),
  ]

hex = custom_target(
  'hello.hex',
  input : hexes,
  output : 'hello.hex',
  command : [
    find_program('srec_cat'), 
    '-O', '@OUTPUT@', '-Intel',
    '@INPUT0@', '-Intel',
    '@INPUT1@', '-Intel',
  ],
  build_by_default : true
)
