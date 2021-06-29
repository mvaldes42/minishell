# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/20 12:16:14 by mvaldes           #+#    #+#              #
#    Updated: 2021/06/29 17:31:27 by mvaldes          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= minishell

SRCS =	srcs/main.c \
		srcs/ft_strtok.c

OBJS = $(SRCS:.c=.o)
CC = @gcc
RM = @/bin/rm -f
CC_FLAGS = -Wall -Wextra -Werror -I.
LIBFT = lib/libft/libft.a
GNL = lib/get_next_line/get_next_line.a
LIBFT_F = lib/libft
GNL_F = lib/get_next_line

all:		$(NAME)

$(NAME):	compile $(OBJS)
			$(CC) $(CC_FLAGS) $(OBJS) $(LIBFT) $(GNL) -o $(NAME)
			@echo "> compile done <"

compile:
			@make -C $(LIBFT_F)
			@make -C $(GNL_F)

clean:
			@make clean -C $(LIBFT_F)
			@make clean -C $(GNL_F)
			$(RM) $(OBJS)
			@echo "> clean done <"

fclean:		clean
			@make fclean -C $(LIBFT_F)
			@make fclean -C $(GNL_F)
			$(RM) $(NAME)
			@echo "> fclean done <"

re:			fclean all

.PHONY: clean fclean re compile all