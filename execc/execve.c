/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 12:12:46 by ckannane          #+#    #+#             */
/*   Updated: 2023/09/16 17:33:36 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	my_access(const char *path, int mode)
{
	if (access(path, mode) == 0)
		return (0);
	else
		return (-1);
}

int	search_path(t_val *env)
{
	while (env)
	{
		if (ft_strcmp(env->name, "PATH") == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

void	acces(char *com, char **all_com, char **env_set)
{
	execve(com, all_com, env_set);
	perror("execve");
	exit(126);
}

void	launch_execve(t_com *com, t_zid *zone, char **env_set, int i)
{
	char	**path;

	path = NULL;
	if (my_access(com->commad, X_OK) == 0)
		acces(com->commad, com->slp, env_set);
	if (search_path(zone->env) == 1)
		path = get_path(com->commad, zone->env);
	while (path[i])
	{
		if (my_access(path[i], X_OK) == 0)
		{
			acces(path[i], com->after_red, env_set);
			exit(0);
		}
		i++;
	}
	ft_putendl_fd("command not found", 2);
	exit(127);
}

void	execute_command(t_com *com, t_zid *zone)
{
	char	**env_set;
	int		status;
	pid_t	pid;

	env_set = pas_env(zone->env);
	pid = fork();
	if (pid == 0)
		launch_execve(com, zone, env_set, 0);
	else if (pid > 0)
	{
		if (wait(&status) == -1)
		{
			perror("wait");
			exit(EXIT_FAILURE);
		}
		if (WIFEXITED(status) != 0)
			zone->exito = WEXITSTATUS(status);
	}
	else
		perror("fork");
}
