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

# define NM_OPTION_STR "anopruUxj"
typedef struct s_options
{
	u_int16_t a_debugger: 1;
	u_int16_t n_numeric_sort: 1;
	u_int16_t o_add_path: 1;
	u_int16_t p_no_sort: 1;
	u_int16_t r_rev_sort: 1;
	u_int16_t u_only_undef: 1;
	u_int16_t mu_only_no_undef: 1;
	u_int16_t x_display_sym_hx: 1;
	u_int16_t j_only_sym: 1;
	u_int16_t padding: 7;
} t_options;

typedef struct s_no
{
	int max_debug_name;
	void *fat_start;
	void *start_map;
	bool is_fat;
	bool is_big;
	struct section_64 *section;
	void *map_end;
	size_t map_size;
	t_list *section_list;
	void **symbol_array;
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
char get_symbol_type(t_no *no, struct nlist_64 *sym);
bool build_sym_array(t_no *no, struct symtab_command *symtab_command);

// print

// build
int add_link_section_list(t_no *no, void *p_command);

// option parse
int option_parser(char **av, int ac);

// getters
t_no *get_no(void);
t_options *get_options(void);
char *get_name(void *ptr);

// sort
void bubble_sort_symbol_array(void **current);

// setter
void set_string_table(void);

// test func
bool is_64bits(void);

// utils
uint32_t swapif32(uint32_t uint_32);
uint64_t swapif64(uint64_t uint_64);

// debug
void print_sym(t_no *no, struct nlist_64 *symbol);
void print_sym_array(t_no *no);
char *get_debug_str(uint16_t type);

#endif
