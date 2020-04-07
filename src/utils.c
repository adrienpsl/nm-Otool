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
	printf("%s \n", section_64->sectname);
	printf("%s \n", section_64->segname);
	return (false);
}

void print_section_list(t_list *list)
{
	ft_listfunc(list, print_section, NULL);
}

uint32_t swapif32(uint32_t uint_32)
{
	return (
		get_no()->is_big
		?
		ft_bswap_32(uint_32)
		:
		uint_32
	);
}

uint64_t swapif64(uint64_t uint_64)
{
	return (
		get_no()->is_big
		?
		ft_bswap_64(uint_64)
		:
		uint_64
	);
}

