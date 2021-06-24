/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 18:03:21 by mvaldes           #+#    #+#             */
/*   Updated: 2021/06/24 17:31:49 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_fail(t_data *data)
{
	(void)data;
	ft_putstr_fd("Error\n", STDERR);
	exit(EXIT_FAILURE);
}

// int	ft_isalpha(char c)
// {
// 	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
// 		return (1);
// 	return (0);
// }

int	word_count(t_data *data, const char *s, char c)
{
	unsigned int	i;
	unsigned int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	if (count == 0)
		exit_fail(data);
	return (count);
}

void	print_prompt(void)
{
	char	cwd[256];

	ft_putstr_fd("-> ", STDOUT);
	ft_putstr_fd(getcwd(cwd, sizeof(cwd)), STDOUT);
	ft_putstr_fd(" >$ ", STDOUT);
}

int	lexer(char *line, t_data *data)
{
	// int		i;
	char	**unspec_token;

	data->s_tokens.token_nbr = word_count(data, line, CHAR_WHITESPACE);
	unspec_token = (char **)malloc(sizeof(char *) * (data->s_tokens.token_nbr + 1));
	unspec_token = ft_split(line, CHAR_WHITESPACE);
	// while (line[i])
	// {
	// 	if (ft_isalpha(line[i]) && data->s_tokens->tokens_lst[i].token_type != CHAR_ALPHA)
	// 	{

	// 	}
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
	// data.s_tokens->tokens_lst->token_type = CHAR_SINGLE_QUOTE;
	// printf("%c\n", data.s_tokens->tokens_lst->token_type);
	print_prompt();
	while (get_next_line(STDIN, &line) > 0)
	{
		lexer(line, &data);
		print_prompt();
	}
	return (1);
}
