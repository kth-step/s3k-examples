project('2partitions', 'c', 
  version : '1.0',
  default_options : [
    'warning_level=2', 
    'c_std=gnu11', 
    'optimization=s'])

elfs = [
  subproject('s3k').get_variable('elf'),
  subproject('app0').get_variable('elf'),
  subproject('app1').get_variable('elf'),
  ]

qemu_gen = find_program('../../scripts/qemu_gen.sh')
qemu = custom_target('qemu',
  output : 'qemu.sh',
  input : elfs ,
  command : [qemu_gen, '@OUTPUT@', '@INPUT@'],
  build_by_default: true,
  )

