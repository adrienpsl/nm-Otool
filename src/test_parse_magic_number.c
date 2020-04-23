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

uint32_t g_64bits[] = {
	MH_MAGIC_64,
	MH_CIGAM_64,
	FAT_MAGIC_64,
	FAT_CIGAM_64,
};

uint32_t g_32bits[] = {
	MH_MAGIC,
	0,
	0,
	0
};

uint32_t g_cigam[] = {
	MH_CIGAM,
	MH_CIGAM_64,
	FAT_CIGAM,
	FAT_CIGAM_64,
};

uint32_t g_fat[] = {
	FAT_MAGIC,
	FAT_MAGIC_64,
	FAT_CIGAM,
	FAT_CIGAM_64,
};

bool is_in(const uint32_t *test, uint32_t magic)
{
	uint8_t i;

	i = 0;
	while (i < 4)
	{
		if (magic == test[i])
			return (true);
		i++;
	}
	return (false);
}

int is_valid_magic(uint32_t magic)
{
	bool is;

	is = is_in(g_64bits, magic)
		 || is_in(g_cigam, magic)
		 || is_in(g_fat, magic)
		 || is_in(g_32bits, magic);
	if (is == false)
		return (KO);
	return (OK);
}

void parse_magic_maco(t_ofile *ofile, uint32_t magic)
{
	if (is_in(g_64bits, magic))
		ofile->header_64 = true;
	if (is_in(g_cigam, magic))
		ofile->is_big = true;
	else
		ofile->is_big = false;
	if (is_in(g_fat, magic))
		ofile->is_fat = true;
}

e_ret parse_magic_number(t_ofile *ofile, const uint32_t *magic)
{
	if (is_valid_magic(*magic))
		return (KO);
	parse_magic_maco(ofile, *magic);
	return (OK);
}

