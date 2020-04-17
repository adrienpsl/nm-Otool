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

void print_debug(struct nlist_64 *symbol)
{
	uint8_t debug_sym;

	debug_sym = get_debug_type(symbol->n_type);
	//		if (letter == '-')
	//		{
	//			ft_printf(" %02d", symbol->n_desc);
	//			ft_printf(" %04d", symbol->n_sect);
	//			ft_printf(" %d ", debug_sym);
	//		}
}

void print_sym(t_no *no, struct nlist_64 *symbol)
{
	char *symbol_name;
	char letter;
	struct nlist *n_list;

	// no debug
	if (N_STAB & symbol->n_type)
		return;

	symbol_name = no->string_table + symbol->n_un.n_strx;
	letter = get_symbol_letter(no, symbol);
	if ((*symbol_name) == '\0')
		return;
	n_list = (void *)symbol;
	if (no->header_64 ? symbol->n_value : n_list->n_value)
	{
		if (no->header_64)
			ft_printf("0000000%09llx", symbol->n_value);
		else
			ft_printf("%08x", symbol->n_value);
		ft_printf(" %c %s\n", letter, symbol_name);
	}
	else
	{
		if (no->header_64)
			ft_printf("                 %c %s\n", letter, symbol_name);
		else
			ft_printf("         %c %s\n", letter, symbol_name);
	}
}

// 000000029b500002b20
// 			  00002b20
//            00002b20