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

bool cmp_func(struct nlist_64 *l1, struct nlist_64 *l2)
{
	char *string_table;
	char *s1;
	char *s2;
	int res;

	string_table = get_no()->string_table;
	s1 = string_table + (
		get_no()->header_64 ?
		((struct nlist_64 *)l1)->n_un.n_strx
							:
		((struct nlist *)l1)->n_un.n_strx
	);
	s2 = string_table + (
		get_no()->header_64 ?
		((struct nlist_64 *)l2)->n_un.n_strx
							:
		((struct nlist *)l2)->n_un.n_strx
	);
	res = ft_strcmp(s1, s2) >= 0 ? true : false;
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

bool build_symbol_list(t_no *no, struct symtab_command *symtab_command)
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
