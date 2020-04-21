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

t_no *get_no(void)
{
	static t_no no = {};

	return &no;
}

t_ofile *get_ofile(void)
{
	static t_ofile ofile = {};

	return (&ofile);
}

t_options *get_options(void)
{
	static t_options op = {};

	return (&op);
}

char *get_name(void *ptr)
{
	char *result;

	result = get_ofile()->string_table +
			 ((struct nlist *)ptr)->n_un.n_strx;
	return (result ? result : "");
}
