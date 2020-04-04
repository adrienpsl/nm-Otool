#!/usr/bin/env bash

# test with all file in bin
nm -a /usr/bin/du > real_nm
./cmake-build-debug/nm_otool /usr/bin/du > my_nm

diff real_nm my_nm