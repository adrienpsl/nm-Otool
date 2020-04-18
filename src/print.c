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

void print_debug(struct nlist_64 *symbol, char letter)
{
	char *debug_sym;

	if (letter != '-')
		return;
	debug_sym = get_debug_type(symbol->n_type);
	ft_printf(" %02d", symbol->n_sect);
	ft_printf(" %04d", symbol->n_desc);
	ft_printf(" %s ", debug_sym);
}
