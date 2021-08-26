# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
<<<<<<< HEAD
#    By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/20 12:16:14 by mvaldes           #+#    #+#              #
#    Updated: 2021/08/19 14:15:36 by mvaldes          ###   ########.fr        #
=======
#    By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/20 12:16:14 by mvaldes           #+#    #+#              #
#    Updated: 2021/08/26 17:51:04 by fcavillo         ###   ########.fr        #
>>>>>>> wip
#                                                                              #
# **************************************************************************** #

include minishell.mk

NAME		=	minishell

SRCS_DIR	=	srcs
OBJS_DIR	=	objs
HEADER		=	./srcs/minishell.h

CC			=	gcc
RM			=	/bin/rm -rf
<<<<<<< HEAD
CC_FLAGS	=	-Wall -Wextra -Werror -fsanitize=address
=======
CC_FLAGS	=	-Wall -Wextra -Werror -fsanitize=address -g3
>>>>>>> wip
INC			=	-I $(HEADER) \
				-lreadline \
				-L /usr/local/opt/readline/lib \
				-I /usr/local/opt/readline/include
				# -L /Users/$(USER)/.brew/opt/readline/lib \
				# -I /Users/$(USER)/.brew/opt/readline/include \

LIBFT		=	lib/libft/libft.a
LIBFT_F		=	lib/libft


SRCS	=	$(addprefix $(SRCS_DIR)/, $(FILES))
OBJS 	=	$(addprefix $(OBJS_DIR)/, $(FILES:.c=.o))

all:		$(NAME)

$(NAME):	$(OBJS) $(HEADER)
			@make -C $(LIBFT_F)
			@$(CC) $(CC_FLAGS) $(INC) $(OBJS) $(LIBFT) $(GNL) -o $(NAME)
			@printf "$(GREEN)$(NAME) created with '$(CC_FLAGS)' flags\n$(END)"
			@printf "$(PURPLE)Minishell is ready to work!\n$(END)"

$(OBJS_DIR)/%.o : $(SRCS_DIR)/%.c | $(OBJS_DIR)
	    	@$(CC) $(CC_FLAGS) -c $< -o $@

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