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

static e_ret setup_lc_start(void **ptr)
{
	uint32_t size;
	void *start;

	size = is_64bits() ? sizeof(struct mach_header_64)
					   : sizeof(struct mach_header);
	start = get_ofile()->ptr + size;
	*ptr = start;
	return (is_overflow(start, 0));
}

static uint32_t get_ncmds(void *ptr)
{
	uint32_t result;

	result = is_64bits() ? ((struct mach_header_64 *)ptr)->ncmds
						 : ((struct mach_header *)ptr)->ncmds;
	result = swapif_u32(result);
	return (result);
}

static bool is_lc_segment(struct load_command *lc)
{
	bool result;
	uint32_t cmd;

	cmd = swapif_u32(lc->cmd);
	result = is_64bits() ? cmd == LC_SEGMENT_64
						 : cmd == LC_SEGMENT;
	return (result);
}

static uint8_t next_command(void **p_lc)
{
	size_t cmd_size;
	t_load_command *next;

	next = *p_lc;
	cmd_size = swapif_u32(next->cmdsize);
	next = (void *)next + cmd_size;
	*p_lc = next;
	return (is_overflow(next, 0));
}

e_ret build_section_list(t_ofile *ofile)
{
	void *lc;
	uint32_t i;
	uint32_t ncmds;

	i = 0;
	if (KO == setup_lc_start(&lc))
		return (KO);
	ncmds = get_ncmds(ofile->start);
	while (i < ncmds)
	{
		if (is_lc_segment(lc)
			&& add_link_section_list(ofile, lc))
			return (KO);
		if (swapif_u32(((t_load_command *)lc)->cmd) == LC_SYMTAB)
			ofile->symtab_command = lc;
		if (KO == next_command(&lc))
			return (KO);
		i++;
	}
	ft_lst_reverse(&ofile->sections);
	return (OK);
}
