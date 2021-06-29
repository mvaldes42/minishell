/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 18:03:21 by mvaldes           #+#    #+#             */
/*   Updated: 2021/06/29 18:51:39 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_fail(t_data *data)
{
	(void)data;
	ft_putstr_fd("Error\n", STDERR);
	exit(EXIT_FAILURE);
}

// int	word_count(const char *s, char c)
// {
// 	unsigned int	i;
// 	unsigned int	count;

// 	i = 0;
// 	count = 0;
// 	while (s[i])
// 	{
// 		while (s[i] == c)
// 			i++;
// 		if (s[i])
// 			count++;
// 		while (s[i] != c && s[i])
// 			i++;
// 	}
// 	if (count == 0)
// 		return (0);
// 	return (count);
// }

int	delim_count(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\'' || str[i] == '\"')
			i++;
		if (str[i])
			count++;
		while (!(str[i] == ' ' || str[i] == '\'' || str[i] == '\"') && str[i])
			i++;
		i++;
	}
	return (count);
}

int	char_occu(char *str, char c)
{
	int		nbr;
	char	*s;

	s = str;
	nbr = 0;
	while (*s)
	{
		if (*s == c)
			nbr++;
		s++;
	}
	if (nbr > 0)
		return (nbr);
	return (0);
}

void	print_prompt(void)
{
	char	cwd[256];

	ft_putstr_fd("-> ", STDOUT);
	ft_putstr_fd(getcwd(cwd, sizeof(cwd)), STDOUT);
	ft_putstr_fd(" >$ ", STDOUT);
}

int	lexer(char *line, t_lexer lx)
{
	int		i;
	int		j;
	char	**unspec_token;

	i = 0;
	if (char_occu(line, CHAR_SINGLE_QUOTE) % 2 || char_occu(line, CHAR_DOUBLE_QUOTE) % 2)
		exit(EXIT_FAILURE);
	lx.tk_nbr = delim_count(line);
	unspec_token = (char **)malloc(sizeof(char *) * (lx.tk_nbr + 1));
	printf("count : %d\n", delim_count(line));
	// char *ptr = ft_strtok(line, " '");
	// while(ptr != NULL)
	// {
	// 	printf(">%s<\n", ptr);
	// 	ptr = ft_strtok(NULL, " '");
	// }
	// unspec_token = (char **)malloc(sizeof(char *) * (lx.tk_nbr + 1));
	// unspec_token = ft_split(line, CHAR_WHITESPACE);
	// lx.tk_lst = (t_token_id *)malloc(sizeof(t_token_id *) * (lx.tk_nbr + 1));
	// ft_memset(lx.tk_lst, 0, sizeof(t_token_id *) * (lx.tk_nbr + 1));
	// while (unspec_token[i])
	// {
	// 	lx.tk_lst[i].token_ptr = ft_strdup(unspec_token[i]);
	// 	if (ft_strlen(unspec_token[i]) == 1 && unspec_token[i][0] == CHAR_PIPE)
	// 		lx.tk_lst[i].token_type = CHAR_PIPE;
	// 	else if (ft_strlen(unspec_token[i]) == 2)
	// 	{
	// 		if (ft_strncmp(unspec_token[i], ">>", 2))
	// 			lx.tk_lst[i].token_type = STR_RED_OUT_APP;
	// 		if (ft_strncmp(unspec_token[i], "<<", 2))
	// 			lx.tk_lst[i].token_type = STR_READ_IN;
	// 		if (ft_strncmp(unspec_token[i], "$?", 2))
	// 			lx.tk_lst[i].token_type = STR_EXIT_STAT;
	// 	}
	// 	else if (unspec_token[i][0] == CHAR_EXP)
	// 		lx.tk_lst[i].token_type = CHAR_EXP;
	// 	else if (unspec_token[i][0] == CHAR_EXP)
	// 		lx.tk_lst[i].token_type = CHAR_EXP;
	// 	// else if (is_occu_odd(unspec_token[i], CHAR_SINGLE_QUOTE) == 1)
	// 	i++;
	// }
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	char			*line;
	t_data			data;

	(void)argc;
	(void)argv;
	(void)env;
	line = NULL;
	ft_bzero(&data, sizeof(data));
	print_prompt();
	while (get_next_line(STDIN, &line) > 0)
	{
		lexer(line, data.s_tokens);
		print_prompt();
	}
	return (1);
}
