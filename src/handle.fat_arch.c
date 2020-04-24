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


uint32_t get_arch_nb(t_fat_header *fh, t_header_type *ht)
{
	uint32_t result;

	result = swapby_u32(fh->nfat_arch, ht);
	return (result);
}

e_ret launch_macho(void *start, t_fat_arch *p_arch, t_header_type *ht)
{
	int result;
	void *start_maco;

	start_maco = start + swapby_u32(p_arch->offset, ht);
	if (true == no_overflow(start_maco))
		return (KO);
	result = handle_maco(start_maco, swapby_u32(p_arch->size, ht), 1);
	return (result);
}

void print_archive_type(t_fat_arch *p_arch, t_header_type *ht)
{
	char *name;
	if (swapby_u32(p_arch->cputype, ht) == 7)
		name = "i386";
	else if (swapby_u32(p_arch->cputype, ht) == 18)
		name = "ppc";
	else
		name = "X86_64";
	ft_printf("\n%s (for architecture %s):\n",
		get_no()->file_name, name);
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
	while (i < get_arch_nb(start, &ht))
	{
		if (true == no_overflow(p_arch))
			return (KO);
		if (print_all)
		{
			print_archive_type(p_arch, &ht);
			result = launch_macho(start, p_arch, &ht);
		}
		else if (swapby_u32(p_arch->cputype, &ht) == 16777223)
			return (launch_macho(start, p_arch, &ht));
		if (result == KO)
			return (result);
		p_arch = (void *)p_arch + sizeof(t_fat_arch);
		i++;
	}
	return (print_all ? OK : handle_fat_binaries(start, 1));
}
