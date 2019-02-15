# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gedemais <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/05 00:59:17 by gedemais          #+#    #+#              #
#    Updated: 2019/02/15 06:33:07 by gedemais         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

CC = @gcc -g

FLAGS = -fsanitize=address

CFLAGS = -Wall -Werror -Wextra

LIB_PATH = libft/

LIB = libft/libft.a

SRCS_NAME = 	fts.c\
		main.c \
		ft_run.c\
		ft_list.c\
		ft_usage.c\
		ft_address.c\
		ft_datecmp.c\
		ft_parsing.c \
		display_fts.c \
		ft_quicksort.c \
		ft_display_cols.c\
		ft_display_line.c \
		ft_display_lines.c \

SRCS_PATH = srcs/

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))

OBJS = $(SRCS_NAME:.c=.o)

all : $(LIB) $(NAME)

$(NAME) : $(LIB) $(OBJS)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIB)

$(LIB) : $(LIB_PATH)
		@make re -C $(LIB_PATH)

$(OBJS) : $(SRCS)
		$(CC) $(CFLAGS) -c $(SRCS)

clean : 
	@rm -rf $(OBJS)
	@make clean -C $(LIB_PATH)

fclean : clean
	@make fclean -C $(LIB_PATH)
	@rm -rf $(NAME)

fsanitize : $(LIB) $(SRCS)
			$(CC) $(FLAGS) $(SRCS) $(LIB)

re : fclean all
