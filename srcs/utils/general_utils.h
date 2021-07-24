#ifndef GENERAL_UTILS_H
# define GENERAL_UTILS_H
# include "../minishell.h"

typedef struct s_split
{
	char		**dest;
	char		c;
	int			start;
	int			end;
	int			i;
	int			w_count;
}	t_split;

void	exit_fail(t_data *data);
void	exit_sucess(t_data *data, char *line);
void	clear_data(t_data *data);
void	create_prompt(t_data *data);

int		char_occu(char *str, char c);

char	**token_split(char const *s, char c);
int		token_count(const char *s, char c);

#endif

//  echo -n bonjour|echo cool' $HOME top '" $HOME    super "|echo $?>txt1
