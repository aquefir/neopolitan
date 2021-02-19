#!/bin/sh
# -*- coding: utf-8 -*-

echo -n 'Removing the Cosmopolitan downloads and binaries... ' >/dev/stderr;
rm -f common/build/cosmo.zip;
rm -rf common/build/cosmo;
echo 'done.' >/dev/stderr;

exit 0;
