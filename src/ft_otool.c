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

char *g_otool_usage[] = {
	"-t print the text section",
	0
};

int main(int ac, char **av)
{
	int i;

	get_no()->mode = OTOOL;
	i = option_parser(av, ac, OTOOL_OPTION_STR, g_otool_usage);
	if (i == -1)
		exit(EXIT_FAILURE);
	return (start_program(ac, av, 0));
}

