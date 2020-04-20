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

static void *setup_lc_start(void)
{
	uint32_t size;
	void *start;

	size = is_64bits() ?
		   sizeof(struct mach_header_64) : sizeof(struct mach_header);
	start = get_no()->map + size;
	is_overflow(start);
	return (start);
}

static uint32_t get_ncmds()
{
	uint32_t result;
	void *mmap;

	mmap = get_no()->map;
	result = (
		is_64bits() ?
		((struct mach_header_64 *)mmap)->ncmds
					:
		((struct mach_header *)mmap)->ncmds
	);
	result = swapif32(result);
	return (result);
}

static bool is_lc_segment(struct load_command *lc)
{
	bool result;
	uint32_t cmd;

	cmd = swapif32(lc->cmd);
	if (is_64bits())
		result = cmd == LC_SEGMENT_64;
	else
		result = cmd == LC_SEGMENT;
	return (result);
}

static void *next_command(struct load_command *lc)
{
	size_t cmd_size;
	void *next;

	cmd_size = swapif32(lc->cmdsize);
	next = (void *)lc + cmd_size;
	is_overflow(next);
	return (next);
}

bool build_section_list(t_no *no)
{
	uint32_t i;
	struct load_command *lc;

	i = 0;
	lc = setup_lc_start();
	while (i < get_ncmds())
	{
		if (is_lc_segment(lc)
			&& add_link_section_list(no, (void *)lc))
			return (EXIT_FAILURE);
		if (swapif32(lc->cmd) == LC_SYMTAB)
			no->symtab_command = lc;
		lc = next_command(lc);
		i++;
	}
	ft_lst_reverse(&no->section_list);
	return (EXIT_SUCCESS);
}
