/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:30:39 by ckannane          #+#    #+#             */
/*   Updated: 2023/09/15 10:27:55 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	apply_empty_cd(t_val	*current)
{
	int found;

	found = 0;
	while (current)
	{
		if (ft_strcmp(current->name, "HOME") == 0)
		{
			found = 1;
			break ;
		}
		current = current -> next;
	}
	if (found == 0)
	{
		perror("cd");
		//shell->exito = 1;
	}
	else
	chdir(current->value);
}

void	apply_cd(t_zid *zone, t_zid	*old_path)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		free(old_path->env->value);
		old_path->env->value = ft_strdup(zone->env->value);
		free(zone->env->value);
		zone->env->value = ft_strdup(cwd);
		free(old_path->exp->value);
		old_path->exp->value = ft_strdup(zone->exp->value);
		free(zone->exp->value);
		zone->exp->value = ft_strdup(cwd);
	}
	else
	{
		perror("getcwd");
		//shell->exito = 1;
	}
}

int	ft_cd(t_com *com, t_zid *zone)
{
	t_zid	*old_path;
	t_val	*current;

	old_path = malloc(sizeof(t_zid));
	*old_path = *zone;
	current = malloc(sizeof(t_val));
	*current = *zone->env;
	while (ft_strcmp(zone->env->name, "PWD") != 0)
		zone->env = zone->env -> next;
	while (ft_strcmp(zone->exp->name, "PWD") != 0)
		zone->exp = zone->exp -> next;
	while (ft_strcmp(old_path->env->name, "OLDPWD") != 0)
		old_path->env = old_path->env -> next;
	while (ft_strcmp(old_path->exp->name, "OLDPWD") != 0)
		old_path->exp = old_path->exp -> next;
	if (com->arg[0] == NULL)
		apply_empty_cd(current);
	else if (chdir(com->arg[0]) == -1)
	{
		perror("cd");
		//exito = 1;
		return (-1);
	}
	apply_cd(zone, old_path);
	return (0);
}
