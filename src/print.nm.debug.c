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

static const t_stabname g_stabname[] = {
	{ N_GSYM,    "GSYM" },
	{ N_FNAME,   "FNAME" },
	{ N_FUN,     "FUN" },
	{ N_STSYM,   "STSYM" },
	{ N_LCSYM,   "LCSYM" },
	{ N_BNSYM,   "BNSYM" },
	{ N_OPT,     "OPT" },
	{ N_RSYM,    "RSYM" },
	{ N_SLINE,   "SLINE" },
	{ N_ENSYM,   "ENSYM" },
	{ N_SSYM,    "SSYM" },
	{ N_SO,      "SO" },
	{ N_OSO,     "OSO" },
	{ N_LSYM,    "LSYM" },
	{ N_BINCL,   "BINCL" },
	{ N_SOL,     "SOL" },
	{ N_PARAMS,  "PARAM" },
	{ N_VERSION, "VERS" },
	{ N_OLEVEL,  "OLEV" },
	{ N_PSYM,    "PSYM" },
	{ N_EINCL,   "EINCL" },
	{ N_ENTRY,   "ENTRY" },
	{ N_LBRAC,   "LBRAC" },
	{ N_EXCL,    "EXCL" },
	{ N_RBRAC,   "RBRAC" },
	{ N_BCOMM,   "BCOMM" },
	{ N_ECOMM,   "ECOMM" },
	{ N_ECOML,   "ECOML" },
	{ N_LENG,    "LENG" },
	{ N_PC,      "PC" },
	{ 0,         0 }
};

static char *
get_debug_str(uint16_t type)
{
	u_int8_t i;

	i = 0;
	while (0 != g_stabname[i].n_type)
	{
		if (g_stabname[i].n_type == type)
			return (g_stabname[i].name);
		i++;
	}
	return ("");
}

void print_debug(t_ofile *ofile, struct nlist *nlist)
{
	(void)ofile;
	ft_printf(" %02d" " %04d" " %5s",
		nlist->n_sect,
		nlist->n_desc,
		get_debug_str(nlist->n_type));
}