#include "nm_otool.h"

int nm_exit(int error)
{
	if (error)
		ft_dprintf(ERROR_FD, NM_NAME": %s\n", ft_errno(NULL));
	return (0);
}

bool is_archive(t_no *no, void *ptr)
{
	if (OK == ft_strncmp(ptr, ARMAG, SARMAG))
	{
		no->is_ar = true;
		return (true);
	}
	return (false);
}

int main(int ac, char **av)
{
	int i;
	t_no *no;

	no = get_no();
	i = option_parser(av, ac);
	no->mode = 1;
	while (i < ac)
	{
		if (KO == create_mmap(av[i], no))
		{
			i++;
			continue;
		}
		if (true == is_archive(no, no->mmap_start))
			handle_archive(no, no->mmap_start);
		else
			handle_maco(no->mmap_start, no->mmap_size, 0);
		munmap(no->mmap_start, no->mmap_size);
		i++;
	}
	nm_exit(0);
}
