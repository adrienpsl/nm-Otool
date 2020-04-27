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
	"-p" "\t" "Don't sort; display in symbol-table order.",
	"-r" "\t" "Sort in reverse order.",
	0
};

int main(int ac, char **av)
{
	static char *no_argument[] = { "a.out", 0 };
	int i;
	get_no()->mode = NM;

	i = option_parser(av, ac, NM_OPTION_STR, g_nm_usage);
	if (i == -1)
		exit(EXIT_FAILURE);
	if (i == ac)
	{
		av = no_argument;
		i = 0;
		ac = 1;
	}
	return (start_program(ac, av, i));
}
