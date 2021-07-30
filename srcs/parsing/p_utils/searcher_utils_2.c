/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searcher_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 15:12:48 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/30 15:35:42 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_utils.h"
#include "../../minishell.h"

void	free_srch_struct(t_searcher *srch)
{
	int	i;

	i = 0;
	while (i < srch->nbr_var)
	{
		free(srch->var_name[i]);
		if (ft_strncmp(srch->var_name[i], "$?", 2) == 0)
			free(srch->var_trans[i]);
		i++;
	}
	free(srch->var_name);
	free(srch->var_trans);
	free(srch->o_var_len);
	free(srch->t_var_len);
}

int	search_funct_ext(t_parsing *parsing, t_token_id *token, t_searcher *srch)
{
	struct stat	statbuf;
	char		*dest_dir;
	int			size;
	int			i;

	i = 0;
	while (srch->env_path[i] != NULL)
	{
		size = sizeof(char) * (ft_strlen(srch->env_path[i]) + ft_strlen("/") + \
		ft_strlen(srch->env_path[i]) + 1);
		dest_dir = (char *)malloc(size);
		if (dest_dir == NULL)
			return (0);
		ft_strlcat(dest_dir, srch->env_path[i], size);
		ft_strlcat(dest_dir, "/", size);
		ft_strlcat(dest_dir, token->token_ptr, size);
		if (stat(dest_dir, &statbuf) == 0)
		{
			token->tk_fct_path = ft_strdup(dest_dir);
			printf("%s\n", token->tk_fct_path);
			parsing->command_nbr++;
			free(dest_dir);
			return (1);
		}
		free(dest_dir);
		i++;
	}
	return (1);
}
