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

void parse_magic_maco(t_header_type *hp, uint32_t magic)
{
	if (is_in(g_64bits, magic))
		hp->header_64 = true;
	if (is_in(g_cigam, magic))
		hp->is_big = true;
	else
		hp->is_big = false;
	if (is_in(g_fat, magic))
		hp->is_fat = true;
}

e_ret parse_magic_number(t_header_type *ht, const uint32_t *magic)
{
	if (is_valid_magic(*magic))
	{
		if (get_no()->mode)
			ft_printf("%s: is not an object file\n", get_no()->file_name);
		else
			ft_printf(
				"/Library/Developer/CommandLineTools/usr/bin/nm: %s The file was not recognized as a valid object file\n\n",
				get_no()->file_name);
		return (KO);
	}
	//	ft_printf("in magic %x\n", *magic);
	parse_magic_maco(ht, *magic);
	return (OK);
}

