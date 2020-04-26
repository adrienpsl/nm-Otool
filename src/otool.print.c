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

void set_up_and_check(t_ofile *ofile, t_otool *otool, void *section)
{
	otool->start =
		ofile->x64
		? swapif_u64(ofile, ((struct section_64 *)section)->addr)
		: (uint64_t)swapif_u32(ofile, ((struct section *)section)->addr);
	otool->end =
		ofile->x64
		? swapif_u64(ofile, ((struct section_64 *)section)->size)
		: (uint64_t)swapif_u32(ofile, ((struct section *)section)->size);
	otool->offset =
		ofile->x64
		? swapif_u64(ofile, ((struct section_64 *)section)->offset)
		: (uint64_t)swapif_u32(ofile, ((struct section *)section)->offset);
	otool->padding = ofile->x64 ? 0x100000000 : 0x1000;
	otool->ptr = ofile->start + otool->offset;
}

void not_big_endian_arch(t_ofile *ofile, t_otool *otool)
{
	uint64_t i;
	uint64_t y;
	i = 0;

	while (i < otool->end)
	{
		y = 0;
		ofile->x64 ? ft_printf("%016llx\t", otool->start + y + i)
				   : ft_printf("%08llx\t", otool->start + y + i);
		while (y < 16 && (i + y) < otool->end)
		{
			if (true == is_overflow(ofile, otool->ptr + i + y, true))
				return;
			ft_printf("%02x ", (unsigned char)(otool->ptr)[y + i]);
			y++;
		}
		ft_printf("\n");
		i += 16;
	}
}

void big_endian(t_ofile *ofile, t_otool *otool)
{
	uint64_t i;
	uint64_t y;
	i = 0;

	otool->ptr = otool->ptr - 4;
	while (i < otool->end)
	{
		y = 0;
		ofile->x64 ? ft_printf("%016llx\t", otool->start + y + i)
				   : ft_printf("%08llx\t", otool->start + y + i);
		while (y < 16 && (i + y) < otool->end)
		{
			if (true == is_overflow(ofile, otool->ptr + i + y, true))
				return;
			ft_printf("%08x ",
				swapif_u64(ofile, *(uint64_t *)(otool->ptr + y + i)));
			y = y + 4;
		}
		ft_printf("\n");
		i += 16;
	}
}

e_ret otool_print(t_ofile *ofile, void *section)
{
	t_otool otool;

	if (true == is_overflow(ofile, section + sizeof(struct section_64), true))
		return (KO);
	if (false == ofile->no_print_file_otool)
		ft_printf("%s:\n", get_no()->file_name);
	ft_printf("Contents of (__TEXT,__text) section\n");

	set_up_and_check(ofile, &otool, section);
	if (ofile->big_endian)
		big_endian(ofile, &otool);
	else
		not_big_endian_arch(ofile, &otool);



	//	if (ofile->ht.is_big)

	//	printf("start File %10p \n", ofile->start);
	//	printf("end File   %10p \n", ofile->end);
	//	printf("ptr        %10p \n", otool.ptr);
	//	printf("addr %016llx    \n", otool.start);
	//	printf("offset %016llx    \n", otool.offset);
	//	if (!get_no()->is_ar && !get_no()->is_print)

	return (OK);
}
//	else
//	{
//	}
//return (OK);
//}
//