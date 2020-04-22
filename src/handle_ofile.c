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

void free_ofile(t_ofile *ofile)
{
	if (ofile->sections)
		ft_lstdel(ofile->sections, NULL);
	if (ofile->symbols)
		free(ofile->symbols);
}

e_ret handle_ofile(t_ofile *ofile, void *start, size_t size)
{
	int result;

	result = OK;
	fill_ofile(start, size, ofile);
	if (parse_magic_number(ofile)
		|| (ofile->is_fat && KO == handle_fat_binaries(ofile))
		|| build_section_list(ofile)
		|| !ofile->symtab_command
		|| build_sym_array(ofile, ofile->symtab_command))
		result = KO;
	else
		print_sym_array(ofile);
	free_ofile(ofile);
	return (result);
}
