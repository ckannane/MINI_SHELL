/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 13:08:59 by ckannane          #+#    #+#             */
/*   Updated: 2023/09/15 23:54:33 by ckannane         ###   ########.fr       */
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
void	acces(char *com,char **all_com ,char **env_set)
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

void	execute_command(t_com *com ,t_zid *zone)
{
	//char	**path;
	//int		i;
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

void	exe_builtins(t_com *com, t_zid *zone)
{
	t_val	*current;

	current = zone->env;
	if (ft_strcmp(com->commad, "cd") == 0)
		ft_cd(com, zone);
	else if (ft_strcmp(com->commad, "pwd") == 0)
		ft_pwd(zone);
	else if (ft_strcmp(com->commad, "echo") == 0 && com->arg != NULL)
		ft_echo(com);
	else if (ft_strcmp(com->commad, "export") == 0)
		ft_export(com, zone);
	else if (ft_strcmp(com->commad, "unset") == 0)
		ft_unset(com, zone);
	else if (ft_strcmp(com->commad, "exit") == 0)
	{
		printf("Exiting the minishell.\n");
		exit(0);
	}
	else if (ft_strcmp(com->commad, "env") == 0)
		while (current)
		{
			printf("%s=%s\n", current->name, current->value);
			current = current->next;
		}
}

int	vip_command_check(t_com *com)
{
	if (ft_strcmp(com->commad, "cd") == 0
		|| ft_strcmp(com->commad, "pwd") == 0
		|| ft_strcmp(com->commad, "echo") == 0
		|| ft_strcmp(com->commad,"export") == 0
		|| ft_strcmp(com->commad, "unset") == 0
		|| ft_strcmp(com->commad, "env") == 0
		|| ft_strcmp(com->commad,"exit") == 0)
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

void	turn_on(t_com *com ,t_zid *zone)
{
	if (search_for_redirection(com) != 0)
		apply_fd(com);
	if (vip_command_check(com) == 1 && com->commad != NULL)
		exe_builtins(com,zone);
	else if (com->commad != NULL)
		execute_command(com,zone);
}

void	intial_com(t_com *com ,t_zid *zone, char *line)
{
	while (com)
	{
		read_com(com, zone, line);
		com = com->next;
	}
}

void	run_child(t_com *com, t_zid *zone, int	*fid)
{
	close(fid[0]);
	if (com->next)
		dup2(fid[1], 1);
	turn_on(com,zone);
	close(fid[1]);
	exit(0);
}

void	exe_with_fork(t_zid *zone, t_com *com)
{
	pid_t	child_pid;
	int		status;
	int		fid[2];
	int		stdi;
	int		stdo;
	int		uid;
	stdi = dup(0);
	stdo = dup(1);
	//t_zid	*current;

	//current = malloc(sizeof(t_zid));
	//current = NULL;
	//*current = *zone;
	while (com)
	{
		pipe(fid);
		child_pid = fork();
		if (!child_pid)
			run_child(com,zone,fid);
		close(fid[1]);
		dup2(fid[0], 0);
		waitpid(child_pid, &status, WNOHANG);
		zone->exito = WEXITSTATUS(status);
		close(fid[0]);
		com = com->next;
	}
	uid = wait(&status);
	while (uid > 0)
	{
		if (uid < child_pid)
			zone->exito = WEXITSTATUS(status);
		uid = wait(&status);
	}
	zone->exito = WEXITSTATUS(status);
	dup2(stdi, 1);
	dup2(stdo, 0);
}

void	track_com(char *line, t_zid *zone, t_com *com)
{
	char	**all;
	int		i;
	t_com	*index;

	if (check_quote(line))
	{
		zone->exito = 1;
		ft_putstr_fd("Syntax error\n", 2);
		return ;
	}
	i = 0;
	all = splitString(line);
	if(all[0] == NULL)
		return;
	while (all[i])
	{
		index = ft_comnew(all[i++]);
		ft_comadd_back(&com, index);
	}
	intial_com(com, zone, line);
	if (com->slp[0] == NULL || com->commad == NULL)
		return ;
	if (how_much_com(com) > 1 || search_for_redirection(com) != 0)
		exe_with_fork(zone,com);
	else
		turn_on(com,zone);
}

void	sigintHandler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

t_zid *lets_start(char **env)
{
	t_zid *zone;

	zone = malloc(sizeof(t_zid));
	zone->env = int_env(env);
	zone->exp = int_env(env);
	zone->exito = 0;
	return zone;
}

int main(int ac, char **av, char **env)
{
	char *line;
	t_zid *zone;
	(void)ac;
	(void)av;
	t_com *com;

	com = malloc(sizeof(t_com));
	zone = lets_start(env);
	signal(SIGQUIT, SIG_IGN);
	com = NULL;
	while (1)
	{
		signal(SIGINT, sigintHandler);
		line = readline("[minishell] $> ");
		if (line == NULL)
			break;
		if (*line)
		{
			track_com(line, zone,com);
			add_history(line);
		}
		free_t_com_list(com);
		free(line);
	}
	return 0;
}
