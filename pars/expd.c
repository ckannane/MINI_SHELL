/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:20:10 by ckannane          #+#    #+#             */
/*   Updated: 2023/09/20 00:29:55 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*apply_exp(t_com *com, char *str, int i, t_zid *zone)
{
	int		size;
	char	*tmp1;
	char	*tmp2;
	char	*new;

	size = i;
	i++;
	com->var_len = 0;
	tmp1 = ft_substr(str, 0, size);
	com->var_len = count_var_size(str + i);
	routine(str, i, com, zone);
	tmp2 = ft_strdup(str + (i + com->var_len));
	new = ft_strjoin(ft_strjoin(tmp1, com->var), tmp2);
	free(str);
	free(tmp2);
	return (new);
}

char	*expd(t_com *com, char *str, t_zid	*zone)
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
	free(com->var);
	return (str);
}

char	*expansion(t_com *com, t_zid *zone)
{
	int		i;
	char	*res;
	char	*hold;
	char	*command;

	res = NULL;
	command = NULL;
	hold = ft_strdup("");
	if (command)
		command = ft_strdup("");
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

int	check_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] > '9' || str[i] < '0')
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(t_com *com, t_zid *zone)
{
	if (com->arg[0] == NULL)
		exit(zone->exito);
	else if (com->arg[0] != NULL && check_digit(com->arg[0]) \
	&& com->arg[1] == NULL)
		exit(ft_atoi(com->arg[0]));
	else if (check_digit(com->arg[0]) == 0)
	{
		printf("exit, %s not numeric", com->arg[0]);
		exit(255);
	}
	else if (check_digit(com->arg[0]) && check_digit(com->arg[1]) \
	&& com->arg[1] != NULL)
		printf("too many args");
}
