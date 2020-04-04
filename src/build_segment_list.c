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
#include "ft_list.struct.h"

int add_segment_to_list(t_no *no, struct segment_command_64 *command_64)
{
	struct section_64 *section_64;
	t_list *new;
	uint32_t i;

	i = 0;
	section_64 = (void *)command_64 + sizeof(struct segment_command_64);
	while (i < command_64->nsects)
	{
		if (NULL == (new = ft_lstnew(section_64, 0)))
			return (EXIT_FAILURE);
		new->content = section_64;
		ft_lstadd(&no->section_list, new);
		section_64 = (void *)section_64 + sizeof(struct section_64);
		i++;
	}
	return (EXIT_SUCCESS);
}

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
			&& add_segment_to_list(no, (void *)lc))
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

