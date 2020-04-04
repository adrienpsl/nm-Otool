NAME = ft_nm

LIBFTDIR = libft/
INCSDIR = includes/
SRCSDIR = src/
OBJSDIR = objs/
CC = gcc
CFLAGS = -Wall -Wextra -Werror

HEADER_FILES  = nm_otool.h
HEADERS =  $(addprefix includes/, $(HEADER_FILES))

# cd render/src; ls -1 | tr '\n' ' ' | pbcopy
SRCS =	main.c  \
		binary_map.c \
        build_segment_list.c

SRC = $(wildcard src/*.c)
SRCS = $(SRC:src/%=%)

OBJS = $(addprefix $(OBJSDIR),$(SRCS:.c=.o))


$(OBJSDIR)%.o: $(SRCSDIR)%.c $(HEADERS)
	mkdir -p $(OBJSDIR)
	$(CC) $(CFLAGS) -I $(INCSDIR) -I $(LIBFTDIR)$(INCSDIR) -o $@ -c $<

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFTDIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L./libft -lft

clean:
	rm -rf $(OBJSDIR)
	make -C $(LIBFTDIR) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re