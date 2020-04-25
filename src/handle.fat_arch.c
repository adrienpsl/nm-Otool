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

static void *
parse_header(t_ofile *mode, struct fat_header *header, uint32_t *p_nfat_arch)
{
	uint32_t nfat_arch;
	uint32_t header_size;

	{
		header_size = sizeof(struct fat_header);
		if (true == is_overflow(mode, (void *)header + header_size))
			return (NULL);
	}
	{
		nfat_arch = header->nfat_arch;
		*p_nfat_arch = swapif_u32(mode, nfat_arch);
	}
	return ((void *)header + header_size);
}

e_ret
launch_dispatch(t_ofile *fat_option, struct fat_arch *fat_arch, void *fat_start)
{
	uint32_t offset;
	uint32_t size;
	void *end;
	void *start;

	offset = swapif_u32(fat_option, fat_arch->offset);
	size = swapif_u32(fat_option, fat_arch->size);
	start = fat_start + offset;
	end = start + size;
	if (true == is_overflow(fat_option, start)
		|| is_overflow(fat_option, end))
		return (KO);
	else
		dispatch(start, end);
	return (OK);
}

e_ret handle_fat_arch(t_ofile *fat_option, void *start, bool print_all)
{
	struct fat_arch *f_arch;
	uint32_t nfat_arch;

	if (NULL ==
		(f_arch = parse_header(fat_option, start, &nfat_arch)))
		return (KO);
	while (nfat_arch)
	{
		if (true == is_overflow(fat_option, f_arch))
			return (KO);
		if (print_all)
			launch_dispatch(fat_option, f_arch, start);
		else if (swapif_u32(fat_option, f_arch->cputype) == 16777223)
			return (launch_dispatch(fat_option, f_arch, start));
		f_arch = (void *)f_arch + sizeof(struct fat_arch);
		nfat_arch = nfat_arch - 1;
	}
	if (!print_all)
		handle_fat_arch(fat_option, start, 1);
	return (OK);
}