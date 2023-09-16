/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_par.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:44:27 by ckannane          #+#    #+#             */
/*   Updated: 2023/09/16 17:59:57 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_slp_p	*init_slp_p(void)
{
	t_slp_p	*val;

	val = malloc(sizeof(t_slp_p));
	val->i = 0;
	val->start = 0;
	val->in_d = 0;
	val->in_s = 0;
	val->slp_len = 0;
	val->j = 0;
	return (val);
}

void	tokenize_input(char *input, t_slp_p *val, char ***result)
{
	while (input[val->j] != '\0')
	{
		if (input[val->j] == '|' && !val->in_d && !val->in_s)
		{
			val->slp_len = val->j - val->start;
			if (val->slp_len > 0)
			{
				*result = ft_realloc(result, val->i * sizeof(char *), \
				(val->i + 1) * sizeof(char *));
				(*result)[val->i] = malloc(val->slp_len + 1);
				ft_strncpy((*result)[val->i], &input[val->start], val->slp_len);
				(*result)[val->i][val->slp_len] = '\0';
				val->i++;
			}
			val->start = val->j + 1;
		}
		else if (input[val->j] == '"')
			val->in_d = !val->in_d;
		else if (input[val->j] == '\'')
			val->in_s = !val->in_s;
		val->j++;
	}
}

char	**splitstring(char *input)
{
	t_slp_p	*val;
	char	**result;

	val = init_slp_p();
	result = NULL;
	tokenize_input(input, val, &result);
	val->slp_len = ft_strlen(input) - val->start;
	if (val->slp_len > 0)
	{
		result = ft_realloc(result, val->i * sizeof(char *), \
		(val->i + 1) * sizeof(char *));
		result[val->i] = malloc(val->slp_len + 1);
		ft_strncpy(result[val->i], &input[val->start], val->slp_len);
		result[val->i][val->slp_len] = '\0';
		val->i++;
	}
	result = ft_realloc(result, val->i * sizeof(char *), \
	(val->i + 1) * sizeof(char *));
	result[val->i] = NULL;
	return (result);
}

void	read_com(t_com *com, t_zid *zone, char *line)
{
	char	*tmp;
	int		num_args;

	com->sp = ft_split(com->word, ' ');
	tmp = expansion(com, zone, line);
	tmp = return_without_quote(tmp);
	tmp = redirection_split(tmp);
	com->slp = ft_split(tmp, ' ');
	if (com->slp[0] == NULL)
		return ;
	com->commad = set_command(com->slp);
	if (com->commad == NULL)
		return ;
	num_args = set_arg_size(com);
	if (num_args == 0)
		return ;
	install_arg(com, num_args);
}
