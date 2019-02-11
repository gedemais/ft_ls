# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gedemais <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/05 00:59:17 by gedemais          #+#    #+#              #
#    Updated: 2019/02/07 01:44:38 by gedemais         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

CC = @gcc

CFLAGS = -Wall -Werror -Wextra

LIB_PATH = libft/

LIB = libft/libft.a

SRCS_NAME = main.c \
			ft_run.c \
			ft_list.c  \
			ft_parsing.c \
			ft_quicksort.c \
			fts.c

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

fclean :
	@make fclean -C $(LIB_PATH)
	@rm -rf $(NAME)

re : fclean all
