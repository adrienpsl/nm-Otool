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

# include "nm_otool.h"

e_ret create_mmap(char *path, t_no *no)
{
	int fd;
	struct stat buf;

	if (0 > (fd = open(path, O_RDONLY)))
	{
		ft_dprintf(ERROR_FD, NM_NAME": fd open error\n");
		return (KO);
	}
	if (0 > fstat(fd, &buf))
	{
		ft_dprintf(ERROR_FD, NM_NAME": fstats < 0\n");
		return (KO);
	}
	if (MAP_FAILED ==
		(no->mmap_start = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)))
	{
		ft_dprintf(ERROR_FD, NM_NAME": mmap failed\n");
		return (KO);
	}
	no->mmap_size = buf.st_size;
	no->file_name = path;
	return (OK);
}

