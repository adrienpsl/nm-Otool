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

e_ret otool_print(t_ofile *ofile, void *section)
{
	uint64_t start;
	uint64_t end;
	uint64_t offset;
	char *ptr;
	uint64_t i = 0;

	start = is_64bits() ? swapif64(((t_sec_64 *)section)->addr)
						: (uint64_t)swapif_u32(((t_sec *)section)->addr);
	end = is_64bits() ? swapif64(((t_sec_64 *)section)->size)
					  : (uint64_t)swapif_u32(((t_sec *)section)->size);
	offset = is_64bits() ? swapif64(((t_sec_64 *)section)->offset)
						 : (uint64_t)swapif_u32(((t_sec *)section)->offset);
	//	printf("-------- %llx \n", end);

	//	uint64_t padding = is_64bits() ? 0x100000000 : 0x1000;
	//	start = start - padding;
	ptr = ofile->start + offset;
	if (ofile->ht.is_big)
		ptr = ptr - 4;




	//	printf("start File %10p \n", ofile->start);
	//	printf("end File   %10p \n", ofile->end);
	//	printf("ptr        %10p \n", ptr);
	//	printf("addr %016llx    \n", start);
	//	printf("offset %016llx    \n", offset);
	if (!get_no()->is_ar && !get_no()->is_print)
		ft_printf("%s:\n", get_no()->file_name);
	ft_printf("Contents of (__TEXT,__text) section\n");

	uint64_t y;
	if (!ofile->ht.is_big)
	{
		while (i < end)
		{
			y = 0;
			is_64bits() ? ft_printf("%016llx\t", start + y + i)
						: ft_printf("%08llx\t", start + y + i);
			while (y < 16 && (i + y) < end)
			{
				if (true == no_overflow(ptr + i))
					return (KO);
				ft_printf("%02x ", (unsigned char)ptr[y + i]);
				y++;
			}
			ft_printf("\n");
			i += 16;
		}
	}
	else
	{
		while (i < end)
		{
			y = 0;
			is_64bits() ? ft_printf("%016llx\t", start + y + i)
						: ft_printf("%08llx\t", start + y + i);
			while (y < 16 && (i + y) < end)
			{
				if (true == no_overflow(ptr + i))
					return (KO);
				ft_printf("%08x ", swapif64(*(uint64_t *)(ptr + y + i)));
				y = y + 4;
			}
			ft_printf("\n");
			i += 16;
		}
	}
	return (OK);
}
