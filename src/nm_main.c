#include "nm_otool.h"

int nm_exit(int error)
{
	t_no *no;

	no = get_no();
	if (no->mmap_start)
		munmap(no->mmap_start, no->mmap_size);
	//	if (no->symbol_array)
	//		free(no->symbol_array);
	//	ft_lstdel(no->section_list, NULL);
	//	if (error)
	//		exit(EXIT_FAILURE);
	(void)error;
	return (0);
}

void fill_ofile(void *start, size_t size, t_ofile *ofile)
{
	ft_bzero(ofile, sizeof(t_ofile));
	ofile->start = start;
	ofile->end = start + size;
	ofile->ptr = start;
}

e_ret handle(t_no *no)
{
	t_ofile *ofile;

	ofile = get_ofile();
	fill_ofile(no->mmap_start, no->mmap_size, ofile);

	if (parse_magic_number(ofile))
		return (KO);
	if (ofile->is_fat
		&& KO == handle_fat_binaries(ofile))
		return (KO);
	// will be out
	if (build_section_list(ofile)
		|| build_sym_array(ofile, ofile->symtab_command))
		return (nm_exit(1));
	print_sym_array(ofile);
	return (0);
}

//void ar(t_no *no)
//{
//	t_ar_hdr *ar_hdr;
//	void *ptr;
//	int name_size;
//
//	if (!no->is_ar)
//		return;
//	name_size = 0;
//	ptr = no->map + SARMAG;
//	ar_hdr = ptr;
//	ptr += ft_atoi(ar_hdr->ar_size) + sizeof(t_ar_hdr);
//	while (no->map < no->map_end)
//	{
//		ar_hdr = ptr;
//		if (!ft_strncmp(ptr, AR_EFMT1, ft_strlen(AR_EFMT1)))
//			name_size = ft_atoi(ar_hdr->ar_name + ft_strlen(AR_EFMT1));
//
//		ptr += sizeof(t_ar_hdr);
//		no->map = ptr + name_size;
//		handle(no);
//		no->map -= name_size;
//		ft_printf("%s\n", ar_hdr);
//		ptr += ft_atoi(ar_hdr->ar_size);
//	}
//}

bool is_archive(t_no *no, void *ptr)
{
	if (OK == ft_strncmp(ptr, ARMAG, SARMAG))
	{
		no->is_ar = true;
		return (true);
	}
	return (false);
}

int main(int ac, char **av)
{
	int i;
	t_no *no;

	no = get_no();
	i = option_parser(av, ac);

	// is archive? -> loop on the header
	// pas archive -> loop on the file
	if (KO == create_mmap(av[i], no))
		return (nm_exit(1));

	//	if (parse_magic_number(no, no->map))
	//		return (KO);

	// is arch ?
	//	if (true == is_archive(no, no->map))
	//		return (OK);

	handle(no);

	//	if (no->is_ar)
	// start arch parsing
	//		ar(no);
	// fill binary


	nm_exit(0);
}
