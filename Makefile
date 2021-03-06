# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/20 12:16:14 by mvaldes           #+#    #+#              #
#    Updated: 2021/10/22 14:51:33 by mvaldes          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include minishell.mk

NAME		=	minishell

SRCS_DIR	=	srcs
OBJS_DIR	=	objs
HEADER		=	./srcs/minishell.h

CC			=	gcc
RM			=	/bin/rm -rf
CC_FLAGS	=	-Wall -Wextra -Werror -g3
# -fsanitize=address
INC			=	-I $(HEADER) \
				-lreadline \
				-L/Users/$(USER)/.brew/opt/readline/lib \
				-L/usr/local/opt/readline/lib \
				-lncurses

LIBFT		=	lib/libft/libft.a
LIBFT_F		=	lib/libft


SRCS	=	$(addprefix $(SRCS_DIR)/, $(FILES))
OBJS 	=	$(addprefix $(OBJS_DIR)/, $(FILES:.c=.o))

all:		$(NAME)

$(NAME):	$(OBJS) $(HEADER)
			@make -C $(LIBFT_F)
			@$(CC) $(CC_FLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(INC)
			@printf "$(GREEN)$(NAME) created with '$(CC_FLAGS)' flags\n$(END)"
			@printf "$(PURPLE)Minishell is ready to work!\n$(END)"

$(OBJS_DIR)/%.o :	$(SRCS_DIR)/%.c | $(OBJS_DIR)
					@$(CC) \
					-I/Users/$(USER)/.brew/opt/readline/include \
					-I/usr/local/opt/readline/include \
					$(CC_FLAGS) -c $< -o $@

$(OBJS_DIR):
		@mkdir -p $@
		@mkdir $(addprefix $(OBJS_DIR)/, $(SUB_DIR))
		@printf "Create object directories : $(GREEN)$(OBJS_DIR)\n$(END)"
		@printf "Create object subdirectories : $(GREEN)$(SUB_DIR)\n$(END)"

clean:
			@make clean -C $(LIBFT_F)
			@$(RM) $(OBJS_DIR)
			@printf "$(RED)Cleaning is done!\n$(END)"

fclean:		clean
			@make fclean -C $(LIBFT_F)
			@$(RM) $(NAME)
			@printf "$(YELLOW)FCleaning is done!\n$(END)"

re:			fclean all

.PHONY: clean fclean re compile all