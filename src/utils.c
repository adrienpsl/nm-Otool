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

uint32_t swapif_u32(uint32_t uint_32)
{
	return (get_no()->is_big ? ft_bswap_32(uint_32)
						 : uint_32);
}

uint64_t swapif64(uint64_t uint_64)
{
	return (get_no()->is_big ? ft_bswap_64(uint_64)
							 : uint_64);
}

bool is_64bits(void)
{
	return (get_no()->header_64);
}

e_ret is_overflow(void *ptr)
{
	t_no *no;
	uint8_t result;

	no = get_no();
	result = (ptr < no->start_map
			  || ptr > (no->map_end - sizeof(uint64_t)));
	return (result);
}