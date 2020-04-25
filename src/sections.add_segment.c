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
parse_segment_command(t_ofile *ofile,
					  void *start,
					  uint32_t *p_nsects)
{
	uint32_t header_size;
	uint32_t nsects;

	{
		header_size = ofile->x64 ? sizeof(struct segment_command_64)
								 : sizeof(struct segment_command);
		if (true == is_overflow(ofile, start + header_size))
			return (NULL);
	}
	{
		nsects = ofile->x64 ? ((struct segment_command_64 *)start)->nsects
							: ((struct segment_command *)start)->nsects;
		*p_nsects = swapif_u32(ofile, nsects);
	}
	start = start + header_size;
	return (start);
}

static void *
get_next_section(t_ofile *ofile, void *c_section)
{
	uint32_t section_size;

	section_size = ofile->x64 ? sizeof(struct section_64)
							  : sizeof(struct section);
	c_section = c_section + section_size;
	return (c_section);
}

e_ret add_sections(t_ofile *ofile, void *start)
{
	void *c_section;
	t_list *new;
	uint32_t nsects;

	if (NULL ==
		(c_section = parse_segment_command(ofile, start, &nsects)))
		return (KO);
	while (nsects)
	{
		if (true == is_overflow(ofile, c_section))
			return (KO);
		if (NULL == (new = ft_lstnew(c_section, 0)))
			return (KO);
		new->content = c_section;
		ft_lstadd(&ofile->sections, new);
		c_section = get_next_section(ofile, c_section);
		//		if (get_no()->mode &&
		//			!ft_strcmp(((struct section *)section)->sectname, SECT_TEXT))
		//			return (otool_print(ofile, section));
		nsects--;
	}
	return (OK);
}
