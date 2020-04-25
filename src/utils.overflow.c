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

bool is_overflow(t_ofile *ofile, void *ptr)
{
	bool result;

	result = !(ptr >= ofile->start && ptr <= ofile->end);
	ft_dprintf(STDERR_FILENO, "The ptr is not in the file\n");
	return (result);
}

bool is_overflow_or_come_back(t_ofile *ofile, void *current, void *next)
{
	bool result;

	result = is_overflow(ofile, next);
	if (result == true)
		return (result);
	result = next > current;
	return (result);
}
