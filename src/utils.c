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
	return (get_ofile()->is_big ? ft_bswap_32(uint_32)
								: uint_32);
}

uint64_t swapif64(uint64_t uint_64)
{
	return (get_ofile()->is_big ? ft_bswap_64(uint_64)
								: uint_64);
}

bool is_64bits(void)
{
	t_ofile *ofile;

	ofile = get_ofile();
	return (ofile->header_64);
}

e_ret no_overflow_no_goback(void *ptr)
{
	// todo put in static
	t_no *no;
	uint8_t result;

	no = get_no();
	result = ptr < get_ofile()->ptr
			 || ptr > no->mmap_start + no->mmap_size;
	if (result)
		ft_printf(
			"/Library/Developer/CommandLineTools/usr/bin/nm: %s truncated or malformed object (load command 0 extends past end of file)\n\n",
			get_no()->file_name);
	return (result);
}

e_ret no_overflow(void *ptr)
{
	// todo put in static
	t_no *no;
	uint8_t result;

	no = get_no();
	result = ptr < no->mmap_start
			 || ptr > no->mmap_start + no->mmap_size;
	if (result)
		ft_printf(
			"/Library/Developer/CommandLineTools/usr/bin/nm: %s truncated or malformed object (load command 0 extends past end of file)\n\n",
			get_no()->file_name);
	return (result);
}