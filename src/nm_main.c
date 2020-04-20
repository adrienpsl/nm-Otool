#include "nm_otool.h"

int nm_exit(int error)
{
	t_no *no;

	no = get_no();
	if (no->map)
		munmap(no->start_map, no->map_size);
	if (no->symbol_array)
		free(no->symbol_array);
	ft_lstdel(no->section_list, NULL);
	if (error)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}

int main(int ac, char **av)
{
	int i;
	t_no *no;

	no = get_no();
	i = option_parser(av, ac);
	if (binary_map(av[i], no)
		|| test_parse_magic_number(no, no->map))
		return (nm_exit(1));
	if (no->is_fat)
	{
		handle_fat_binaries(no);
		if (test_parse_magic_number(no, no->map))
			return (nm_exit(1));
	}
	if (build_section_list(no)
		|| build_sym_array(no, no->symtab_command))
		return (nm_exit(1));
	print_sym_array(no);
	nm_exit(0);
}
