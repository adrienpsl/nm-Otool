#include <stdio.h>
#include <stdlib.h>
#include <ft_printf.h>
#include <mach-o/nlist.h>
#include <nm_otool.h>
# include "mach-o/loader.h"
# include "sys/mman.h"
# include "fcntl.h"
# include "sys/stat.h"

struct nlist_64 g_symtab[100];
struct section_64 *g_section[100];


void nm(char *ptr)
{
	// les 4 premiers octets donne l'architecture
	// il va y avoir des fatbinary, ce sont des binaires qui contiennent plusieurs
	// architectures.
	__uint32_t magic_number;

	magic_number = *(int *)ptr;
//	if (magic_number == MH_MAGIC_64)
//		handle_64(ptr);
}

int main(int ac, char **av)
{
	(void)ac;
	t_no no = {};
	if (EXIT_FAILURE == binary_map(av[1], &no))
		return (EXIT_FAILURE);
	build_segment_list(&no);
	build_symbol_list(&no, no.symtab_command);
	print_list(&no);
}
