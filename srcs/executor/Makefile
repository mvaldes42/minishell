# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/20 12:16:14 by mvaldes           #+#    #+#              #
#    Updated: 2021/07/28 18:27:04 by cramdani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BLACK	=	\033[0;30m
RED		=	\033[0;31m
GREEN	=	\033[0;32m
YELLOW	=	\033[0;33m
BLUE	=	\033[0;34m
PURPLE	=	\033[0;35m
CYAN	=	\033[0;36m
WHITE	=	\033[0;37m
END		=	\033[m

SRCS		=	executor.c

NAME		=	executor	

OBJS_DIR	=	objs

CC			=	gcc
RM			=	/bin/rm -rf
CC_FLAGS	=	-Wall -Wextra -Werror

OBJS 	=	$(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

all:		$(NAME)

$(NAME):	$(OBJS) 
			@$(CC) $(CC_FLAGS) $(OBJS)  -o $(NAME) libft.a
			@printf "$(GREEN)$(NAME) created with '$(CC_FLAGS)' flags\n$(END)"
			@printf "$(PURPLE)Executor is ready to work!\n$(END)"

$(OBJS_DIR)/%.o : %.c | $(OBJS_DIR)
	    	@$(CC) $(CC_FLAGS) -c $< -o $@

$(OBJS_DIR):
		@mkdir -p $@
		@printf "Create object directories : $(GREEN)$(OBJS_DIR)\n$(END)"

clean:
			@$(RM) $(OBJS_DIR)
			@printf "$(RED)Cleaning is done!\n$(END)"

fclean:		clean
			@$(RM) $(NAME)
			@printf "$(YELLOW)FCleaning is done!\n$(END)"

re:			fclean all

.PHONY: clean fclean re compile all