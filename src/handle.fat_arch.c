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

int save_start_maco(t_ofile *ofile, t_fat_arch *fat_arch)
{
	ofile->ptr = ofile->start + swapif_u32(fat_arch->offset);
	ofile->start = ofile->ptr;
	return (1);
}

// set the first, and loop to find the good for that arch.
// recall with option to call on all element.
// sinon des que j'ai le bon processeur, je lance le print :).
e_ret handle_fat_binaries(void *start, int print_all)
{
	uint32_t arch_nb;
	uint32_t i;
	t_fat_arch *p_arch;
	t_header_type ht;

	ft_bzero(&ht, sizeof(t_header_type));
	if (KO == parse_magic_number(&ht, start))
		return (KO);
	arch_nb = get_arch_nb(start);
	p_arch = start + sizeof(struct fat_header);
	i = 0;
	while (i < arch_nb)
	{
		if (true == no_overflow(p_arch))
			return (KO);
		if (print_all || swapby_u32(p_arch->cputype, &ht) == 16777223)
			handle_maco(start + swapby_u32(p_arch->offset, &ht),
				swapby_u32(p_arch->size, &ht));
		if (swapby_u32(p_arch->cputype, &ht) == 16777223)
			break;
		p_arch = (void *)p_arch + sizeof(t_fat_arch);
		i++;
	}
	// recall himself if no corresponding value
	//	if (no_overflow_no_goback(ofile->ptr, 0))
	//		return (KO);
	return (OK);
}
