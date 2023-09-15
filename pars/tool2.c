/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 20:53:42 by ckannane          #+#    #+#             */
/*   Updated: 2023/09/15 20:05:01 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expansion(t_com *com, t_zid *zone, char *line)
{
	int		i;
	char	*res;
	char	*hold;
	char	*command;

	res = ft_strdup("");
	hold = ft_strdup("");
	command = malloc(ft_strlen(line));
	com->sq = 0;
	com->dq = 0;
	i = 0;
	while (com->sp[i])
	{
		command = expd(com, com->sp[i], zone);
		res = ft_strjoin(command, " ");
		hold = ft_strjoin(hold, res);
		free(res);
		i++;
	}
	return (hold);
}

int	check_quote(char *line)
{
	int		i;
	char	flag;

	i = 0;
	flag = 0;
	while (line[i])
	{
		if ((line[i] == '"' || line[i] == '\'') && flag == 0)
			flag = line[i++];
		else if (line[i] == flag && flag)
			flag = 0;
		i++;
	}
	if (flag)
		return (1);
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i])
		i++;
	return (s1[i] - s2[i]);
}

t_com	*ft_comnew(char *line)
{
	t_com	*com;

	com = (t_com *)malloc(sizeof(t_com));
	if (!com)
		return (0);
	com->word = line;
	com->next = NULL;
	return (com);
}
char	*apply_exp(t_com *com ,char *str, int i, t_zid *zone)
{
	int		size;
	char	*tmp1;
	char	*tmp2;

	size = i;
	i++;
	com->var_len = 0;
	tmp1 = ft_substr(str, 0, size);
	com->var_len = count_var_size(str + i);
	routine(str, i, com, zone);
	tmp2 = str + (i + com->var_len);
	str = ft_strjoin(ft_strjoin(tmp1, com->var), tmp2);
	return (str);
}
char	*expd(t_com *com ,char *str, t_zid	*zone)
{
	int		i;
	int		is_double;
	int		is_single;

	is_double = 0;
	is_single = 0;
	com->var = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !(is_double))
			is_single = !(is_single);
		if (str[i] == '"' && !(is_double))
			is_double = !(is_double);
		if (str[i] == '$' && str[i + 1] != '\0' && !(is_single))
		{
			str = apply_exp(com, str, i, zone);
			i = 0;
		}
		i++;
	}
	return (str);
}
