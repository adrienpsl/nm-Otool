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

uint64_t get_size(void *list)
{
	struct nlist *nlist;
	struct nlist_64 *nlist_64;

	nlist = list;
	nlist_64 = list;
	if (is_64bits())
		return nlist_64->n_value;
	else
		return (uint64_t)(nlist->n_value);
}

bool cmp_func(void *l1, void *l2)
{
	int res;

	res = ft_strcmp(
		get_name(l1),
		get_name(l2)
	);
	if (res == 0)
	res = get_size(l1) > get_size(l2);
	res = res > 0 ? true : false;
	return (res);
}

int get_size_array(void **current)
{
	int end;

	end = 0;
	while (current[end])
		end = end + 1;
	return (end);
}

void bubble_sort_symbol_array(void **current)
{
	void *tmp;
	int end;
	int i;
	int y;

	end = get_size_array(current);
	i = 0;
	while (i < end - 1)
	{
		y = 0;
		while (y < end - i - 1)
		{
			if (cmp_func(current[y], current[y + 1]))
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
