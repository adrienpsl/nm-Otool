
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

struct stabnames
{
	unsigned char n_type;
	char *name;
};

static const struct stabnames stabnames[] = {
	{ N_GSYM,    "GSYM" },
	{ N_FNAME,   "FNAME" },
	{ N_FUN,     "FUN" },
	{ N_STSYM,   "STSYM" },
	{ N_LCSYM,   "LCSYM" },
	{ N_BNSYM,   "BNSYM" },
	{ N_OPT,     "OPT" },
	{ N_RSYM,    "RSYM" },
	{ N_SLINE,   "SLINE" },
	{ N_ENSYM,   "ENSYM" },
	{ N_SSYM,    "SSYM" },
	{ N_SO,      "SO" },
	{ N_OSO,     "OSO" },
	{ N_LSYM,    "LSYM" },
	{ N_BINCL,   "BINCL" },
	{ N_SOL,     "SOL" },
	{ N_PARAMS,  "PARAM" },
	{ N_VERSION, "VERS" },
	{ N_OLEVEL,  "OLEV" },
	{ N_PSYM,    "PSYM" },
	{ N_EINCL,   "EINCL" },
	{ N_ENTRY,   "ENTRY" },
	{ N_LBRAC,   "LBRAC" },
	{ N_EXCL,    "EXCL" },
	{ N_RBRAC,   "RBRAC" },
	{ N_BCOMM,   "BCOMM" },
	{ N_ECOMM,   "ECOMM" },
	{ N_ECOML,   "ECOML" },
	{ N_LENG,    "LENG" },
	{ N_PC,      "PC" },
	{ 0,         0 }
};

char * get_debug_type(uint16_t type)
{
	u_int8_t i;

	i = 0;
	while (0 != stabnames[i].n_type)
	{
		if (stabnames[i].n_type == type)
			return (stabnames[i].name);
		i++;
	}
	return ("");
}
