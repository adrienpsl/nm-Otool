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

e_ret dispatch_ofile(t_ofile *ofile, void *start, void *end)
{
	if (false == handle_magic_number(ofile, start))
	{
		ft_dprintf(STDERR_FILENO, "bad magic number\n");
		return (KO);
	}
	handle_ofile(ofile, start, end);
	if (ofile->fat_header)
		return (handle_fat_arch(ofile));
	else if (ofile->archive)
		return (handle_archive(ofile));
	else
		return (handle_maco(ofile));
}
