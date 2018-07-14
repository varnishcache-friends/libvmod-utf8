libvmod-utf8
============

[![Build Status](https://travis-ci.org/fgsch/libvmod-utf8.svg?branch=oldstable)](https://travis-ci.org/fgsch/libvmod-utf8)

## About

A Varnish 4.1 and 5.x VMOD for Unicode normalization, case-folding,
and other operations for data in the UTF-8 encoding.

For Varnish 6.0 and master refer to the master and devel branches,
respectively.

## Requirements

To build this VMOD you will need:

* make
* a C compiler, e.g. GCC or clang
* pkg-config
* python-docutils or docutils in macOS [1]
* varnish-dev in Debian/Ubuntu, varnish-devel in CentOS/RedHat or
  varnish in macOS [1]

If you are building from Git, you will also need:

* autoconf
* automake
* libtool

In addition, to run the tests you will need:

* varnish

If varnish is installed in a non-standard prefix you will also need
to set `PKG_CONFIG_PATH` to the directory where **varnishapi.pc** is
located before running `autogen.sh` and `configure`.  For example:

```
export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig
```

## Installation

### From a tarball

To install this VMOD, run the following commands:

```
./configure
make
make check
sudo make install
```

The `make check` step is optional but it's good to know whether the
tests are passing on your platform.

### From the Git repository

To install from Git, clone this repository by running:

```
git clone --recursive https://github.com/fgsch/libvmod-utf8
```

And then run `./autogen.sh` followed by the instructions above for
installing from a tarball.

## Example

```
import utf8;

sub vcl_recv {
	# Case folding
	set req.url = utf8.transform(req.url, 1024);
}
```

## License

This VMOD is licensed under BSD license. See LICENSE for details.

### Note

1. Using Homebrew, https://github.com/Homebrew/brew/.
