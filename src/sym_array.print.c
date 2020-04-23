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
print_local(struct nlist_64 *symbol, char *symbol_name, char type)
{
	if (!get_options()->a_debugger && type == '-')
		return;
	is_64bits() ? ft_printf("%016llx", symbol->n_value)
				: ft_printf("%08x", symbol->n_value);
	ft_printf(" %c", type);
	if (type == '-' && get_options()->a_debugger)
		ft_printf(" %02d" " %04d" " %5s",
			symbol->n_sect,
			symbol->n_desc,
			get_debug_str(symbol->n_type));
	ft_putstr_lim(symbol_name);
}

void print_sym(t_ofile *ofile, struct nlist_64 *symbol)
{
	char *symbol_name;
	char type;

	// with the name I take the last element?
	symbol_name = get_name(symbol);
	type = get_symbol_type(ofile->sections, symbol);
	if (get_options()->u_only_undef && type == 'U')
		return (ft_putstr_lim(symbol_name));
	else if (type != 'U' && type != 'I')
		return (print_local(symbol, symbol_name, type));
	is_64bits() ? ft_printf("%18c %s", type, symbol_name)
				: ft_printf("%10c %s", type, symbol_name);
	if (type == 'I')
		ft_printf(" (indirect for %s)", symbol_name);
	ft_putchar('\n');
}

void print_sym_array(t_ofile *file)
{
	void **current;

	current = file->symbols;
	while ((*current))
	{
		print_sym(file, *current);
		current += 1;
	}
}
