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

e_ret set_string_table(t_ofile *ofile)
{
	ofile->string_table = ofile->start
						  + ((struct symtab_command *)ofile->symtab_command)->stroff;
	return (is_overflow(ofile->string_table, 0) ? KO : OK);
}

void fill_array_element(t_ofile *ofile, uint32_t symoff, int i)
{
	void *nlist;
	uint32_t nlist_size;
	void *name_ptr;

	nlist_size = is_64bits() ? sizeof(struct nlist_64) : sizeof(struct nlist);
	nlist = ofile->ptr + symoff;
	name_ptr = nlist + (i * nlist_size);
	is_overflow(name_ptr, 0);
	ofile->symbols[i] = name_ptr;
}

int build_sym_array(t_ofile *ofile, struct symtab_command *symtab_command)
{
	uint32_t i;

	set_string_table(ofile);
	if (NULL == (ofile->symbols = ft_memalloc(
		sizeof(void *) * (symtab_command->nsyms + 1))))
		return (KO);
	i = 0;
	while (i < symtab_command->nsyms)
	{
		fill_array_element(ofile, symtab_command->symoff, i);
		i++;
	}
	if (!get_options()->p_no_sort)
		bubble_sort_symbol_array(ofile->symbols);
	return (OK);
}
