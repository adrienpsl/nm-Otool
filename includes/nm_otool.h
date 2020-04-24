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
	t_list *sections;
	void *symtab_command;
	void *string_table;
} t_ofile;

typedef struct s_no
{
	void *mmap_start;
	size_t mmap_size;
	char *file_name;
	bool is_ar;
	int is_print;
	int mode;
} t_no;

typedef struct s_stabname
{
	unsigned char n_type;
	char *name;
} t_stabname;


/*
**	short type
*/
typedef struct ar_hdr t_ar_hdr;
typedef struct load_command t_load_command;
typedef struct fat_arch t_fat_arch;
typedef struct fat_header t_fat_header;
typedef struct section_64 t_section_64;
typedef struct section t_section;


bool handle_magic_number(t_ofile *ofile, uint32_t *magic);
e_ret handle_ofile(t_ofile *ofile, void *start, void *end);
e_ret handle_archive(t_ofile *ofile);
e_ret handle_fat_arch(t_ofile *ofile);
e_ret handle_maco(t_ofile *ofile);
e_ret dispatch_ofile(t_ofile *ofile, void *start, void *end);


bool is_overflow(t_ofile *ofile, void *ptr);
uint32_t swapif_u32(t_ofile *ofile, uint32_t uint);






#endif
