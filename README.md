libvmod-utf8
============

How to install vmod_utf8 from source::

  git submodule init
  git submodule update
  ./autogen.sh && ./configure && make
  sudo make install

Now use it in your VCL file like so::

  import utf8;

  set req.http.normalized = utf8.transform(req.http.header, 0);


[![Join the chat at https://gitter.im/fgsch/libvmod-utf8](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/fgsch/libvmod-utf8?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)
[![Build Status](https://travis-ci.org/fgsch/libvmod-utf8.svg?branch=master)](https://travis-ci.org/fgsch/libvmod-utf8)
