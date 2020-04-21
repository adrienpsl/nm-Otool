#include "nm_otool.h"

int nm_exit(int error)
{
	t_no *no;

	no = get_no();
	if (no->map)
		munmap(no->start_map, no->map_size);
	if (no->symbol_array)
		free(no->symbol_array);
	ft_lstdel(no->section_list, NULL);
	if (error)
		exit(EXIT_FAILURE);
	return (0);
}

int handle(t_no *no)
{
	if (parse_magic_number(no, no->map))
		return (nm_exit(1));
	handle_fat_binaries(no);
	if (parse_magic_number(no, no->map))
		return (nm_exit(1));
	// will be out
	if (build_section_list(no)
		|| build_sym_array(no, no->symtab_command))
		return (nm_exit(1));
	print_sym_array(no);
	return (0);
}

void ar(t_no *no)
{
	t_ar_hdr *ar_hdr;
	void *ptr;
	int name_size;

	if (!no->is_ar)
		return;
	name_size = 0;
	ptr = no->map + SARMAG;
	ar_hdr = ptr;
	ptr += ft_atoi(ar_hdr->ar_size) + sizeof(t_ar_hdr);
	while (no->map < no->map_end)
	{
		ar_hdr = ptr;
		if (!ft_strncmp(ptr, AR_EFMT1, ft_strlen(AR_EFMT1)))
			name_size = ft_atoi(ar_hdr->ar_name + ft_strlen(AR_EFMT1));

		ptr += sizeof(t_ar_hdr);
		no->map = ptr + name_size;
		handle(no);
		no->map -= name_size;
		ft_printf("%s\n", ar_hdr);
		ptr += ft_atoi(ar_hdr->ar_size);
	}
}

int main(int ac, char **av)
{
	int i;
	t_no *no;

	no = get_no();
	i = option_parser(av, ac);

	// is archive? -> loop on the header
	// pas archive -> loop on the file
	if (create_mmap(av[i], no)
		|| parse_magic_number(no, no->map))
		return (nm_exit(1));

	if (no->is_ar)
		ar(no);

	handle(no);

	nm_exit(0);
}
