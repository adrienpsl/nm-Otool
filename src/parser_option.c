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

int search_in_available_option(char *options, char *user_input)
{
	char *found;
	long int position;

	while (*user_input != '\0')
	{
		found = ft_strchr(options, *user_input);
		if (NULL == found)
			return (EXIT_FAILURE);
		position = found - options;
		get_options() |= 1 << position;
		user_input += 1;
	}
	return (EXIT_SUCCESS);
}

// loop on the element and add by matching with my str option
// retun -1 if pb, the new loop if ok
// # define NM_OPTION_STR " agnopruUmxj "
int option_parser(char **av, int ac)
{
	int i;

	i = 1;
	while (i < ac)
	{
		if (av[i][0] == '\0')
			return (i);
		if (av[i][0] != '-')
			break;
		if (search_in_available_option(NM_OPTION_STR, av[i] + 1))
		{
			ft_printf("usage bitch\n");
			return (-1);
		}
		i++;
	}
	return (i);
}
