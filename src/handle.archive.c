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

int ar_header_size(void *ptr, char *ar_name)
{
	int size;

	size = 0;
	if (!ft_strncmp(ptr, AR_EFMT1, ft_strlen(AR_EFMT1)))
		size = ft_atoi(ar_name + ft_strlen(AR_EFMT1));
	return (size);
}

void *next_ar(void *c_ar)
{
	void *next;
	int32_t size;

	size = ft_atoi(((struct ar_hdr *)c_ar)->ar_size);
	if (size <= 0)
	{
		ft_dprintf(STDERR_FILENO, "archive size <= 0\n");
		return (NULL);
	}
	next = c_ar + size + sizeof(struct ar_hdr);
	return (next);
}

static e_ret
launch_dispatch(t_ofile *arch_option, struct ar_hdr *ar_hdr)
{
	int32_t size_name;
	int32_t ar_size;
	void *start;
	void *end;
	(void)arch_option;

	size_name = ar_header_size(ar_hdr, ar_hdr->ar_name);
	ar_size = ft_atoi(ar_hdr->ar_size);
	if (ar_size <= 0)
		return (KO);
	start = (void *)ar_hdr + sizeof(struct ar_hdr) + size_name;
	end = start + ar_size - size_name;
	if (true == is_overflow(arch_option, start, true)
		|| true == is_overflow(arch_option, end, true))
		return (KO);
	return (dispatch(start, end, arch_option));
}

e_ret handle_archive(t_ofile *arch_option, void *start, void *end)
{
	(void)arch_option;
	void *c_ar;
	int i = 0;

	c_ar = start + SARMAG;
	c_ar = next_ar(c_ar);
	if (get_no()->mode != NM)
		ft_printf("Archive : %s\n", arch_option->file_name);
	arch_option->no_print_file_otool = true;
	while (c_ar < end)
	{
		if (true == is_overflow(arch_option, c_ar, true))
			return (KO);
		if (get_no()->mode == NM)
			ft_putchar('\n');
		ft_printf("%s(%s):\n", arch_option->file_name,
			c_ar + sizeof(struct ar_hdr));
		launch_dispatch(arch_option, c_ar);
		c_ar = next_ar(c_ar);
		i = i + 1;
	}
	return (OK);
}