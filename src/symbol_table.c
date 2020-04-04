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

bool cmp_func(struct nlist_64 *l1, struct nlist_64 *l2)
{
	char *string_table;
	char *s1;
	char *s2;

	string_table = get_no()->string_table;
	s1 = string_table + l1->n_un.n_strx;
	s2 = string_table + l2->n_un.n_strx;
	return (ft_strcmp(s1, s2));
}

int get_end(void **current)
{
	int end;

	end = 0;
	while (current[end + 1])
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
	while (i < end)
	{
		y = 0;
		while (y < i)
		{
			if (cmp_func(current[i], current[i + 1]))
			{
				tmp = current[i];
				current[i] = current[i + 1];
				current[i + 1] = tmp;
			}
			y += 1;
		}
		i += 1;
	}
}

bool build_symbol_list(t_no *no, struct symtab_command *symtab_command)
{
	struct nlist_64 *symbol_table;
	uint32_t i;

	i = 0;
	no->string_table = no->map + symtab_command->stroff;
	symbol_table = no->map + symtab_command->symoff;

	if (NULL == (no->symbol_list = ft_memalloc(
		sizeof(void *) * (symtab_command->nsyms + 1))))
		return (false);

	while (i < symtab_command->nsyms)
	{
		no->symbol_list[i] = (symbol_table + i);
		i++;
	}
	sort_symbol_list(no->symbol_list);
	return (true);
}

