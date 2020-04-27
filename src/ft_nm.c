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

char *g_nm_usage[] = {
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
	"-x" "\t" "Display  the symbol table entry's fields in hexadecimal,"
	" along with the name as a string",
	"-j" "\t" "Just display the symbol names (no value or type).",
	0
};

int main(int ac, char **av)
{
	int i;
	get_no()->mode = NM;

	i = option_parser(av, ac, NM_OPTION_STR, g_nm_usage);
	if (i == -1)
		exit(EXIT_FAILURE);
	return (start_program(ac, av, i));
}

