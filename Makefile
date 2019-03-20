# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gedemais <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/05 00:59:17 by gedemais          #+#    #+#              #
#    Updated: 2019/03/20 12:23:58 by gedemais         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DEF = \033[0m
GRA = \033[1m
SOU = \033[4m
BLI = \033[5m
BLA = \033[30m
RED = \033[31m
GRE = \033[32m
YEL = \033[33m
BLU = \033[34m
PUR = \033[35m
CYA = \033[36m
WHI = \033[37m
ORG = \033[1;31m

NAME = ft_ls

CC = @gcc

FLAGS = -g -fsanitize=address

CFLAGS = -Wall -Werror -Wextra

LIB_PATH = libft/

LIB = libft/libft.a

SRCS_NAME = 		fts.c \
			main.c \
			ft_run.c\
			run_fts.c\
			ft_free.c \
			ft_list.c  \
			ft_path.c   \
			ft_usage.c   \
			lines_fts.c   \
			ft_params.c    \
			ft_address.c    \
			ft_datecmp.c     \
			ft_parsing.c      \
			ft_displays.c      \
			ft_quicksort.c      \
			ft_singletons.c      \

SRCS_PATH = srcs/

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))

OBJS_NAME = $(SRCS_NAME:.c=.o)

OBJS_PATH = obj/

OBJS = $(addprefix $(OBJS_PATH), $(OBJS_NAME))

all : $(LIB) $(NAME)

$(NAME) : $(LIB) $(OBJS)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIB)
		@echo "$(GRE)Done !$(DEF)"

$(LIB) : $(LIB_PATH)
		@echo "Making $(RED)Libft$(DEF)..."
		@make re -C $(LIB_PATH)

$(OBJS) : $(SRCS)
		@mkdir -p $(OBJS_PATH)
		@echo "Making $(CYA)ft_ls$(DEF)..."
		$(CC) $(CFLAGS) -c $(SRCS)
		@mv $(OBJS_NAME) obj/

clean : 
	@rm -rf obj/
	@make clean -C $(LIB_PATH)

fclean : clean
	@make fclean -C $(LIB_PATH)
	@rm -rf $(NAME)

fsanitize : $(LIB) $(SRCS)
			$(CC) $(FLAGS) $(SRCS) $(LIB)

re : fclean all
