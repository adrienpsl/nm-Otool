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


void set_string_table(void)
{
	t_no *no;

	no = get_no();
	no->string_table = no->map
					   + ((struct symtab_command *)no->symtab_command)->stroff;
}

void fill_array_element(t_no *no, uint32_t symoff, int i)
{
	void *nlist;
	uint32_t nlist_size;

	nlist_size = is_64bits() ? sizeof(struct nlist_64) : sizeof(struct nlist);
	nlist = no->map + symoff;
	no->symbol_array[i] = nlist + (i * nlist_size);
}

bool build_sym_array(t_no *no, struct symtab_command *symtab_command)
{
	uint32_t i;

	set_string_table();
	if (NULL == (no->symbol_array = ft_memalloc(
		sizeof(void *) * (symtab_command->nsyms + 1))))
		return (false);
	i = 0;
	while (i < symtab_command->nsyms)
	{
		fill_array_element(no, symtab_command->symoff, i);
		i++;
	}
	bubble_sort_symbol_array(no->symbol_array);
	return (true);
}