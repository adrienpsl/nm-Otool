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

# include "libft.h"
# include "ft_printf.h"
# include "ft_list.struct.h"

# include <stdbool.h>
# include <stdio.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/mman.h>
# include "mach-o/fat.h"
# include <mach-o/nlist.h>
# include <mach-o/loader.h>

# define NM_NAME "nm"

typedef enum HEADER_TYPE
{
	HEADER,
	HEADER_64
} e_header_type;

typedef struct s_no
{
	void *fat_start;
	void *start_map;
	bool is_fat;
	bool is_big;
	void *map_end;
	size_t map_size;
	t_list *section_list;
	e_header_type header_type;
	void **symbol_list;
	bool header_64;
	void *symtab_command;
	void *map;
	void *string_table;
	char *file_name;
} t_no;


int binary_map(char *path, t_no *no);
bool build_segment_list(t_no *no);
char get_symbol_letter(t_no *no, struct nlist_64 *sym);
bool build_symbol_list(t_no *no, struct symtab_command *symtab_command);

// print
u_int8_t get_debug_type(uint16_t type);

// build
int add_link_sectionlst(t_no *no, void *p_command);

// utils
t_no *get_no(void);

// utils
uint32_t swapif32(uint32_t uint_32);
uint64_t swapif64(uint64_t uint_64);

// debug
void print_sym(t_no *no, struct nlist_64 *symbol);
void print_list(t_no *no);

#endif
