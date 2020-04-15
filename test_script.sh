#!/usr/bin/env bash

## test with all file in bin
##
rm -fr test
mkdir test
##
for file in /usr/bin/*; do
  nm -a "$file" > real_nm 2>&1
  ./cmake-build-debug/nm_otool "$file" > my_nm 2>&1
  res=$(diff real_nm my_nm)
  file_res=$(echo "$file" | sed -e "s/^\/usr\/bin\///")
  [ ! -z "$res" ] &&  echo "$res" > "test/$file_res"
done

cd test
rm 2to3*


