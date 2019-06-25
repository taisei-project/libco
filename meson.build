project('libco', 'c',
    meson_version : '>=0.45.0',
    default_options : [
        'c_std=c11',
    ]
)

libco = static_library('co',
    'libco.c',
    install : false,
    build_by_default : not meson.is_subproject()
)

libco_dep = declare_dependency(
    link_with : libco,
    include_directories : include_directories('.')
)
