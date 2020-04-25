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

static uint32_t
get_nlist_size(t_ofile *ofile)
{
	uint32_t nlist_size;

	nlist_size = ofile->x64 ? sizeof(struct nlist_64)
							: sizeof(struct nlist);
	return (nlist_size);
}

static e_ret
set_string_table(t_ofile *ofile, struct symtab_command *sym)
{
	void *string_table;

	string_table = ofile->start + sym->stroff;
	if (is_overflow(ofile, string_table))
		return (KO);
	ofile->string_table = string_table;
	return (OK);
}

static e_ret
fill_array_element(t_ofile *ofile, uint32_t symoff, uint32_t i)
{
	void *start_nlist;
	void *nlist_el;
	start_nlist = ofile->ptr + symoff;
	nlist_el = start_nlist + (i * get_nlist_size(ofile));
	if (true == is_overflow(ofile, nlist_el))
		return (KO);

//	char *result;
//	result = ofile->string_table + swapif_u32(ofile, ((struct nlist*)nlist_el)->n_un.n_strx);
//	printf("%s \n",result);

	ofile->symbols[i] = nlist_el;
	return (OK);
}

static void
sym_handle_big_endian(t_ofile *ofile, struct symtab_command *sym)
{
	sym->nsyms = swapif_u32(ofile, sym->nsyms);
	sym->stroff = swapif_u32(ofile, sym->stroff);
	sym->symoff = swapif_u32(ofile, sym->symoff);
}

int build_symtab(t_ofile *ofile)
{
	struct symtab_command *sym;
	uint32_t i;

	sym = &ofile->symtab_command;
	sym_handle_big_endian(ofile, sym);
	if (KO == set_string_table(ofile, sym))
		return (KO);
	if (NULL ==
		(ofile->symbols = ft_memalloc(
			(sym->nsyms + 1) * get_nlist_size(ofile))))
		return (KO);
	i = 0;
	while (i < sym->nsyms)
	{
		if (KO == fill_array_element(ofile, sym->symoff, i))
			return (KO);
		i = i + 1;
	}
	//	if (!get_options()->p_no_sort)
	//		bubble_sort_symbol_array(ofile->symbols);
	return (OK);
}