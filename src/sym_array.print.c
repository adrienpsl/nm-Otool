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

void print_sym(t_no *no, struct nlist_64 *symbol)
{
	char *symbol_name;
	char letter;
	struct nlist *n_list;

	symbol_name = get_name(symbol);
	letter = get_symbol_letter(no, symbol);
	if (letter == '-' && !get_options()->a_debugger)
		return;
	n_list = (void *)symbol;
	if ((no->header_64 ? symbol->n_value : n_list->n_value) || letter == '-')
	{
		if (no->header_64)
			ft_printf("0000000%09llx", symbol->n_value);
		else
			ft_printf("%08x", symbol->n_value);
		print_debug(symbol, letter);
		ft_printf(" %c %s\n", letter, symbol_name);
	}
	else
	{
		print_debug(symbol, letter);
		if (no->header_64)
			ft_printf("                 %c %s\n", letter, symbol_name);
		else
			ft_printf("         %c %s\n", letter, symbol_name);
	}
}

void print_sym_array(t_no *no)
{
	void **current;

	current = no->symbol_array;
	while ((*current))
	{
		print_sym(no, *current);
		current += 1;
	}
}
