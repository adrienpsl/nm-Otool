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

void test(t_no *no, struct nlist_64* symbol)
{
	char *symbol_name;
	char letter;

	symbol_name = no->string_table + symbol->n_un.n_strx;
	letter = get_symbol_letter(no, symbol);
	printf("%c %s \n", letter, symbol_name);
}

bool handle_symtab(t_no *no, struct symtab_command *symtab_command)
{
	struct nlist_64 *symbol_table;
	struct nlist_64 *symbol;
	uint32_t i;

	no->string_table = no->map + symtab_command->stroff;
	symbol_table = no->map + symtab_command->symoff;
	i = 0;

	while (i < symtab_command->nsyms)
	{
		symbol = symbol_table + i;
		test(no, symbol);
		i++;
	}
	return (true);
}

