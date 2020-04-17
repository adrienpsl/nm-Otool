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

	if (no->is_fat == false)
		return;
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
