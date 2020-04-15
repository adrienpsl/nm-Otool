
#include "nm_otool.h"
#include "mach-o/stab.h"

char g_debugsym[] = {
	N_GSYM,
	N_FNAME,
	N_FUN,
	N_STSYM,
	N_LCSYM,
	N_BNSYM,
	N_AST,
	N_OPT,
	N_RSYM,
	N_SLINE,
	N_ENSYM,
	N_SSYM,
	N_SO,
	N_OSO,
	N_LSYM,
	N_BINCL,
	N_SOL,
	N_PARAMS,
	N_VERSION,
	N_OLEVEL,
	N_PSYM,
	N_EINCL,
	N_ENTRY,
	N_LBRAC,
	N_EXCL,
	N_RBRAC,
	N_BCOMM,
	N_ECOMM,
	N_ECOML,
	N_LENG,
	0
};

char get_debug_letter(uint16_t type)
{
	int i;

	i = 0;
	while (g_debugsym[i])
	{
		if (g_debugsym[i] == type)
		{
			return (g_debugsym[i]);
		}
		i++;
	}
	return ('-');
}