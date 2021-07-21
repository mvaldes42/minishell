# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/20 12:16:14 by mvaldes           #+#    #+#              #
#    Updated: 2021/07/21 19:46:25 by mvaldes          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= minishell

SRCS =	srcs/minishell.c \
		srcs/lexer.c \
		srcs/utils/general_utils.c \
		srcs/utils/lexer_utils.c \
		srcs/utils/sep_token_count.c \
		srcs/utils/ft_strtok.c \
		srcs/utils/ft_strtok_spec.c \

OBJS = $(SRCS:.c=.o)
CC = @gcc
RM = @/bin/rm -f
CC_FLAGS = -Wall -Wextra -Werror -I.
LIBFT = lib/libft/libft.a
LIBFT_F = lib/libft

all:		$(NAME)

$(NAME):	compile
			$(CC) $(CC_FLAGS) -lreadline $(OBJS) $(LIBFT) $(GNL) -o $(NAME)
			@echo "> compile done <"

compile:
			@make -C $(LIBFT_F)
			@make $(OBJS)

clean:
			@make clean -C $(LIBFT_F)
			$(RM) $(OBJS)
			@echo "> clean done <"

fclean:		clean
			@make fclean -C $(LIBFT_F)
			$(RM) $(NAME)
			@echo "> fclean done <"

re:			fclean all

.PHONY: clean fclean re compile all