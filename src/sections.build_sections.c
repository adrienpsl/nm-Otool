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

static void *
parse_header(t_ofile *ofile, void *start, uint32_t *p_ncmds)
{
	uint32_t ncmds;
	uint32_t header_size;

	{
		header_size = ofile->x64 ? sizeof(struct mach_header_64)
								 : sizeof(struct mach_header);
		if (true == is_overflow(ofile, start + header_size, true))
			return (NULL);
	}
	{
		ncmds = ofile->x64 ? ((struct mach_header_64 *)start)->ncmds
						   : ((struct mach_header *)start)->ncmds;
		*p_ncmds = swapif_u32(ofile, ncmds);
	}
	start = start + header_size;
	return (start);
}

static bool is_lc_segment(t_ofile *ofile, struct load_command *lc)
{
	bool result;
	uint32_t cmd;

	cmd = swapif_u32(ofile, lc->cmd);
	result = ofile->x64 ? cmd == LC_SEGMENT_64
						: cmd == LC_SEGMENT;
	return (result);
}

static void *
next_command(t_ofile *ofile, void *c_lc)
{
	uint32_t size;

	size = ((t_load_command *)(c_lc))->cmdsize;
	size = swapif_u32(ofile, size);
	c_lc = c_lc + size;
	if (size == 0)
	{
		ft_dprintf(STDERR_FILENO, "load command == 0 ...\n");
		return (NULL);
	}
	else if (true == is_overflow(ofile, c_lc, true))
	{
//		ft_dprintf(STDERR_FILENO, "overflow load command");
		return (NULL);
	}
	else
		return (c_lc);
}

static void
save_symtab_address(t_ofile *ofile, struct load_command *c_lc)
{
	uint32_t cmd;

	cmd = c_lc->cmd;
	cmd = swapif_u32(ofile, cmd);
	if (cmd == LC_SYMTAB)
		ofile->symtab_command = *(struct symtab_command *)c_lc;
}

e_ret build_sections(t_ofile *ofile)
{
	void *c_lc;
	uint32_t ncmds;

	if (NULL ==
		(c_lc = parse_header(ofile, ofile->start, &ncmds)))
		return (KO);
	while (ncmds)
	{
		if (true == is_overflow(ofile, c_lc, true))
			return (KO);
		if (true == is_lc_segment(ofile, c_lc)
			&& add_sections(ofile, c_lc))
			return (KO);
		save_symtab_address(ofile, c_lc);
		if (NULL ==
			(c_lc = next_command(ofile, c_lc)))
			return (KO);
		ncmds = ncmds - 1;
	}
	ft_lst_reverse(&ofile->sections);
	return (OK);
}
