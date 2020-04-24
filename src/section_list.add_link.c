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

static e_ret setup_start_section(void *start, void **p_section)
{
	is_64bits() ? (*p_section = start + sizeof(struct segment_command_64))
				: (*p_section = start + sizeof(struct segment_command));
	return (no_overflow_no_goback(*p_section, 0));
}

static uint32_t get_nsects(void *p_command)
{
	uint32_t result;

	is_64bits() ? (result = ((struct segment_command_64 *)p_command)->nsects)
				: (result = ((struct segment_command *)p_command)->nsects);
	return (swapif_u32(result));
}

static e_ret get_next_section(void **section)
{
	is_64bits() ? (*section = *section + sizeof(struct section_64))
				: (*section = *section + sizeof(struct section));
	return (no_overflow_no_goback(*section, 0));
}

e_ret add_link_section_list(t_ofile *ofile, void *start)
{
	void *section;
	t_list *new;
	uint32_t i;
	uint32_t nsects;

	i = 0;
	nsects = get_nsects(start);
	if (setup_start_section(start, &section))
		return (KO);

	while (i < nsects)
	{
		if (NULL == (new = ft_lstnew(section, 0)))
			return (KO);
		if (get_no()->mode &&
			!ft_strcmp(((struct section *)section)->sectname, SECT_TEXT))
			return (otool_print(ofile, section));
		new->content = section;
		ft_lstadd(&ofile->sections, new);
		if (get_next_section(&section))
			return (KO);
		i++;
	}
	return (OK);
}

