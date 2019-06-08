# Fakesudo
A small library to fake root privilieges through the usage of `LD_PRELOAD`.

Apart from simply replacing `get(e)uid` functions, some work is also done to prevent
this library from being un-LD_PRELOADed by functions like `setenv` or `execve`. Current
implementation is far from being perfect but... it kinda works

## Building and running
Prerequisites:

- [Meson build system](https://mesonbuild.com) and [Ninja](https://ninja-build.org/)
- A Linux system (other POSIX systems might work, but it is not guaranteed)
- A C++ compiler

Building:

```sh
meson setup 'build'
cd 'build'
ninja
```

Running a fake-sudoed program:

```sh
LD_PRELOAD=./libfakesudo.so LIBFAKESUDO_UID=<faked uid> <command>
```

or

```sh
sudo -u <faked username> <command>
```

**WARNING**: Custom `/usr/bin/sudo` is provided by this program, which might conflict with system-provided
`sudo` implementation. Install (a) to any location if `sudo` is not provided by the system (e.g.
Arch on Termux) or (b) to location like `~/bin` or `/usr/local/bin` if you want to avoid conflicts.

## License
Unlicense (Public Domain). See LICENSE file for details
