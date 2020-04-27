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

bool is_overflow(t_ofile *ofile, void *ptr, bool print_error)
{
	bool result;

	result = !(ptr >= ofile->start && ptr <= ofile->end);
	if (result && print_error && get_no()->mode == OTOOL)
		ft_putchar('\n');
	if (result && print_error)
		ft_dprintf(STDERR_FILENO, NM_ERROR_START"%s truncated or malformed object (load command 0 extends past end of file)\n\n",
			ofile->file_name);
	return (result);
}

uint32_t swapif_u32(t_ofile *ofile, uint32_t uint)
{
	if (ofile->big_endian)
		return (ft_bswap_32(uint));
	else
		return (uint);
}

uint64_t swapif_u64(t_ofile *ofile, uint64_t uint)
{
	if (ofile->big_endian)
		return (ft_bswap_64(uint));
	else
		return (uint);
}
