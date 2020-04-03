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

# include <nm_otool.h>

// open file and display error if needed
int binary_map(char *path, t_no *no)
{
	int fd;
	struct stat buf;

	if (0 > (fd = open(path, O_RDONLY)))
	{
		ft_dprintf(STDERR_FILENO, NM_NAME": fd open error\n");
		return (EXIT_FAILURE);
	}
	if (0 > fstat(fd, &buf))
	{
		ft_dprintf(STDERR_FILENO, NM_NAME": fstats < 0\n");
		return (EXIT_FAILURE);
	}
	if (MAP_FAILED ==
		(no->map = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)))
	{
		ft_dprintf(2, NM_NAME": mmap failed\n");
		return (EXIT_FAILURE);
	}
	no->map_size = buf.st_size;
	no->map_end = no->map + buf.st_size;
	return (EXIT_SUCCESS);
}

