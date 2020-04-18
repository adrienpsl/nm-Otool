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

char *usage[] = {
	"ft_nm, look into other's stuff, you can't hide bitch!\n",
	"USAGE: nm [options] <input files>\n\nOPTIONS:",
	"-a" "\t" "Display  all symbol table entries,"
	" including those inserted for use by debuggers.",
	"-n" "\t" "Sort numerically rather than alphabetically.",
	"-o" "\t" "Prepend file or archive element name to each  output  line,"
	" rather than only once.",
	"-p" "\t" "Don't sort; display in symbol-table order.",
	"-r" "\t" "Sort in reverse order.",
	"-u" "\t" "Display only undefined symbols.",
	"-U" "\t" "Don't display undefined symbols.",
	"-m" "\t" "Display all data.",
	"-x" "\t" "Display  the symbol table entry's fields in hexadecimal,"
	" along with the name as a string",
	"-j" "\t" "Just display the symbol names (no value or type).",
	0
};

void print_usage(void)
{
	char **str = usage;
	while (*str)
	{
		ft_printf("%s\n", *str);
		str += 1;
	}
}

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
		(*(uint16_t *)get_options()) |= (uint16_t)1 << position;
		user_input += 1;
	}
	return (EXIT_SUCCESS);
}

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
			print_usage();
			return (-1);
		}
		i++;
	}
	return (i);
}
