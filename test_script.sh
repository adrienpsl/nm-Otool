#!/usr/bin/env bash

## test with all file in bin
##
rm -fr test
mkdir test
#
for file in /usr/bin/*; do
  nm "$file" > real_nm 2>&1
#  nm  "$file" > real_nm 2>&1
  ./cmake-build-debug/nm_otool "$file" > my_nm 2>&1
  res=$(diff real_nm my_nm)
  file_res=$(echo "$file" | sed -e "s/^\/usr\/bin\///")
  [ ! -z "$res" ] &&  echo "$res" > "test/$file_res"
done


for file in ./binaire_test/*; do
  echo "$file"
  nm "$file" > real_nm 2>&1
#  nm  "$file" > real_nm 2>&1
  ./cmake-build-debug/nm_otool "$file" > my_nm 2>&1
  res=$(diff real_nm my_nm)
  file_res=$(echo "$file" | sed -e "s/^\.\/binaire_test\///")
  [ ! -z "$res" ] &&  echo "$res" > "test/$file_res"
done

for file in /bin/*; do
  echo "$file"
  nm "$file" > real_nm 2>&1
#  nm  "$file" > real_nm 2>&1
  ./cmake-build-debug/nm_otool "$file" > my_nm 2>&1
  res=$(diff real_nm my_nm)
  file_res=$(echo "$file" | sed -e "s/^\/bin\///")
  [ ! -z "$res" ] &&  echo "$res" > "test/$file_res"
done



#for file in ./binaire_test/*; do
#  echo "$file"
#  nm "$file" > real_nm 2>&1
##  nm  "$file" > real_nm 2>&1
#  ./cmake-build-debug/nm_otool "$file" > my_nm 2>&1
#  res=$(diff real_nm my_nm)
#  file_res=$(echo "$file" | sed -e "s/^\.\/binaire_test\///")
#  [ ! -z "$res" ] &&  echo "$res" > "test/$file_res"
#done

cd test
ls -l | wc -l
#rm 2to3* sudo


