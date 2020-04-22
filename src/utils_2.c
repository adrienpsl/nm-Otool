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

void ft_putstr_lim(char *str)
{
	void *limit;
	int i;
	
	limit = get_no()->mmap_start + get_no()->mmap_size;
	i = 0;
	ft_putchar(' ');
	while (str[i])
	{
		ft_putchar(str[i]);
	    i++;
		if ((str + i) == limit)
			return;
	}
	ft_putchar('\n');
}
