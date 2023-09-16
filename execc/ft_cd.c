/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:30:39 by ckannane          #+#    #+#             */
/*   Updated: 2023/09/16 17:34:38 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	apply_empty_cd(t_zid *zone)
{
	int		found;
	t_val	*current;

	current = zone->env;
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
		zone->exito = 1;
	}
	else
		chdir(current->value);
}

void	apply_cd(t_zid *new_path, t_zid	*old_path, t_zid *zone)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		free(old_path->env->value);
		old_path->env->value = ft_strdup(new_path->env->value);
		free(new_path->env->value);
		new_path->env->value = ft_strdup(cwd);
		free(old_path->exp->value);
		old_path->exp->value = ft_strdup(new_path->exp->value);
		free(new_path->exp->value);
		new_path->exp->value = ft_strdup(cwd);
	}
	else
	{
		perror("getcwd");
		zone->exito = 1;
	}
	free (cwd);
}

void	ft_cd(t_com *com, t_zid *zone)
{
	t_zid	*oldpwd_path;
	t_zid	*pwd_path;

	oldpwd_path = malloc(sizeof(t_zid));
	*oldpwd_path = *zone;
	pwd_path = malloc(sizeof(t_zid));
	*pwd_path = *zone;
	while (ft_strcmp(pwd_path->env->name, "PWD") != 0)
		pwd_path->env = pwd_path->env -> next;
	while (ft_strcmp(pwd_path->exp->name, "PWD") != 0)
		pwd_path->exp = pwd_path->exp-> next;
	while (ft_strcmp(oldpwd_path->env->name, "OLDPWD") != 0)
		oldpwd_path->env = oldpwd_path->env -> next;
	while (ft_strcmp(oldpwd_path->exp->name, "OLDPWD") != 0)
		oldpwd_path->exp = oldpwd_path->exp -> next;
	if (com->arg[0] == NULL)
		apply_empty_cd(zone);
	else if (chdir(com->arg[0]) == -1)
	{
		perror("cd");
		zone->exito = 1;
	}
	apply_cd(pwd_path, oldpwd_path, zone);
}
