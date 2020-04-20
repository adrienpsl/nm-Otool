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

int is_valid_magic(t_no *no, uint32_t magic)
{
	bool is;

	is = is_in(g_64bits, magic)
		 || is_in(g_cigam, magic)
		 || is_in(g_fat, magic)
		 || is_in(g_32bits, magic);
	if (is == false)
	{
		ft_printf("/Library/Developer/CommandLineTools/usr/bin/nm:"
				  " %s The file was not recognized as a valid object file\n\n",
			no->file_name);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void parse_magic_number(t_no *no, uint32_t magic)
{
	if (is_in(g_64bits, magic))
		no->header_64 = true;
	if (is_in(g_cigam, magic))
		no->is_big = true;
	else
		no->is_big = false;
	{
		if (is_in(g_fat, magic))
			no->is_fat = true;
	}
}

int test_parse_magic_number(t_no *no, void *ptr)
{
	uint32_t magic;

	magic = *(uint32_t *)ptr;
	if (EXIT_SUCCESS == ft_strncmp(ptr, ARMAG, SARMAG))
	{
		no->is_ar = true;
		return (EXIT_SUCCESS);
	}
	else if (is_valid_magic(no, magic))
		return (EXIT_FAILURE);
	parse_magic_number(no, magic);
	return (EXIT_SUCCESS);
}

