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

uint64_t get_size(t_ofile *ofile, void *list)
{
	struct nlist *nlist;
	struct nlist_64 *nlist_64;

	nlist = list;
	nlist_64 = list;
	if (ofile->x64)
		return nlist_64->n_value;
	else
		return (uint64_t)(nlist->n_value);
}

bool cmp_func(void *l1, void *l2, t_ofile *ofile)
{
	int res;

	if (get_nm_options()->n_numeric_sort)
		res = get_size(ofile, l1) > get_size(ofile, l2);
	else
	{
		res = ft_strcmp(
			get_name(ofile, l1),
			get_name(ofile, l2));
//		if (res == 0)
//			res = get_size(ofile, l1) > get_size(ofile, l2);
		res = res > 0 ? true : false;
	}
	if (get_nm_options()->r_rev_sort)
		res = !res;
	return (res);
}

void
bubble_sort_symbol_array(t_ofile *ofile, void **current, uint32_t array_size)
{
	void *tmp;
	uint32_t i;
	uint32_t y;

	i = 0;
	if (0 == array_size)
		return;
	while (i < array_size - 1)
	{
		y = 0;
		while (y < array_size - i - 1)
		{
			if (cmp_func(current[y], current[y + 1], ofile))
			{
				tmp = current[y];
				current[y] = current[y + 1];
				current[y + 1] = tmp;
			}
			y += 1;
		}
		i += 1;
	}
}
