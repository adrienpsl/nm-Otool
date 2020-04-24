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
	uint32_t result;

	result = swapif_u32(fh->nfat_arch);
	return (result);
}

e_ret launch_macho(void *start, t_fat_arch *p_arch, t_header_type *ht)
{
	int result;
	void *start_maco;

	start_maco = start + swapby_u32(p_arch->offset, ht);
	ft_printf("%X \n", *(int*)start_maco);
	if (true == no_overflow(start_maco))
		return (KO);
	result = handle_maco(start_maco, swapby_u32(p_arch->size, ht));
	return (1);
	return (result);
}

e_ret handle_fat_binaries(void *start, int print_all)
{
	uint32_t i;
	t_fat_arch *p_arch;
	t_header_type ht;
	int result;

	ft_bzero(&ht, sizeof(t_header_type));
	parse_magic_number(&ht, start);
	p_arch = start + sizeof(struct fat_header);
	i = 0;
	while (i < get_arch_nb(start))
	{
		if (true == no_overflow(p_arch))
			return (KO);
		if (print_all || i == 0) // print somme shit in function
		{
			result = launch_macho(start, p_arch, &ht);
			ft_putchar('\n');
		}
//		else if (swapby_u32(p_arch->cputype, &ht) == 16777223)
//			return (launch_macho(start, p_arch, &ht));
//		if (result == KO)
//			return (result);
		p_arch = (void *)p_arch + sizeof(t_fat_arch);
		i++;
	}
//	return (print_all ? OK : handle_fat_binaries(start, 1));
return (OK);
}
