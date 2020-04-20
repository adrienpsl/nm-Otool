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

void
print_local_and_debug(struct nlist_64 *symbol, char *symbol_name, char type)
{
	is_64bits() ? ft_printf("%016llx", symbol->n_value)
				: ft_printf("%08x", symbol->n_value);
	if (type == '-' && get_options()->a_debugger)
		ft_printf(" %02d" " %04d" " %5s",
			symbol->n_sect,
			symbol->n_desc,
			get_debug_str(symbol->n_type));
	ft_printf(" %c", type);
	ft_printf(" %s\n", symbol_name);
}

void print_op_u(struct nlist_64 *symbol, char *symbol_name, char type)
{
	if (!get_options()->a_debugger && type == '-')
		return;
	else if (get_options()->u_only_undef && type == 'U')
		ft_printf(" %s\n", symbol_name);
	else if (get_options()->mu_only_no_undef && type != 'U')
		print_local_and_debug(symbol, symbol_name, type);

	print_local_and_debug(symbol, symbol_name, type);
}

void print_sym(t_no *no, struct nlist_64 *symbol)
{
	char *symbol_name;
	char type;

	symbol_name = get_name(symbol);
	type = get_symbol_type(no, symbol);
	if ((is_64bits() ? symbol->n_value : ((struct nlist *)symbol)->n_value)
		|| type == '-')
		print_op_u(symbol, symbol_name, type);
	else
	{
		is_64bits() ?
		ft_printf("%18c %s\n", type, symbol_name) :
		ft_printf("%10c %s\n", type, symbol_name);
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
