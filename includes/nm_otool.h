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

#ifndef NM_OTOOL_H
#define NM_OTOOL_H

# include "stdio.h"
# include <sys/stat.h>
# include <fcntl.h>
#include <ft_printf.h>
#include <stdlib.h>
#include <sys/mman.h>

# define NM_NAME "nm"

typedef struct s_no
{
	void *map_end;
	size_t map_size;
	void *map;
} t_no;


int binary_map(char *path, t_no *no);


#endif
