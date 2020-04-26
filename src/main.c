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
	t_no *no;
	int i;

	no = get_no();
	i = option_parser(av, ac);
	get_no()->mode = 1;
	while (i < ac)
	{
		if (create_mmap(av[i], no))
		{
			i++;
			continue;
		}
		dispatch(no->mmap_start, no->mmap_start + no->mmap_size, NULL);
		munmap(no->mmap_start, no->mmap_size);
		i++;
	}
	return (EXIT_SUCCESS);
}

