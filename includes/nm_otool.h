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

# define NM_OPTION_STR "agnopruUmxj"
typedef struct s_options
{
	int a_debugger: 1;
	int n_numeric_sort: 1;
	int o_add_path: 1;
	int p_no_sort: 1;
	int r_rev_sort: 1;
	int u_only_undef: 1;
	int mu_only_no_undef: 1;
	int m_display_all: 1;
	int x_display_sym_hx: 1;
	int j_only_sym: 1;
} t_options;

typedef struct s_no
{
	void *fat_start;
	void *start_map;
	bool is_fat;
	bool is_big;
	void *map_end;
	size_t map_size;
	t_list *section_list;
	void **symbol_list;
	bool header_64;
	void *symtab_command;
	void *map;
	void *string_table;
	char *file_name;
} t_no;

// parse magic
int test_parse_magic_number(t_no *no, void *ptr);

// fat header
void handle_fat_binaries(t_no *no);

int binary_map(char *path, t_no *no);
bool build_section_list(t_no *no);
char get_symbol_letter(t_no *no, struct nlist_64 *sym);
bool build_sym_list(t_no *no, struct symtab_command *symtab_command);

// print
u_int8_t get_debug_type(uint16_t type);

// build
int add_link_section_list(t_no *no, void *p_command);

// option parse
int option_parser(char **av, int ac);

// utils
t_no *get_no(void);
t_options *get_options(void);

// utils
uint32_t swapif32(uint32_t uint_32);
uint64_t swapif64(uint64_t uint_64);

// debug
void print_sym(t_no *no, struct nlist_64 *symbol);
void print_list(t_no *no);

#endif
