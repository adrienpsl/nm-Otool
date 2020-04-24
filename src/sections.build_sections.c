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

// check if I can go, and if I can go
static e_ret get_ncmds(t_ofile *ofile, void *ptr, uint32_t *ncmds)
{
	uint32_t result;
	uint32_t header_size;

	header_size = ofile->x64 ? sizeof(struct mach_header_64)
							 : sizeof(struct mach_header);
	if (true == is_overflow(ofile, ptr + header_size))
		return (KO);
	result = ofile->x64 ? ((struct mach_header_64 *)ptr)->ncmds
						: ((struct mach_header *)ptr)->ncmds;
	*ncmds = swapif_u32(ofile, result);
	return (OK);
}

// passe the maco header with the magic number and
// other shit, verifie que je peux lire dans le ncmds
static e_ret set_first_lc(t_ofile *ofile, void **p_lc)
{
	uint32_t header_size;
	uint32_t load_command_size;
	void *new_ptr;

	header_size = ofile->x64 ? sizeof(struct mach_header_64)
							 : sizeof(struct mach_header);
	load_command_size = sizeof(struct load_command);
	new_ptr = ofile->start + header_size;
	if (true == is_overflow(ofile, new_ptr + load_command_size))
		return (KO);
	else
		*p_lc = new_ptr;
	return (OK);
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

static e_ret next_command(t_ofile *ofile, void **p_current_lc)
{
	void *next;
	uint32_t size;

	size = ((t_load_command *)(*p_current_lc))->cmdsize;
	size = swapif_u32(ofile, size);
	next = *p_current_lc + size;
	if (size == 0)
	{
		ft_dprintf(STDERR_FILENO, "load command == 0 ...");
		return (KO);
	}
	else if (true == is_overflow(ofile, next))
	{
		ft_dprintf(STDERR_FILENO, "overflow load command");
		return (KO);
	}
	else
	{
		*p_current_lc = next;
		return (O);
	}
}

e_ret build_sections(t_ofile *ofile)
{
	void *current_lc;
	uint32_t i;
	uint32_t ncmds;

	i = 0;
	if (KO == get_ncmds(ofile, ofile->start, &ncmds)
		|| KO == set_first_lc(ofile, &current_lc))
		return (KO);
	while (i < ncmds)
	{
		if (true == is_lc_segment(ofile, current_lc)
			&& add_link_section_list(ofile, current_lc))
			return (KO);
		if (swapif_u32(((t_load_command *)current_lc)->cmd) == LC_SYMTAB)
			ofile->symtab_command = current_lc;
		if (KO == next_command((void *)&current_lc))
			return (KO);
		i++;
	}
	ft_lst_reverse(&ofile->sections);
	return (OK);
}
