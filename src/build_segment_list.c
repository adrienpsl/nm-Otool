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


bool build_segment_list(t_no *no)
{
	uint32_t i;
	struct mach_header_64 *header_64;
	struct load_command *lc;

	header_64 = no->map;
	i = 0;
	lc = no->map + sizeof(struct mach_header_64);
	while (i < header_64->ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64
			&& add_link_sectionlst(no, (void *)lc))
			return (EXIT_FAILURE);
		// todo faire une function qui fais ca.
		if (lc->cmd == LC_SYMTAB)
			no->symtab_command = lc;
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
	ft_lst_reverse(&no->section_list);
	return (EXIT_SUCCESS);
}

