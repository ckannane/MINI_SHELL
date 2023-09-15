/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 20:56:25 by ckannane          #+#    #+#             */
/*   Updated: 2023/09/15 10:24:56 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_var_size(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (ft_isalpha(str[i]) || ft_isdigit(str[i])))
		i++;
	return (i);
}

char	*var_expand(t_com *sh, t_val *env)
{
	int		len;
	int		i;
	char	*res;

	len = ft_strlen(sh->var);
	i = 0;
	while (env)
	{
		if (ft_strcmp(sh->var, env->name) == 0)
			break ;
		else
			env = env->next;
	}
	if (env != NULL)
		res = ft_strdup(env->value);
	else
		res = ft_strdup("");
	return (res);
}

void	routine(char *str, int i,t_com *com, t_val *env)
{
	if (str[i] == '?')
	{
		com->var_len = 1;
		com->var = ft_itoa(1);
		//shell->exito = 0;
	}
	else
	{
		com->var = ft_substr(str, i, com->var_len);
		com->var = var_expand(com, env);
	}
}

int	check_q(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

t_val	*int_env(char **env)
{
	t_val	*zone;
	t_val	*index;
	int		i;

	i = 0;
	zone = NULL;
	while (env[i])
	{
		index = ft_val_re_new(env[i++]);
		ft_valadd_back(&zone, index);
	}
	return (zone);
}
