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

e_ret dispatch(void *start, void *end)
{
	t_ofile ofile;

	if (false == handle_magic_number(&ofile, start))
	{
		if (get_no()->mode == NM)
			ft_dprintf(STDERR_FILENO,
				"/Library/Developer/CommandLineTools/usr/bin/nm: %s "
				"The file was not recognized as a valid object file\n\n",
				get_no()->file_name);
		else
			ft_dprintf(STDERR_FILENO, "bad magic number\n");
		return (KO);
	}
	handle_ofile(&ofile, start, end);
	if (ofile.fat_header)
		return (handle_fat_arch(&ofile, ofile.start, 0));
	else if (ofile.archive)
		return (handle_archive(&ofile, ofile.start, ofile.end));
	else
		return (handle_maco(&ofile));
}
