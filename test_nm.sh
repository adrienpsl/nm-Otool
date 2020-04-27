####

nm -u break-nm/feed_the_nm/64_exe_hard | cat -e > a
./ft_nm -u break-nm/feed_the_nm/64_exe_hard | cat -e > b
diff a b
