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
	(void)ac;
	(void)av;
	t_ofile ofile;
	uint32_t archive = *(uint32_t *)ARMAG;
	(void)archive;
	bool res;

//	uint32_t magic = FAT_CIGAM_64;
	res = handle_magic_number(&ofile, &archive);
	printf("%d \n", res);

	return (EXIT_SUCCESS);
}