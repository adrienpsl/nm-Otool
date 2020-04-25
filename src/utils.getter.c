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

char *get_name(t_ofile *ofile, void *p_nlist)
{
	char *name;
	uint32_t position;

	position = ofile->x64 ? ((struct nlist_64 *)p_nlist)->n_un.n_strx
						  : ((struct nlist *)p_nlist)->n_un.n_strx;
	position = swapif_u32(ofile, position);
	name = ofile->string_table + position;
	if (is_overflow(ofile, name))
		return ("bad string index");
	return (name ? name : "");
}

t_nm_options *get_nm_options(void)
{
	static t_nm_options op = {};

	return (&op);
}

t_no *get_no(void)
{
	static t_no no = {};

	return &no;
}

