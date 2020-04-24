#!/usr/bin/env bash

## test with all file in bin
##
rm -fr test
mkdir test


##### debug option
#for file in /usr/bin/*; do
#  echo "$file"
#  otool -t  "$file" > real_nm 2>&1
#  ./cmake-build-debug/nm_otool  "$file" > my_nm 2>&1
#  res=$(diff real_nm my_nm)
#  file_res=$(echo "$file" | sed -e "s/^\/usr\/bin\///")
#  [ ! -z "$res" ] &&  echo "$res" > "test/$file_res"
#done
#ls -l ./test | wc -l
#rm test/*
#
##
#for file in ./binaire_test/*; do
#  otool -t "$file" > real_nm 2>&1
#  nm  "$file" > real_nm 2>&1
#  ./cmake-build-debug/nm_otool "$file" > my_nm 2>&1
#  res=$(diff real_nm my_nm)
#  file_res=$(echo "$file" | sed -e "s/^\.\/binaire_test\///")
#  [ ! -z "$res" ] &&  echo "$res" > "test/$file_res"
#done
#
#for file in /bin/*; do
#  otool -t "$file" > real_nm 2>&1
##  nm  "$file" > real_nm 2>&1
#  ./cmake-build-debug/nm_otool "$file" > my_nm 2>&1
#  res=$(diff real_nm my_nm)
#  file_res=$(echo "$file" | sed -e "s/^\/bin\///")
#  [ ! -z "$res" ] &&  echo "$res" > "test/$file_res"
#done

#for file in /usr/lib/system/*; do
#  otool -t "$file" | cat -e > real_nm 2>&1
##  nm  "$file" > real_nm 2>&1
#  ./cmake-build-debug/nm_otool "$file" | cat -e > my_nm 2>&1
#  res=$(diff real_nm my_nm)
#  file_res=$(echo "$file" | sed -e "s/^\/usr\/lib\/system\///")
#  [ ! -z "$res" ] &&  echo "$res" > "test/$file_res"
#done
#
#
#for file in ./objs/*; do
#  otool -t "$file" > real_nm 2>&1
##  nm  "$file" > real_nm 2>&1
#  ./cmake-build-debug/nm_otool "$file" > my_nm 2>&1
#  res=$(diff real_nm my_nm)
#  file_res=$(echo "$file" | sed -e "s/^\.\/objs\///")
#  [ ! -z "$res" ] &&  echo "$res" > "test/$file_res"
#done
##

#for file in ./break-nm/feed_the_nm/*; do
#  echo "$file"
#  otool -t "$file" > real_nm 2>&1
  nm  "$file" > real_nm 2>&1
#  ./cmake-build-debug/nm_otool "$file" > my_nm 2>&1
#  res=$(diff real_nm my_nm)
#  file_res=$(echo "$file" | sed -e "s/^\.\/break-nm\/feed_the_nm\///")
#  [ ! -z "$res" ] &&  echo "$res" > "test/$file_res"
#done


for file in ./break-nm/weird_architecture/*; do
  otool -t "$file" > real_nm 2>&1
#  nm  "$file" > real_nm 2>&1
  ./cmake-build-debug/nm_otool "$file" > my_nm 2>&1
  res=$(diff real_nm my_nm)
  file_res=$(echo "$file" | sed -e "s/^\.\/break-nm\/weird_architecture\///")
  [ ! -z "$res" ] &&  echo "$res" > "test/$file_res"
done

for file in ./break-nm/weird_archive/*; do
  otool -t "$file" > real_nm 2>&1
#  nm  "$file" > real_nm 2>&1
  ./cmake-build-debug/nm_otool "$file" > my_nm 2>&1
  res=$(diff real_nm my_nm)
  file_res=$(echo "$file" | sed -e "s/^\.\/break-nm\/weird_archive\///")
  [ ! -z "$res" ] &&  echo "$res" > "test/$file_res"
done

for file in ./break-nm/weird_binaries/*; do
  otool -t "$file" > real_nm 2>&1
#  nm  "$file" > real_nm 2>&1
  ./cmake-build-debug/nm_otool "$file" > my_nm 2>&1
  res=$(diff real_nm my_nm)
  file_res=$(echo "$file" | sed -e "s/^\.\/break-nm\/weird_binaries\///")
  [ ! -z "$res" ] &&  echo "$res" > "test/$file_res"
done

#for file in ./break-nm/corrupted_archive/*; do
#  otool -t "$file" > real_nm 2>&1
##  nm  "$file" > real_nm 2>&1
#  ./cmake-build-debug/nm_otool "$file" > my_nm 2>&1
#  res=$(diff real_nm my_nm)
#  file_res=$(echo "$file" | sed -e "s/^\.\/break-nm\/corrupted_archive\///")
#  [ ! -z "$res" ] &&  echo "$res" > "test/$file_res"
#done
#
#
#for file in ./break-nm/corrupted_binaries/*; do
#  otool -t "$file" > real_nm 2>&1
##  nm  "$file" > real_nm 2>&1
#  ./cmake-build-debug/nm_otool "$file" > my_nm 2>&1
#  res=$(diff real_nm my_nm)
#  file_res=$(echo "$file" | sed -e "s/^\.\/break-nm\/corrupted_binaries\///")
#  [ ! -z "$res" ] &&  echo "$res" > "test/$file_res"
#done

ls -l test | wc -l
