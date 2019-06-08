project('fakesudo', 'cpp', version: '0.0.0', default_options: ['cpp_std=c++17'])

libfakesudo_sources = [
    'src/libfakesudo/environment.cpp',
    'src/libfakesudo/exec.cpp',
    'src/libfakesudo/parameters.cpp',
    'src/libfakesudo/user.cpp',
]

includes = [
    include_directories('include'),
]

libfakesudo_depends = [
    meson.get_compiler('cpp').find_library('dl'),
]

shared_library(
    'fakesudo',
    libfakesudo_sources,
    include_directories: includes,
    dependencies: libfakesudo_depends,
)
