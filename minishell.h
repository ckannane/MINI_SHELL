/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 20:04:54 by ckannane          #+#    #+#             */
/*   Updated: 2023/09/12 16:17:10 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "Libft/libft.h"
#include <sys/wait.h>
#include <dirent.h>

typedef struct s_com
{
	char	*line;
	char	*word;
	char	*commad;
	char	**after_red;
	char	**arg;
	char	**slp;
	int 	s_quot;
	int 	d_quot;
	int		output;
	int		input;
	int		herdo;
	int		sq;
	char	**sp;
    int		dq;
	char	*var;
	int	exit_status;
	struct s_red	*red;
	struct s_com	*next;
	pid_t pid;
}t_com;

typedef struct s_red
{
	char			*redit;
	char			*file;
	struct s_red	*next;
}t_red;

typedef struct s_val
{
	char			*content;
	char			*name;
	char			*value;
	struct s_val	*next;
}t_val;

typedef struct s_zid
{
	t_val	*exp;
	t_val	*env;
}t_zid;

//readline
void	rl_replace_line (const char *text, int clear_undo);

char	**split_arg(char *str);
int		ft_strcmp(char *s1,char *s2);
void	ft_echo(t_com *p);
int		ft_strcmp(char *s1,char *s2);
void	ft_pwd(t_val *env);
int		ft_cd(t_com *com,t_zid *zone);
t_val	*ft_valnew(char *content,char *name);
void    ft_export(t_com *com,t_zid *zone);
t_val	*ft_val_re_new(char*content);
void	ft_valadd_back(t_val **val, t_val *new);
void custom_ls(char **args);
t_val	*int_env(char **env);
char *save_before_equal(char *input);
char *save_after_equal(char *input);
void	ft_unset(t_com *com, t_zid *zone);
int	search_for_redirection(t_com *com);
void apply_fd(t_com *com,t_zid *zone) ;
void sigintHandler(int signum);
int		vip_command_check(t_com *com);
void	exe_builtins(t_com *com , t_zid *zone);
void execute_command(char *command, char **arguments, t_val *env);

#endif