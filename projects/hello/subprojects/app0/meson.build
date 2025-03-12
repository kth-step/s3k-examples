project('app0', 'c',
  version : '0.1',
  default_options : [
    'warning_level=2', 
    'c_std=gnu11', 
    'optimization=s']
)


subdir('src')

subdir('platform' / get_option('platform'))

libserio_dep = subproject('libserio').get_variable('dep')
libs3k_dep = subproject('libs3k').get_variable('dep')

c_args = [
  '-DNPROC=' + get_option('nproc').to_string(),
  '-DNHART=' + get_option('nhart').to_string(),
  '-DNSLOT=' + get_option('nslot').to_string(),
  '-DNTICK=' + get_option('ntick').to_string(),
  '-DNPMP=' + get_option('npmp').to_string(),
  '-DNCHAN=' + get_option('nchan').to_string(),
  '-DNCAP=' + get_option('ncap').to_string(),
]

link_args = [
  '-nostdlib',
  '-nostartfiles',
  '-T', linker_script.full_path()
]

elf = executable('app0.elf', 
  sources : sources,
  c_args : c_args,
  link_args : link_args,
  dependencies : [libs3k_dep, libserio_dep]
)
