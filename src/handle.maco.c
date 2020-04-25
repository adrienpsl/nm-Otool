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

e_ret handle_maco(t_ofile *ofile)
{
	if (KO == build_sections(ofile))
		return (KO);
	if (KO == build_symtab(ofile))
		return (KO);
	print_nm(ofile, get_nm_options());
	// if nm, break here!
	//	if (NULL == ofile->symtab_command)
	//	{
	//		ft_dprintf(STDERR_FILENO, "no symtab\n");
	//		return (KO);
	//	}
	// build the symtab array ?
	// build the fucking list man!

	//	print_section_list(ofile->sections);
	return (OK);
}