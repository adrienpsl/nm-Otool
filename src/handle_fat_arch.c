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

uint32_t get_arch_nb(t_fat_header *fh)
{
	return (swapif_u32(fh->nfat_arch));
}

void save_start_maco(t_ofile *ofile, t_fat_arch *fat_arch)
{
	ofile->ptr = ofile->start + swapif_u32(fat_arch->offset);
}

// set the first, and loop to find the good for that arch.
e_ret handle_fat_binaries(t_ofile *ofile)
{
	uint32_t arch_nb;
	uint32_t i;
	t_fat_arch *p_arch;

	arch_nb = get_arch_nb(ofile->ptr);
	p_arch = ofile->ptr + sizeof(struct fat_header);
	i = 0;
	while (i < arch_nb)
	{
		if (true == is_overflow(p_arch, sizeof(t_fat_arch)))
			return (KO);
		if (i == 0
			|| swapif_u32(p_arch->cputype) & CPU_TYPE_X86_64)
			save_start_maco(ofile, p_arch);
		p_arch = (void *)p_arch + sizeof(t_fat_arch);
		i++;
	}
	if (is_overflow(ofile->ptr, 0))
		return (KO);
	return (parse_magic_number(ofile));
}
