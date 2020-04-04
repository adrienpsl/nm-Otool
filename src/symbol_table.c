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
	return (true);
}

