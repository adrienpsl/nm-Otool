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
print_extern(t_ofile *ofile, t_nm_options *options, char *name,
			 char type)
{
	int padding;

	padding = ofile->x64 ? 18 : 10;
	if (type != 'U' && options->mu_only_no_undef)
		return;
	if (type == 'U' && options->u_only_undef)
		ft_putstrnl_lim(ofile, name);
	else if (type == 'U')
	{
		ft_printf("%*c ", padding, type);
		ft_putstrnl_lim(ofile, name);
	}
	else if (type == 'I')
	{
		ft_printf("%*c ", padding, type, name, name);
		ft_putstrnl_lim(ofile, name);
		ft_printf(" (indirect for ");
		ft_putstrnl_lim(ofile, name);
		ft_printf(")");
	}
	ft_putchar('\n');
}

void print_address(t_ofile *ofile, void *nlist)
{
	uint32_t val32;
	uint64_t val64;

	if (ofile->x64)
	{
		val64 = ((struct nlist_64 *)nlist)->n_value;
		val64 = swapif_u64(ofile, val64);
		ft_printf("%016llx", val64);
	}
	else
	{
		val32 = ((struct nlist *)nlist)->n_value;
		val32 = swapif_u32(ofile, val32);
		ft_printf("%08x", val32);
	}
}

static void
print_intern(t_ofile *ofile, void *nlist, char *name, char type)
{
	t_nm_options *options;

	options = get_nm_options();
	if (0 == options->a_debugger && type == '-')
		return;
	print_address(ofile, nlist);
	ft_printf(" %c ", type);
	if (type == '-')
		print_debug(nlist);
	ft_putstrnl_lim(ofile, name);
	ft_putchar('\n');
}

void print_sym(t_ofile *ofile, t_nm_options *options, void *symbol)
{
	char *name;
	char type;

	name = get_name(ofile, symbol);
	type = get_symbol_type(ofile->sections, symbol);

	if (type == 'U' || type == 'I')
		print_extern(ofile, options, name, type);
	else
		print_intern(ofile, symbol, name, type);
}

e_ret print_nm(t_ofile *ofile, t_nm_options *options)
{
	void **current;
	uint32_t i = 0;

	current = ofile->symbols;
	while (current[i])
	{
		print_sym(ofile, options, current[i]);
		i++;
	}
	return (OK);
}