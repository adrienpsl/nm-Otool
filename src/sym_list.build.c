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

#include <mach-o/nlist.h>
#include "nm_otool.h"
# include "string.h"

uint64_t get_size(void *list)
{
	struct nlist *nlist;
	struct nlist_64 *nlist_64;

	nlist = list;
	nlist_64 = list;
	if (get_no()->header_64)
		return nlist_64->n_value;
	else
		return (uint64_t)(nlist->n_value);
}

char *get_name(struct nlist *ptr)
{
	char *result;

	result = get_no()->string_table +
			 ((struct nlist *)ptr)->n_un.n_strx;
	return (result);
}

bool cmp_func(void *l1, void *l2)
{
	int res;

	res = ft_strcmp(
		get_name(l1),
		get_name(l2)
	) > 0 ? true : false;
	return (res);
}

int get_end(void **current)
{
	int end;

	end = 0;
	while (current[end])
		end = end + 1;
	return (end);
}

void sort_symbol_list(void **current)
{
	void *tmp;
	int end;
	int i;
	int y;

	end = get_end(current);
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

bool build_sym_list(t_no *no, struct symtab_command *symtab_command)
{
	uint32_t i;
	struct nlist *nlist;
	struct nlist_64 *nlist_64;

	i = 0;
	no->string_table = no->map + symtab_command->stroff;
	{
		no->header_64 ?
		(void)(nlist_64 = no->map + symtab_command->symoff) :
		(void)(nlist = no->map + symtab_command->symoff);
	}
	if (NULL == (no->symbol_list = ft_memalloc(
		sizeof(void *) * (symtab_command->nsyms + 1))))
		return (false);
	while (i < symtab_command->nsyms)
	{
		no->symbol_list[i] = (no->header_64 ?
							  (void *)(nlist_64 + i) :
							  (void *)(nlist + i));
		i++;
	}
	sort_symbol_list(no->symbol_list);
	return (true);
}
