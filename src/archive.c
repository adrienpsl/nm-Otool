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

e_ret next_ar(void **p_ar, t_ar_hdr *ar_hdr)
{
	void *next;

	next = (*p_ar) + ft_atoi(ar_hdr->ar_size) + sizeof(t_ar_hdr);
	*p_ar = next;
	return (no_overflow_no_goback(next, 0));
}

e_ret handle_archive(t_no *no, void *start)
{
	t_ar_hdr *ar_hdr;
	void *ptr;
	int name_size;

	ptr = start + SARMAG;
	if (next_ar(&ptr, ptr))
		return (KO);
	if (no->mode)
		ft_printf("Archive : %s\n", no->file_name);
	while (ptr < no->mmap_start + no->mmap_size)
	{
		ar_hdr = ptr;
		name_size = ar_header_size(ptr, ar_hdr->ar_name);
		if (!no->mode)
			ft_putchar('\n');
		ft_printf("%s(%s):\n", no->file_name, ptr + sizeof(t_ar_hdr));
		if (handle_maco(ptr + sizeof(t_ar_hdr) + name_size,
			ft_atoi(ar_hdr->ar_size), 0))
			return (KO);
		if (next_ar(&ptr, ptr))
			return (KO);
	}
	return (OK);
}
