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

void free_ofile(t_ofile *ofile)
{
	if (ofile->sections)
		ft_lstdel(ofile->sections, NULL);
	if (ofile->symbols)
		free(ofile->symbols);
}

e_ret handle_maco(t_ofile *ofile)
{
	if (KO == build_sections(ofile))
		return (KO);
	if (KO == build_symtab(ofile))
		return (KO);
	if (get_no()->mode == OTOOL)
		otool_print(ofile, ofile->otool_section);
	if (get_no()->mode == NM)
		print_nm(ofile, get_nm_options());
	return (OK);
}

static e_ret
handle_ofile(t_ofile *ofile, void *start, void *end, t_ofile *prev)
{
	ofile->start = start;
	ofile->ptr = start;
	ofile->end = end;
	ofile->file_name = get_no()->file_name;
	if (NULL != prev)
	{
		ofile->no_print_file_otool = prev->no_print_file_otool;
		ofile->is_print = prev->is_print;
	}
	return (OK);
}

e_ret dispatch(void *start, void *end, t_ofile *prev)
{
	t_ofile ofile;
	e_ret result;

	if (false == handle_magic_number(&ofile, start))
	{
		if (get_no()->mode == NM)
			ft_dprintf(STDERR_FILENO,
				"/Library/Developer/CommandLineTools/usr/bin/nm: %s "
				"The file was not recognized as a valid object file\n\n",
				get_no()->file_name);
		else
			ft_dprintf(STDERR_FILENO, "%s: is not an object file\n",
				get_no()->file_name);
		return (KO);
	}
	handle_ofile(&ofile, start, end, prev);
	if (ofile.fat_header)
		result = handle_fat_arch(&ofile, ofile.start, 0);
	else if (ofile.archive)
		result = handle_archive(&ofile, ofile.start, ofile.end);
	else
		result = handle_maco(&ofile);
	free_ofile(&ofile);
	return (result);
}
