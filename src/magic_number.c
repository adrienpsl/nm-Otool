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

typedef struct s_test
{
	uint32_t magic;
	t_ofile ofile;
} t_test;

#define MAGIC_NUMBER_ARRAY_LIMIT 9

t_test g_test[MAGIC_NUMBER_ARRAY_LIMIT] = {
	{ MH_MAGIC,     {}},
	{ MH_MAGIC_64,  { .x64 = true }},
	{ MH_CIGAM,     { .big_endian = true }},
	{ MH_CIGAM_64,  { .x64 = true, .big_endian = true }},
	{ FAT_MAGIC,    { .fat_header = true }},
	{ FAT_CIGAM,    { .big_endian = true, .fat_header = true }},
	{ FAT_MAGIC_64, { .x64 = true, .fat_header = true }},
	{ FAT_CIGAM_64, { .x64 = true, .big_endian = true, .fat_header = true }},
	{ 0,            { .archive = true }},
};

bool handle_magic_number(t_ofile *ofile, uint32_t *magic)
{
	uint8_t i;
	static int first = 1;

	if (first)
	{
		first = 0;
		g_test[8].magic = *(uint32_t *)ARMAG;
	}
	i = 0;
	while (i < MAGIC_NUMBER_ARRAY_LIMIT)
	{
		if (*magic == g_test[i].magic)
		{
			(*ofile) = g_test[i].ofile;
			return (true);
		}
		i++;
	}
	return (false);
}

