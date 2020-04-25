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

int main(int ac, char **av)
{
	t_no *no = get_no();
	(void)ac;

	if (create_mmap(av[1], no))
		return (EXIT_FAILURE);
	if (KO == dispatch(no->mmap_start, no->mmap_start + no->mmap_size))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

// 14x