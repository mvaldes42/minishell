#ifndef GENERAL_UTILS_H
# define GENERAL_UTILS_H
# include "../minishell.h"

void	exit_fail(t_data *data);
void	exit_sucess(t_data *data, char *line);
void	clear_data(t_data *data);
void	create_prompt(t_data *data);

int		sep_token_count(t_data *data, char *str, char *sep);
int		char_occu(char *str, char c);
char	*ft_strtok(char *s, const char *delim);
char	**ft_strtok_spec(t_data *data, char *s, int tk_nbr);

#endif
