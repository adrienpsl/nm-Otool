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
	void *p_lc;

	p_lc = (
		get_no()->header_64
		?
		get_no()->map + sizeof(struct mach_header_64)
		:
		get_no()->map + sizeof(struct mach_header)
	);
	return (p_lc);
}

static uint32_t get_ncmds()
{
	uint32_t result;
	void *mmap;

	mmap = get_no()->map;
	result = (
		get_no()->header_64
		?
		((struct mach_header_64 *)mmap)->ncmds
		:
		((struct mach_header *)mmap)->ncmds
	);
	return (result);
}

static bool is_lc_segment(struct load_command *lc)
{
	bool result;

	if (get_no()->header_64)
		result = lc->cmd == LC_SEGMENT_64;
	else
		result = lc->cmd == LC_SEGMENT;
	return (result);
}

bool build_segment_list(t_no *no)
{
	uint32_t i;
	struct load_command *lc;

	i = 0;
	lc = setup_lc_start();
	while (i < get_ncmds())
	{
		if (is_lc_segment(lc)
			&& add_link_sectionlst(no, (void *)lc))
			return (EXIT_FAILURE);
		if (lc->cmd == LC_SYMTAB)
			no->symtab_command = lc;
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
	ft_lst_reverse(&no->section_list);
	return (EXIT_SUCCESS);
}

