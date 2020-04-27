#
#
#
#

function print_header() {

rm -fr test
mkdir test

echo "
test $1
      --------------------------------------------------------------------------
      --------------------------------------------------------------------------"
}

function test_and_diff() {
nm "$1" > a
./ft_nm "$1" > b
diff a b
}

cat -e author

echo "nm test -----------------------------------------------------------------"

################################################################################
print_header "Bad options"
./ft_nm -sanoetuh
./ft_nm -s -s -s asasoeuth

print_header "File does not exits"
./ft_nm asnoeuth
nm asnoeuth


################################################################################
print_header "No argument"

touch hello.c
echo "#include <stdio.h>
int main(int ac, char **av)
{
    printf(\"hello words\");
    return (1);
} " > hello.c
gcc hello.c

test_and_diff

################################################################################
print_header "2 and 3 argument"
test_and_diff a.out a.out


###############################################################################
#print_header "test all in /usr/bin"
#
#rm -fr test
#mkdir test
#
#for file in /usr/bin/*; do
#  nm  "$file" > real_nm 2>&1
#  ./ft_nm  "$file" > my_nm 2>&1
#  res=$(diff real_nm my_nm)
#  file_res=$(echo "$file" | sed -e "s/^\/usr\/bin\///")
#  [ ! -z "$res" ] &&  echo "$res" > "test/$file_res"
#done
#ls -l ./test | wc -l

#
#################################################################################
#print_header "all in /bin"
#
#for file in /bin/*; do
#  nm "$file" > real_nm 2>&1
#  ./ft_nm "$file" > my_nm 2>&1
#  res=$(diff real_nm my_nm)
#  file_res=$(echo "$file" | sed -e "s/^\/bin\///")
#  [ ! -z "$res" ] &&  echo "$res" > "test/$file_res"
#done
#ls -l ./test | wc -l
#
#
#################################################################################
#print_header "binaire_test "
#
#for file in ./binaire_test/*; do
#  nm "$file" > real_nm 2>&1
#  ./ft_nm "$file" > my_nm 2>&1
#  res=$(diff real_nm my_nm)
#  file_res=$(echo "$file" | sed -e "s/^\.\/binaire_test\///")
#  [ ! -z "$res" ] &&  echo "$res" > "test/$file_res"
#done
#ls -l ./test | wc -l
#
#################################################################################
#print_header "usr/lib/system"
##
#for file in /usr/lib/system/*; do
#  nm "$file" | cat -e > real_nm 2>&1
#  ./ft_nm "$file" | cat -e > my_nm 2>&1
#  res=$(diff real_nm my_nm)
#  file_res=$(echo "$file" | sed -e "s/^\/usr\/lib\/system\///")
#  [ ! -z "$res" ] &&  echo "$res" > "test/$file_res"
#done
#ls -l ./test | wc -l
#
#################################################################################
#print_header "corrupted_archive"
#
#for file in ./break-nm/corrupted_archive/*; do
#  nm "$file" > real_nm 2>&1
#  ./ft_nm "$file" | cat -e > my_nm 2>&1
#  res=$(diff real_nm my_nm)
#  file_res=$(echo "$file" | sed -e "s/^\.\/break-nm\/corrupted_archive\///")
#  [ ! -z "$res" ] &&  echo "$res" > "test/$file_res"
#done
#ls -l ./test | wc -l


#################################################################################
#print_header "corrupted binary"
#
#for file in ./break-nm/corrupted_binaries/*; do
#  nm "$file" > real_nm 2>&1
#  ./ft_nm "$file" 2> my_nm  1> /dev/null
#  res=$(diff real_nm my_nm)
#  file_res=$(echo "$file" | sed -e "s/^\.\/break-nm\/corrupted_binaries\///")
#  [ ! -z "$res" ] &&  echo "$res" > "test/$file_res"
#done
#ls -l ./test | wc -l


################################################################################
#print_header "feed the nm"
#
#for file in ./break-nm/feed_the_nm/*; do
#  nm "$file" > real_nm 2>&1
#  ./ft_nm "$file" > my_nm 2>&1
#  res=$(diff real_nm my_nm)
#  file_res=$(echo "$file" | sed -e "s/^\.\/break-nm\/feed_the_nm\///")
#  [ ! -z "$res" ] &&  echo "$res" > "test/$file_res"
#done
#ls -l ./test | wc -l


##################################################################################
#print_header "weird_architecture"
#
#for file in ./break-nm/weird_architecture/*; do
#  nm "$file" > real_nm 2>&1
#  ./ft_nm "$file" > my_nm 2>&1
#  res=$(diff real_nm my_nm)
#  file_res=$(echo "$file" | sed -e "s/^\.\/break-nm\/weird_architecture\///")
#  [ ! -z "$res" ] &&  echo "$res" > "test/$file_res"
#done
#ls -l ./test | wc -l


################################################################################
#print_header "weird_archive"
#
#for file in ./break-nm/weird_archive/*; do
#  nm "$file" > real_nm 2>&1
#  ./ft_nm "$file" > my_nm 2>&1
#  res=$(diff real_nm my_nm)
#  file_res=$(echo "$file" | sed -e "s/^\.\/break-nm\/weird_archive\///")
#  [ ! -z "$res" ] &&  echo "$res" > "test/$file_res"
#done
#ls -l ./test | wc -l


################################################################################
print_header "weird_binaries"
for file in ./break-nm/weird_binaries/*; do
  nm "$file" > real_nm 2>&1
#  nm  "$file" > real_nm 2>&1
  ./cmake-build-debug/nm_otool "$file" > my_nm 2>&1
  res=$(diff real_nm my_nm)
  file_res=$(echo "$file" | sed -e "s/^\.\/break-nm\/weird_binaries\///")
  [ ! -z "$res" ] &&  echo "$res" > "test/$file_res"
done
ls -l ./test | wc -l
