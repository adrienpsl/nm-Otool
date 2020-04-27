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

void print_usage(char **usage)
{
	while (*usage)
	{
		ft_printf("%s\n", *usage);
		usage += 1;
	}
}

int search_in_available_options(char *options, const char *user_input)
{
	char *found;
	long int position;

	while (*user_input != '\0')
	{
		found = ft_strchr(options, *user_input);
		if (NULL == found)
			return (EXIT_FAILURE);
		position = found - options;
		(*(uint16_t *)get_nm_options()) |= (uint16_t)1 << position;
		user_input += 1;
	}
	return (EXIT_SUCCESS);
}

int option_parser(char **av, int ac, char *options, char **usage)
{
	int i;

	i = 1;
	while (i < ac)
	{
		if (av[i] == NULL || av[i][0] == '\0')
			return (i);
		if (av[i][0] != '-')
			break;
		if (search_in_available_options(options, av[i] + 1))
		{
			print_usage(usage);
			return (-1);
		}
		i++;
	}
	return (i);
}
