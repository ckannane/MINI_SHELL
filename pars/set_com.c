/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_com.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:42:39 by ckannane          #+#    #+#             */
/*   Updated: 2023/09/18 21:54:59 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	issymbol(char c)
{
	return (c == '<' || c == '>');
}

char	*fill_the_red(int len, int i, int j, char *input)
{
	char	c_tmp;
	char	*result;

	result = ft_calloc(2 * len + 1, 1);
	while (i < len)
	{
		c_tmp = input[i];
		if (issymbol(c_tmp))
		{
			result[j++] = ' ';
			result[j++] = c_tmp;
			if (i < len - 1 && issymbol(input[i + 1]))
				result[j++] = input[i++ + 1];
			result[j++] = ' ';
		}
		else
			result[j++] = c_tmp;
		i++;
	}
	result[j] = '\0';
	return (result);
}

char	*redirection_split(char *input)
{
	int		len;
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	len = ft_strlen(input);
	result = fill_the_red(len, i, j, input);
	free(input);
	return (result);
}

int	set_arg_size(t_com *com)
{
	int	i;
	int	num_args;

	i = 0;
	num_args = 0;
	if ((ft_strcmp(com->slp[0], "<<") == 0) || \
	(ft_strcmp(com->slp[0], "<") == 0))
		i = i + 2;
	while (com->slp[i])
	{
		if ((ft_strcmp(com->slp[i], ">") == 0 || \
		ft_strcmp(com->slp[i], ">>") == 0 || ft_strcmp(com->slp[i], "<") == 0 \
		|| ft_strcmp(com->slp[i], "<<") == 0))
			break ;
		num_args++;
		i++;
	}
	return (num_args);
}

void	install_arg(t_com *com, int num_args)
{
	int	i;
	int	j;

	com->after_red = (char **)malloc((num_args + 1) * sizeof(char *));
	if (!com->after_red)
		com->after_red = NULL;
	com->arg = (char **)malloc((num_args + 1) * sizeof(char *));
	if (!com->arg)
		com->arg = NULL;
	i = 1;
	j = 0;
	while (j < num_args - 1)
		com->arg[j++] = ft_strdup(com->slp[i++]);
	com->arg[j] = NULL;
	j = 0;
	while (j < num_args)
	{
		com->after_red[j] = ft_strdup(com->slp[j]);
		j++;
	}
	com->after_red[j] = NULL;
}
