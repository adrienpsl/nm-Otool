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

e_ret handle_ofile(t_ofile *ofile)
{
	int result;

	result = OK;
	if (build_section_list(ofile)
		|| get_no()->mode
		|| !ofile->symtab_command
		|| build_sym_array(ofile, ofile->symtab_command))
	{
		if (get_no()->mode == 0)
			ft_printf("/Library/Developer/CommandLineTools/usr/bin/nm:"
					  " %s The file was not recognized as a valid object file\n\n",
				get_no()->file_name);
		result = KO;
	}
	else
		print_sym_array(ofile);
	free_ofile(ofile);
	return (result);
}
