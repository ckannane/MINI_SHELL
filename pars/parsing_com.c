/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_com.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 12:08:41 by ckannane          #+#    #+#             */
/*   Updated: 2023/09/20 00:38:42 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exe_builtins(t_com *com, t_zid *zone)
{
	t_val	*current;

	current = zone->env;
	if (ft_strcmp(com->commad, "cd") == 0)
		ft_cd(com, zone);
	else if (ft_strcmp(com->commad, "pwd") == 0)
		ft_pwd(zone);
	else if (ft_strcmp(com->commad, "echo") == 0)
		ft_echo(com);
	else if (ft_strcmp(com->commad, "export") == 0)
		ft_export(com, zone);
	else if (ft_strcmp(com->commad, "unset") == 0)
		ft_unset(com, zone);
	else if (ft_strcmp(com->commad, "exit") == 0)
		ft_exit(com, zone);
	else if (ft_strcmp(com->commad, "env") == 0)
	{
		while (current)
		{
			printf("%s=%s\n", current->name, current->value);
			current = current->next;
		}
	}
}

int	vip_command_check(t_com *com)
{
	if (ft_strcmp(com->commad, "cd") == 0 \
		|| ft_strcmp(com->commad, "pwd") == 0 \
		|| ft_strcmp(com->commad, "echo") == 0 \
		|| ft_strcmp(com->commad, "export") == 0 \
		|| ft_strcmp(com->commad, "unset") == 0 \
		|| ft_strcmp(com->commad, "env") == 0 \
		|| ft_strcmp(com->commad, "exit") == 0)
		return (1);
	else
		return (0);
}

int	how_much_com(t_com *com)
{
	int	i;

	i = 0;
	if (com->commad == NULL)
		return (0);
	while (com)
	{
		if (*com->commad)
			i++;
		com = com->next;
	}
	return (i);
}

void	intial_com(t_com *com, t_zid *zone, char *line)
{
	while (com)
	{
		read_com(com, zone, line);
		com = com->next;
	}
}

void	start_the_exe(t_zid *zone, t_com *com)
{
	if (com->slp[0] == NULL || com->commad == NULL)
		return ;
	if (how_much_com(com) > 1 || search_for_redirection(com) != 0)
		exe_with_fork(zone, com);
	else
		turn_on(com, zone);
}
