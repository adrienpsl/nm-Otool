/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpusel <adpusel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 10:48:07 by adpusel           #+#    #+#             */
/*   Updated: 2017/11/16 12:45:50 by adpusel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void print_fat_header(struct fat_arch *fat_arch)
{
	if (1)
		return;
	ft_printf("    Cpu type:    %d\n", swapif_u32(fat_arch->cputype));
	ft_printf("    Cpu subtype: %d\n", swapif_u32(fat_arch->cpusubtype));
	ft_printf("    offset:      %lu\n", swapif_u32(fat_arch->offset));
	ft_printf("    size:        %lu\n", swapif_u32(fat_arch->size));
	ft_printf("    align:       %lu\n", swapif_u32(fat_arch->align));
}

// set the first, and loop to find the good for that arch.
void handle_fat_binaries(t_no *no)
{
	uint32_t arch_nb;
	uint32_t i;
	struct fat_arch *fat_arch;

	i = 0;
	arch_nb = swapif_u32(((struct fat_header *)no->map)->nfat_arch);
	fat_arch = no->map + sizeof(struct fat_header);
	is_overflow(fat_arch);
	while (i < arch_nb)
	{
		if (swapif_u32(fat_arch->cputype) == 16777223)
			no->fat_start = no->mmap_start + swapif_u32(fat_arch->offset);
		if (no->fat_start == NULL)
			no->fat_start = no->mmap_start + swapif_u32(fat_arch->offset);
		print_fat_header(no->map);
		fat_arch = (void *)fat_arch + sizeof(struct fat_arch);
		is_overflow(fat_arch);
		i++;
	}
	no->map = no->fat_start;
}
