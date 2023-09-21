/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 20:28:52 by ckannane          #+#    #+#             */
/*   Updated: 2023/09/21 00:42:38 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_it_equal(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=' && arg[i + 1] != '\0')
			return (1);
		else if (arg[i] == '=' && arg[i + 1] == '\0')
			return (0);
		i++;
	}
	return (0);
}

void	show_exp(t_val *current_exp)
{
	while (current_exp)
	{
		if (current_exp->value == NULL)
			printf("declare -x %s=\'\'\n", current_exp->name);
		else
			printf("declare -x %s=\"%s\"\n", current_exp->name, \
			current_exp->value);
		current_exp = current_exp->next;
	}
}

void	update_list(t_com *com, int i, t_val *current)
{
	t_val	*index;

	index = ft_val_re_new(com->arg[i]);
	ft_valadd_back(&current, index);
}

void	add_in_lists(t_com *com, t_val *current_exp, t_val *cuurent_env)
{
	int		i;

	i = 0;
	while (com->arg[i])
	{
		if (check_it_equal(com->arg[i]) == 1)
		{
			if (check_val(current_exp, com->arg[i]) == 1)
				update_list(com, i, current_exp);
			if (check_val(cuurent_env, com->arg[i]) == 1)
				update_list(com, i, cuurent_env);
		}
		else if (check_it_equal(com->arg[i]) == 0)
		{
			if (check_val(current_exp, com->arg[i]) == 1)
				update_list(com, i, current_exp);
		}
		i++;
	}
}

void	ft_export(t_com *com, t_zid *zone)
{
	int		i;
	t_val	*cuurent_env;
	t_val	*current_exp;

	i = 0;
	cuurent_env = zone->env;
	current_exp = zone->exp;
	if (com->arg[0] == NULL)
		show_exp(current_exp);
	else
		add_in_lists(com, current_exp, cuurent_env);
}
