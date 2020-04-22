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

// get information from no and add that to the function file
e_ret handle_ofile(void *start, size_t size)
{
	t_ofile *ofile;

	// there is no free of the element.

	ofile = get_ofile();
	fill_ofile(start, size, ofile);
	if (parse_magic_number(ofile))
		return (KO);
	if (ofile->is_fat
		&& KO == handle_fat_binaries(ofile))
		return (KO);
	if (build_section_list(ofile))
		return (KO);
	if (!ofile->symtab_command)
		return (OK);
	if (build_sym_array(ofile, ofile->symtab_command))
		return (KO);
	print_sym_array(ofile);
	return (OK);
}
