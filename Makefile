#
#
#
#
#
#
#
#
#
#

NAME = ft_nm_otool

INCLUDE_PATH = includes
LIBFT_PATH = libft
BUILD_PATH = objs
SRC_PATH = src


SOURCES += handle.archive.c \
           handle.dispatch.c \
           handle.fat_arch.c \
           magic_number.c \
           otool.print.c \
           parser_option.c \
           print.nm.c \
           print.nm.debug.c \
           print.nm.get_symbol_type.c \
           sections.add_segment.c  \
           sections.build_sections.c \
           symtab.build.c \
           symtab.sort.c \
           utils.getter.c \
           utils.overflow.c \
           utils.print.c \
           utils.swap.c \
           start.c

FT_NM_FILES = ft_nm.c $(SOURCES)
FT_NM_SOURCES = $(addprefix $(SRC_PATH)/,$(FT_NM_FILES))
FT_NM_OBJECTS = $(FT_NM_FILES:%.c=$(BUILD_PATH)/%.o)

FT_OTOOL_FILES = ft_otool.c $(SOURCES)
FT_OTOOL_SOURCES = $(addprefix $(SRC_PATH)/,$(FT_OTOOL_FILES))
FT_OTOOL_OBJECTS = $(FT_OTOOL_FILES:%.c=$(BUILD_PATH)/%.o)

LIB_SOURCES = $(LIBFT_PATH)/libft.a

# Variables

FT_NM = ft_nm
FT_OTOOL = ft_otool

CC = gcc
FLAGS_CC = -Wall -Wextra -Werror

# **************************************************************************** #
# COMMANDS  		    													   #
# **************************************************************************** #

.PHONY: all libs clean fclean re ft_nm ft_otool

all: $(NAME)

$(NAME): $(FT_NM) $(FT_OTOOL)

$(FT_NM): libs $(FT_NM_OBJECTS)
	@$(CC) $(FLAGS_CC) -o $@ $(FT_NM_OBJECTS) $(LIB_SOURCES)

$(FT_OTOOL): libs $(FT_OTOOL_OBJECTS)
	@$(CC) $(FLAGS_CC) -o $@ $(FT_OTOOL_OBJECTS) $(LIB_SOURCES)

libs:
	@make -s -C $(LIBFT_PATH)

$(BUILD_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(@D)
	$(CC) $(FLAGS_CC) -c -o $@ $< -I $(INCLUDE_PATH) -I $(LIBFT_PATH)/includes

clean:
	@make clean -C $(LIBFT_PATH)
	@rm -rf $(BUILD_PATH)
	@echo "Clean \033[33mok\033[0m"

fclean: clean
	@make fclean -C $(LIBFT_PATH)
	@rm -f $(FT_NM) $(FT_OTOOL) $(LIB_NAME)
	@echo "Fclean \033[33mok\033[0m"

re: fclean
	@make $(NAME)


