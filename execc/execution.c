/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 12:01:07 by ckannane          #+#    #+#             */
/*   Updated: 2023/09/19 23:56:55 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	turn_on(t_com *com, t_zid *zone)
{
	if (search_for_redirection(com) != 0)
		apply_fd(com);
	if (vip_command_check(com) == 1 && com->commad != NULL)
		exe_builtins(com, zone);
	else if (com->commad != NULL)
		execute_command(com, zone);
}

void	run_child(t_com *com, t_zid *zone, int	*fid)
{
	close(fid[0]);
	if (com->next)
		dup2(fid[1], 1);
	turn_on(com, zone);
	close(fid[1]);
	exit(0);
}

void	in_the_verse(t_zid *zone, int status, pid_t child_pid)
{
	int		uid;

	uid = wait(&status);
	while (uid > 0)
	{
		if (uid < child_pid)
			zone->exito = WEXITSTATUS(status);
		uid = wait(&status);
	}
	zone->exito = WEXITSTATUS(status);
}

void	run_parent(pid_t child_pid, int status, int *fid, t_zid *zone)
{
	close(fid[1]);
	dup2(fid[0], 0);
	waitpid(child_pid, &status, WNOHANG);
	zone->exito = WEXITSTATUS(status);
	close(fid[0]);
}

void	exe_with_fork(t_zid *zone, t_com *com)
{
	pid_t	child_pid;
	int		status;
	int		*fid;
	int		stdi;
	int		stdo;

	stdi = dup(0);
	stdo = dup(1);
	status = 0;
	fid = malloc(sizeof(int) * 2);
	while (com)
	{
		pipe(fid);
		child_pid = fork();
		if (!child_pid)
			run_child(com, zone, fid);
		run_parent(child_pid, status, fid, zone);
		com = com->next;
	}
	in_the_verse(zone, status, child_pid);
	dup2(stdi, 0);
	dup2(stdo, 1);
	free(fid);
}
