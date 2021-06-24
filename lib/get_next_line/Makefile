# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/12 11:18:52 by mvaldes           #+#    #+#              #
#    Updated: 2021/06/24 17:39:27 by mvaldes          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	get_next_line.c \
			get_next_line_utils.c

OBJS	= ${SRCS:.c=.o}

NAME	= get_next_line.a

RM	= rm -f

.c.o: $(SRCS)
	gcc -Wall -Wextra -Werror -c $^ -o ${^:.c=.o}

$(NAME):    $(OBJS) get_next_line.h
	ar rcs $(NAME) $(OBJS)

all:		${NAME}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY: all clean fclean re
