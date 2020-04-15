#include "nm_otool.h"

t_no *get_no(void)
{
	static t_no no = {};

	return &no;
}

uint32_t g_64bits[] = {
	MH_MAGIC_64,
	MH_CIGAM_64,
	FAT_MAGIC_64,
	FAT_CIGAM_64,
	0
};

uint32_t g_cigam[] = {
	MH_CIGAM,
	MH_CIGAM_64,
	FAT_CIGAM,
	FAT_CIGAM_64,
	0
};

uint32_t g_fat[] = {
	FAT_MAGIC,
	FAT_MAGIC_64,
	FAT_CIGAM,
	FAT_CIGAM_64,
	0
};

bool is_that(const uint32_t test[5], uint32_t magic)
{
	int i;

	i = 0;
	while (i < 5)
	{
		if (magic == test[i])
			return (true);
		i++;
	}
	return (false);
}

bool set_header(char *ptr, t_no *no)
{
	uint32_t magic_number;

	magic_number = *(uint32_t *)ptr;

	if (is_that(g_64bits, magic_number))
		no->header_64 = true;

	if (is_that(g_cigam, magic_number))
		no->is_big = true;
	else
		no->is_big = false;

	if (is_that(g_fat, magic_number))
		no->is_fat = true;

	if (is_that(g_64bits, magic_number));
	else if (is_that(g_cigam, magic_number));
	else if (is_that(g_fat, magic_number));
	else
	{
		ft_printf("/Library/Developer/CommandLineTools/usr/bin/nm:"
				  " %s The file was not recognized as a valid object file\n\n",
			no->file_name);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void print_fat_header(t_no *no, struct fat_arch *fat_arch)
{
	if (no->fat_start == NULL)
		no->fat_start = no->start_map + swapif32(fat_arch->offset);
	if (1)
		return;
	ft_printf("    Cpu type:    %d\n", swapif32(fat_arch->cputype));
	ft_printf("    Cpu subtype: %d\n", swapif32(fat_arch->cpusubtype));
	ft_printf("    offset:      %lu\n", swapif32(fat_arch->offset));
	ft_printf("    size:        %lu\n", swapif32(fat_arch->size));
	ft_printf("    align:       %lu\n", swapif32(fat_arch->align));
}

void handle_fat_binaries(t_no *no)
{
	uint32_t arch_nb;
	uint32_t i;

	arch_nb = swapif32(((struct fat_header *)no->map)->nfat_arch);
	i = 0;
	no->map += sizeof(struct fat_header);
	while (i < arch_nb)
	{
		//		ft_printf("architecture %u\n", i);
		print_fat_header(no, no->map);
		no->map += sizeof(struct fat_arch);
		i++;
	}
	no->map = no->fat_start;
}

void print_header(t_no *no)
{
	struct mach_header_64 *mach_header_64;
	//	struct mach_header *mach_header;

	ft_printf("Mach header\n");
	if (no->header_64)
	{
		mach_header_64 = no->map;
		ft_printf("-------------------- 64 bits\n");
		ft_printf(" ");
		ft_printf("0x%X ", mach_header_64->magic);
		ft_printf("  %2d", mach_header_64->cputype);
		ft_printf(" %d", mach_header_64->cpusubtype);
		ft_printf(" 0x%x", mach_header_64->filetype);
		ft_printf(" %u", mach_header_64->ncmds);
		ft_printf(" %u", mach_header_64->sizeofcmds);
		ft_printf(" 0x%x", mach_header_64->flags);
	}
	else
		ft_printf("-------------------- 32 bits");
}

int main(int ac, char **av)
{
	(void)ac;
	t_no *no = get_no();
	if (EXIT_FAILURE == binary_map(av[1], no))
		return (EXIT_FAILURE);
	if (set_header(no->map, no))
		return (EXIT_FAILURE);
	if (no->is_fat)
	{
		handle_fat_binaries(no);
		if (set_header(no->map, no))
			return (EXIT_FAILURE);
		set_header(no->map, no);
	}
	//	print_header(no);
	build_segment_list(no);
	build_symbol_list(no, no->symtab_command);
	print_list(no);
}
