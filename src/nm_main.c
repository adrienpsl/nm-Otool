#include "nm_otool.h"

int nm_exit(int error)
{
	t_no *no;

	no = get_no();
	if (no->mmap_start)
		munmap(no->mmap_start, no->mmap_size);
	//	if (no->symbol_array)
	//		free(no->symbol_array);
	//	ft_lstdel(no->section_list, NULL);
	//	if (error)
	//		exit(EXIT_FAILURE);
	(void)error;
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

void fill_ofile(void *start, size_t size, t_ofile *ofile)
{
	ft_bzero(ofile, sizeof(t_ofile));
	ofile->start = start;
	ofile->end = start + size;
	ofile->ptr = start;
}

// parse magic
e_ret handle_header(t_no *no, void *start)
{
	t_ofile *ofile;

	ofile = get_ofile();
	fill_ofile(start, no->mmap_size, ofile);
	if (KO == parse_magic_number(ofile, start))
		return (KO);
	if (ofile->is_fat)
		return (handle_fat_binaries(ofile));
	else
		return (handle_ofile(ofile));
}

int main(int ac, char **av)
{
	int i;
	t_no *no;

	no = get_no();
	i = option_parser(av, ac);
	while (i < ac)
	{
		if (KO == create_mmap(av[i], no))
			return (nm_exit(1));
		if (true == is_archive(no, no->mmap_start))
			handle_archive(no);
		else
			handle_ofile(get_ofile());
		i++;
	}
	nm_exit(0);
}
