#include "nm_otool.h"

t_no *get_no(void)
{
	static t_no no = {};

	return &no;
}

void print_fat_header(char *ptr)
{

}

void set_header(char *ptr)
{
	// les 4 premiers octets donne l'architecture
	// il va y avoir des fatbinary, ce sont des binaires qui contiennent plusieurs
	// architectures.
	uint32_t magic_number;

	magic_number = *(int *)ptr;
	if (magic_number == MH_MAGIC_64)
		ft_printf("64 bit \n");
	if (magic_number == MH_MAGIC)
		ft_printf("32 bit \n");
	if (magic_number == FAT_MAGIC || magic_number == FAT_CIGAM)
		ft_printf("fat fat big");
}

int main(int ac, char **av)
{
	(void)ac;
	t_no *no = get_no();
	if (EXIT_FAILURE == binary_map(av[1], no))
		return (EXIT_FAILURE);
	set_header(no->map);
	no->header_64 = true;
	build_segment_list(no);
	build_symbol_list(no, no->symtab_command);
	print_list(no);
}
