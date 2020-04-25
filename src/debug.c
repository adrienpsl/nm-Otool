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

bool print_section(t_list *list, void *p)
{
	struct section_64 *section_64;
	(void)p;

	section_64 = list->content;
	printf("%.16s ", section_64->segname);
	printf("%.16s \n", section_64->sectname);
	return (false);
}

void print_section_list(t_list *list)
{
	ft_listfunc(list, print_section, NULL);
}

void print_sym_name(t_ofile *ofile)
{
	void **array = ofile->symbols;
	uint32_t i = 0;
	struct nlist *nlist;
	void *str_table = ofile->string_table;
	char *result;

	while (array[i])
	{
		nlist = array[i];
		result = str_table + swapif_u32(ofile, nlist->n_un.n_strx);
		printf("%s \n",result);
		i++;
	}
}
