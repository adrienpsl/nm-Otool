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

# include "stdbool.h"
# include "stdio.h"
# include <sys/stat.h>
# include <fcntl.h>
#include <ft_printf.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <mach-o/nlist.h>
#include <ft_list.struct.h>
# include "mach-o/loader.h"
# include "libft.h"

# define NM_NAME "nm"

typedef struct s_no
{
	void *map_end;
	size_t map_size;
	t_list *section_list;
	void **symbol_list;
	void *symtab_command;
	void *map;
	void *string_table;
} t_no;


int binary_map(char *path, t_no *no);
bool build_segment_list(t_no *no);
char get_symbol_letter(t_no *no, struct nlist_64 *sym);
bool build_symbol_list(t_no *no, struct symtab_command *symtab_command);

void print_sym(t_no *no, struct nlist_64 *symbol);
void print_list(t_no *no);

#endif
