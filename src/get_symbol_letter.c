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

void *get_link_match_index(t_list *list, int index)
{
	while (index)
	{
		list = list->next;
		index = index - 1;
	}
	return list->content;
}

char get_symbol_section(t_no *no, struct nlist_64 *current_symbol)
{
	struct section_64 *section_64;

	section_64 = get_link_match_index(no->section_list, current_symbol->n_sect);
	printf("%s %d -", section_64->segname, current_symbol->n_sect);
//	printf("%s \n");
	return '5';
}

char get_symbol_letter(t_no *no, struct nlist_64 *sym)
{
	if (N_STAB & sym->n_type)
		return '-'; // Debug symbols
	else if ((N_TYPE & sym->n_type) == N_UNDF)
	{
		//		if (sym->name_not_found)
		//			return 'C';
		//		else
		if (sym->n_type & N_EXT)
			return 'U';
		else
			return '?';
	}
	else if ((N_TYPE & sym->n_type) == N_SECT)
	{
		return get_symbol_section(no, sym);
	}
	else if ((N_TYPE & sym->n_type) == N_ABS)
	{
		return 'A';
	}
	else if ((N_TYPE & sym->n_type) == N_INDR)
	{
		return 'I';
	}
	return ('1');
}
