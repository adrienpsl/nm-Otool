#include "nm_otool.h"

t_no *get_no(void)
{
	static t_no no = {};

	return &no;
}


#define bswap_16(value) \
((((value) & 0xff) << 8) | ((value) >> 8))

#define bswap_32(value) \
(((uint32_t)bswap_16((uint16_t)((value) & 0xffff)) << 16) | \
(uint32_t)bswap_16((uint16_t)((value) >> 16)))

#define bswap_64(value) \
(((uint64_t)bswap_32((uint32_t)((value) & 0xffffffff)) \
<< 32) | \
(uint64_t)bswap_32((uint32_t)((value) >> 32)))

void print_fat_header(void *ptr)
{
	struct fat_arch *fat_arch;

	fat_arch = ptr;
	ft_printf("Cpu type:    %d", fat_arch->cputype);
	ft_printf("Cpu subtype: %d", fat_arch->cpusubtype);
	ft_printf("offset:      %lu", fat_arch->offset);
	ft_printf("size:        %lu", fat_arch->size);
	ft_printf("align:       %lu", fat_arch->align);
}

void set_header(char *ptr)
{
	// les 4 premiers octets donne l'architecture
	// il va y avoir des fatbinary, ce sont des binaires qui contiennent plusieurs
	// architectures.
	uint32_t magic_number;

	magic_number = *(uint32_t *)ptr;
	if (magic_number == MH_MAGIC_64)
	{
		ft_printf("64 bit \n");
		get_no()->header_64 = true;
	}
	if (magic_number == MH_CIGAM_64)
	{
		ft_printf("64 bit little \n");
		get_no()->header_64 = true;
	}

	if (magic_number == MH_MAGIC)
	{
		ft_printf("32 bit \n");
	}
	if (magic_number == MH_CIGAM)
	{
		ft_printf("32 bits little");
	}

	if (magic_number == FAT_MAGIC)
	{
		ft_printf("fat fat big");
	}
	uint32_t data;
	if (magic_number == FAT_CIGAM)
	{
		data = ((struct fat_header*)ptr)->nfat_arch;
		data = bswap_32(data);
		printf("%d", data);
		get_no()->is_big = true;
		get_no()->is_fat = true;
	}
}

int main(int ac, char **av)
{
	(void)ac;
	t_no *no = get_no();
	if (EXIT_FAILURE == binary_map(av[1], no))
		return (EXIT_FAILURE);
	set_header(no->map);

//	if (no->is_fat)
//	{
//		no->map = no->map + sizeof(struct fat_arch);
//		set_header(no->map);
//	}
//
//	build_segment_list(no);
//	build_symbol_list(no, no->symtab_command);
//	print_list(no);
}
