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
