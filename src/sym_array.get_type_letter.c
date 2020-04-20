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
	while (index && list)
	{
		list = list->next;
		index = index - 1;
	}
	return (list ? list->content : NULL);
}

char get_symbol_section(t_no *no, struct nlist_64 *current_symbol)
{
	struct section_64 *section_64;
	char ret;

	section_64 = get_link_match_index(no->section_list,
		current_symbol->n_sect - 1);
	no->section = section_64;
	if (!ft_strcmp(section_64->sectname, SECT_TEXT))
		ret = 'T';
	else if (!ft_strcmp(section_64->sectname, SECT_DATA))
		ret = 'D';
	else if (!ft_strcmp(section_64->sectname, SECT_BSS))
		ret = 'B';
	else
		ret = 'S';
	if (!(current_symbol->n_type & N_EXT))
		ret -= 'A' - 'a';
	return (ret);
}

char get_symbol_type(t_no *no, struct nlist_64 *sym)
{
	if (N_STAB & sym->n_type)
		return ('-');
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
		return get_symbol_section(no, sym);
	else if ((N_TYPE & sym->n_type) == N_ABS)
		return 'A';
	else if ((N_TYPE & sym->n_type) == N_INDR)
		return 'I';
	return ('1');
}
