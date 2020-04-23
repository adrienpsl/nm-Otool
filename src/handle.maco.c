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

void fill_ofile(void *start, size_t size, t_ofile *ofile)
{
	ft_bzero(ofile, sizeof(t_ofile));
	ofile->start = start;
	ofile->end = start + size;
	ofile->ptr = start;
}

// mac o not share same option that the file
e_ret handle_maco(void *start, size_t size)
{
	t_ofile *ofile;

	ofile = get_ofile();

	fill_ofile(start, size, ofile);
	if (KO == parse_magic_number(&ofile->ht, start))
		return (KO);
	// parse magic informaition go into the mmap option,
	if (ofile->ht.is_fat)
		return (handle_fat_binaries(ofile, 0));
	return (handle_ofile(ofile));
}
