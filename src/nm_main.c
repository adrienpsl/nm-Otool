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
	return (0);
}

int handle(t_no *no)
{
	handle_fat_binaries(no);
	if (test_parse_magic_number(no, no->map))
		return (nm_exit(1));
	// will be out
	if (build_section_list(no)
		|| build_sym_array(no, no->symtab_command))
		return (nm_exit(1));
	print_sym_array(no);
	return (0);
}

void ar()
{
	// loop on archive and print each element
}

int main(int ac, char **av)
{
	int i;
	t_no *no;

	no = get_no();
	i = option_parser(av, ac);

	// is archive? -> loop on the header
	// pas archive -> loop on the file
	if (create_mmap(av[i], no)
		|| test_parse_magic_number(no, no->map))
		return (nm_exit(1));

	if (no->is_ar)
		ar();

	handle(no);

	nm_exit(0);
}
