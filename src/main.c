#include "nm_otool.h"

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
	if (test_parse_magic_number(no, no->map))
		return (EXIT_FAILURE);
	if (no->is_fat)
	{
		handle_fat_binaries(no);
		if (test_parse_magic_number(no, no->map))
			return (EXIT_FAILURE);
	}
	//	print_header(no);
	build_segment_list(no);
	build_symbol_list(no, no->symtab_command);
	print_list(no);
}
