/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:47:43 by ckannane          #+#    #+#             */
/*   Updated: 2023/09/20 00:34:11 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_comadd_back(t_com **com, t_com *new)
{
	t_com	*end;

	if (com == NULL || new == NULL)
		return ;
	if (*com == NULL)
	{
		*com = new;
		return ;
	}
	end = ft_comlast(*com);
	end->next = new;
	new->next = NULL;
}

char	*ft_strjoin_env(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	j = 0;
	if (s1 == NULL)
		return ((char *)s2);
	if (s2 == NULL)
		return ((char *)s1);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!str)
		return (0);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i++] = '/';
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}

char	**get_path(char *command, t_val *env)
{
	int		i;
	char	*str;
	char	**slp;

	i = 0;
	while (env)
	{
		if (ft_strcmp(env->name, "PATH") == 0)
			str = ft_strdup(env->value);
		env = env->next;
	}
	slp = ft_split(str, ':');
	free(str);
	while (slp[i])
	{
		slp[i] = ft_strjoin_env(slp[i], command);
		i++;
	}
	return (slp);
}

char	**pas_env(t_val *env)
{
	char	**inenv;
	t_val	*current;
	int		len_list;
	int		i;

	current = env;
	len_list = 0;
	while (current)
	{
		len_list++;
		current = current->next;
	}
	inenv = (char **)malloc(sizeof(char *) * (len_list + 1));
	if (!inenv)
		return (NULL);
	current = env;
	i = 0;
	while (current)
	{
		inenv[i] = ft_strdup(current->content);
		current = current->next;
		i++;
	}
	inenv[i] = NULL;
	return (inenv);
}

t_com	*ft_comlast(t_com *com)
{
	if (com == NULL)
		return (NULL);
	while (com->next != NULL)
		com = com->next;
	return (com);
}
