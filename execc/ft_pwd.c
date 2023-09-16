/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 10:07:29 by ckannane          #+#    #+#             */
/*   Updated: 2023/09/16 19:47:14 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_match_env(t_val *env, t_val *exp)
{
	t_val	*current;

	current = malloc(sizeof(t_val));
	while (env)
	{
		current = exp;
		while (current)
		{
			if (ft_strcmp(env->name, current->name) == 0 && \
			ft_strcmp(env->value, current->value) != 0)
			{
				free(env->value);
				env->value = ft_strdup(current->value);
			}
			current = current->next;
		}
		env = env->next;
	}
}

void	ft_pwd(t_zid *zone)
{
	t_val	*current;

	current = zone->env;
	while (ft_strcmp(current->name, "PWD") != 0)
		current = current -> next;
	if (current -> next != NULL)
		printf("%s\n", current->value);
	else
	{
		perror("pwd");
		zone->exito = 1;
	}
}
