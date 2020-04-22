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

#include <nm_otool.h>

static void setup_start_section(
	void *p_command,
	void **section_64,
	void **section
)
{
	get_ofile()->header_64 ?
	(void)(*section_64 = p_command + sizeof(struct segment_command_64))
						:
	(void)(*section = p_command + sizeof(struct segment_command));
	no_overflow_no_goback(p_command);
}

static uint32_t get_nsects(void *p_command)
{
	uint32_t result;

	result = (
		get_ofile()->header_64 ?
		((struct segment_command_64 *)p_command)->nsects
							:
		((struct segment_command *)p_command)->nsects
	);
	return (result);
}

static void get_next_section(
	void **section_64,
	void **section
)
{
	get_ofile()->header_64 ?
	(void)(*section_64 = *section_64 + sizeof(struct section_64))
						:
	(void)(*section = *section + sizeof(struct section));
}

e_ret add_link_section_list(t_ofile *ofile, void *p_command)
{
	void *section_64;
	void *section;
	t_list *new;
	uint32_t i;

	i = 0;
	setup_start_section(p_command, (void **)&section_64, &section);
	while (i < get_nsects(p_command))
	{
		if (NULL == (new = ft_lstnew(section_64, 0)))
			return (KO);
		new->content = (ofile->header_64 ? (void *)section_64 : (void *)section);
		ft_lstadd(&ofile->sections, new);
		get_next_section(&section_64, &section);
		i++;
	}
	return (OK);
}

