project('fakesudo', 'cpp', version: '0.0.0', default_options: ['cpp_std=c++17'])

# ============= #
# Configuration #
# ============= #

config = configuration_data()
config.set('LIBFAKESUDO_FAKE_CHOWN', get_option('enable-fake-chown'))

configure_file(
    input: 'config.hpp.in',
    output: 'config.hpp',
    configuration: config,
)

# ================================== #
# Sources, includes and dependencies #
# ================================== #

libfakesudo_sources = [
    'src/libfakesudo/chown.cpp',
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

# ======= #
# Targets #
# ======= #

shared_library(
    'fakesudo',
    libfakesudo_sources,
    include_directories: includes,
    dependencies: libfakesudo_depends,
)
