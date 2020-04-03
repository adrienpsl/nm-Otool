#include <stdio.h>
#include <stdlib.h>
#include <mach-o/nlist.h>
#include <ft_printf.h>
# include "mach-o/loader.h"
# include "sys/mman.h"
# include "fcntl.h"
# include "sys/stat.h"

struct nlist_64 g_symtab[100];
struct section_64 *g_section[100];


void symtab_handle(struct symtab_command *symtab_command, void *file_start)
{
	char *str_tab = file_start + symtab_command->stroff;
	struct nlist_64 *sym_tab = file_start + symtab_command->symoff;
	uint32_t nsyms = symtab_command->nsyms;
	uint32_t i = 0;

	struct nlist_64 *symbol;
	struct section_64 *section_64;
	char *sym_name;

	while (i < nsyms)
	{
		symbol = sym_tab + i;
		sym_name = str_tab + symbol->n_un.n_strx;
		if (N_SECT == (N_TYPE & symbol->n_type))
		{
			section_64 = g_section[i];
			printf("%s %llx \n", sym_name , symbol->n_value);
		}
		i++;
	}
}

void handle_segment(struct segment_command_64 *command)
{
	struct section_64 *section_64;
	static int all_sec = 0;

	section_64 = (void *)command + sizeof(struct segment_command_64);
	for (uint32_t j = 0; j < command->nsects; ++j)
	{
		g_section[all_sec] = section_64;
		section_64 = (void *)section_64 + sizeof(struct section_64);
		all_sec += 1;
	}
}

void handle_64(char *ptr)
{
	int ncmds;
	int i;
	struct mach_header_64 *header_64;
	struct load_command *lc;
//	struct symtab_command *sym;

	// the cast convert from big to little ! :) awesome!
	header_64 = (struct mach_header_64 *)ptr;
	ncmds = header_64->ncmds;
	lc = (void *)ptr + sizeof(*header_64);

	for (i = 0; i < ncmds; ++i)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			symtab_handle((void *)lc, ptr);
		}
		if (lc->cmd == LC_SEGMENT_64)
		{
			handle_segment((void *)lc);
		}
		lc = (void *)lc + lc->cmdsize;
	}

	// on va loop sur les load command et stop sur les

}

void nm(char *ptr)
{
	// les 4 premiers octets donne l'architecture
	// il va y avoir des fatbinary, ce sont des binaires qui contiennent plusieurs
	// architectures.
	__uint32_t magic_number;

	magic_number = *(int *)ptr;
	if (magic_number == MH_MAGIC_64)
		handle_64(ptr);
}

int open_and_map_file(char *path)
{
	(void)path;
	ft_printf("bite");
	return (0);
}

int main(int ac, char **av)
{
	(void)ac;
	int fd;
	char *ptr;
	struct stat buf;

	// open the file.
	if ((fd = open(av[1], O_RDONLY)) < 0)
	{
		perror("open");
		return (EXIT_FAILURE);
	}

	if (fstat(fd, &buf) < 0)
	{
		perror("fstats");
		return EXIT_FAILURE;
	}
	printf("%lld \n", buf.st_size);

	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) ==
		MAP_FAILED)
	{
		perror("mmap failed");
		return EXIT_FAILURE;
	}

	nm(ptr);
}
