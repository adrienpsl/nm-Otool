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

# include <mach-o/fat.h>
# include <mach-o/nlist.h>
# include <mach-o/loader.h>
# include <mach-o/stab.h>
# include <ar.h>

# define NM_NAME "nm"
# define ERROR_FD 1
# define NM_ERROR_START "/Library/Developer/CommandLineTools/usr/bin/nm: "
# define ARCH

typedef enum
{
	OK,
	KO
} e_ret;

# define NM_OPTION_STR "anpr"
# define OTOOL_OPTION_STR "t"
typedef struct s_options
{
	u_int16_t a_debugger: 1;
	u_int16_t n_numeric_sort: 1;
	u_int16_t p_no_sort: 1;
	u_int16_t r_rev_sort: 1;
	u_int16_t u_only_undef: 1;
	u_int16_t mu_only_no_undef: 1;
	u_int16_t padding:10;
} t_nm_options;

typedef struct s_ofile
{
	bool x64;
	bool big_endian;
	bool fat_header;
	bool archive;
	void *ptr;
	void *start;
	void *end;
	void **symbols;
	uint32_t symbols_size;
	t_list *sections;
	struct symtab_command symtab_command;
	void *string_table;
	char *file_name;
	void *otool_section;
	int is_print;
	bool no_print_file_otool;
} t_ofile;

# define NM 0
# define OTOOL 1

typedef struct s_no
{
	void *mmap_start;
	size_t mmap_size;
	char *file_name;
	int mode;
} t_no;

typedef struct s_stabname
{
	unsigned char n_type;
	char *name;
} t_stabname;

typedef struct		s_otool
{
	uint64_t start;
	uint64_t end;
	uint64_t offset;
	uint64_t padding;
	char *ptr;

} 					t_otool;

int start_program(int ac, char **av, int i);

int option_parser(char **av, int ac, char *options, char **usage);
e_ret otool_print(t_ofile *ofile, void *section);

bool handle_magic_number(t_ofile *ofile, uint32_t *magic);
e_ret handle_archive(t_ofile *ofile, void *start, void *end);
e_ret handle_fat_arch(t_ofile *fat_option, void *start, bool print_all);
e_ret handle_maco(t_ofile *ofile);
e_ret dispatch(void *start, void *end, t_ofile *prev);


e_ret add_sections(t_ofile *ofile, void *start);
e_ret build_sections(t_ofile *ofile);

int build_symtab(t_ofile *ofile);

// print
char get_symbol_type(t_list *sections, struct nlist_64 *sym);
e_ret print_nm(t_ofile *ofile, t_nm_options *options);
void print_debug(struct nlist *nlist);
void ft_putstrnl_lim(t_ofile *ofile, char *str);

bool is_overflow(t_ofile *ofile, void *ptr, bool print_error);
uint32_t swapif_u32(t_ofile *ofile, uint32_t uint);
uint64_t swapif_u64(t_ofile *ofile, uint64_t uint);
bool is_overflow_or_come_back(t_ofile *ofile, void *current, void *next);

// getter
char *get_name(t_ofile *ofile, void *p_nlist);
t_nm_options *get_nm_options(void);
t_no *get_no(void);

// symtab
void
bubble_sort_symbol_array(t_ofile *ofile, void **current, uint32_t array_size);

// debug
void print_section_list(t_list *list);
void print_sym_name(t_ofile *ofile);

#endif
