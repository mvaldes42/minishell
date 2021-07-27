FILES =	minishell.c \
		utils/general_utils.c \
		parsing/parsing.c \
		parsing/lexer.c \
		parsing/searcher.c \
		parsing/p_utils/lexer_utils.c \
		parsing/p_utils/token_split.c \
		parsing/p_utils/token_count.c \
		parsing/p_utils/token_split_utils.c\

SUB_DIR	=	utils\
			parsing\
			parsing/p_utils\

BLACK	=	\033[0;30m
RED		=	\033[0;31m
GREEN	=	\033[0;32m
YELLOW	=	\033[0;33m
BLUE	=	\033[0;34m
PURPLE	=	\033[0;35m
CYAN	=	\033[0;36m
WHITE	=	\033[0;37m
END		=	\033[m