/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searcher_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 15:12:48 by mvaldes           #+#    #+#             */
/*   Updated: 2021/10/12 13:48:59 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_utils.h"
#include "../../minishell.h"

static void	make_dest_dir(t_funct_ext *ext, char **env_path, int i)
{
	int			size;

	size = sizeof(char *) * (ft_strlen(env_path[i]) + ft_strlen("/\0") + \
	ft_strlen(ext->func_name) + 1);
	ext->dest_dir = (char *)malloc(size);
	ft_memset(ext->dest_dir, 0, sizeof(char *));
	ext->d_ptr = ext->dest_dir;
	ft_strlcat(ext->dest_dir, env_path[i], size);
	ft_strlcat(ext->dest_dir, "/\0", size);
	ft_strlcat(ext->dest_dir, ext->func_name, size);
}

static void	funct_ext_found(t_parsing *parsing, t_token *token, char *path)
{
	token->tk_fct_path = ft_strdup(path);
	parsing->cmd_nbr++;
	token->modif_word = ft_strdup(token->ptr);
	token->type = FUNCTION;
}

int	search_funct_ext(t_parsing *parsing, t_token *token, char **env_path)
{
	t_funct_ext	e;
	int			i;

	e.func_name = token->modif_word;
	if (stat(e.func_name, &e.statbuf) == 0 && !S_ISDIR(e.statbuf.st_mode))
	{
		funct_ext_found(parsing, token, e.func_name);
		return (1);
	}
	i = -1;
	while (env_path != NULL && env_path[++i] != NULL)
	{
		make_dest_dir(&e, env_path, i);
		if (e.dest_dir == NULL)
			return (0);
		if (stat(e.dest_dir, &e.statbuf) == 0 && !S_ISDIR(e.statbuf.st_mode))
		{
			funct_ext_found(parsing, token, e.dest_dir);
			return (1);
		}
		ft_free_str(&e.d_ptr);
	}
	return (0);
}

void	free_expand_struct(t_exp_var *expand)
{
	int	i;

	i = 0;
	while (i < expand->nbr_var)
	{
		ft_free_str(&expand->var_name[i]);
		if (ft_strncmp(expand->var_name[i], "$?", 2) == 0)
			ft_free_str(&expand->var_trans[i]);
		i++;
	}
	ft_free_str(expand->var_name);
	ft_free_str(expand->var_trans);
	ft_free_int((int **)&expand->o_var_len);
	ft_free_int((int **)&expand->t_var_len);
}

int	free_env_path(t_data *data, char ***env_path)
{
	int	i;

	(void)data;
	i = -1;
	while (*env_path != NULL && (*env_path)[++i])
		ft_free_str(&(*env_path)[i]);
	ft_free_str(*env_path);
	return (1);
}
