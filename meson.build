project('libco', 'c',
    meson_version : '>=0.45.0',
    default_options : [
        'c_std=c11',
    ]
)

cfg = configuration_data()
cfg.set('LIBCO_MPROTECT', get_option('mprotect'))

cfg_h = configure_file(
    configuration : cfg,
    output : 'libco_config.h'
)

backend = get_option('impl')

if backend == 'auto'
    os = host_machine.system()
    arch = host_machine.cpu_family()

    if arch == 'x86'
        backend = 'x86'
    elif arch == 'x86_64'
        backend = 'amd64'
    elif os == 'windows'
        backend = 'fiber'
    elif arch == 'arm'
        backend = 'arm'
    elif arch == 'ppc' or arch == 'ppc64'
        backend = 'ppc'
    else
        backend = 'sjlj'
    endif
endif

libco = static_library('co',
    '@0@.c'.format(backend), cfg_h,
    install : false,
    build_by_default : not meson.is_subproject()
)

libco_dep = declare_dependency(
    link_with : libco,
    include_directories : include_directories('.')
)

message('Using the @0@ backend'.format(backend))
