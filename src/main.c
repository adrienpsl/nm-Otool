#include "nm_otool.h"

int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	t_no *no;

	no = get_no();

	char *a[10] = {
		"",
		"-aj",
		""
	};

	printf("%d \n", option_parser(a, sizeof(a) / sizeof(char *)));
	t_options *op = get_options();
	(void)op;
	//	if (EXIT_FAILURE == binary_map(av[1], no))
	//		return (EXIT_FAILURE);
	//
	//	if (test_parse_magic_number(no, no->map))
	//		return (EXIT_FAILURE);
	//	if (no->is_fat)
	//	{
	//		handle_fat_binaries(no);
	//		if (test_parse_magic_number(no, no->map))
	//			return (EXIT_FAILURE);
	//	}
	//	build_section_list(no);
	//	build_sym_list(no, no->symtab_command);
	//	print_list(no);
}
