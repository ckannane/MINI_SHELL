/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 22:07:17 by ckannane          #+#    #+#             */
/*   Updated: 2023/09/15 11:02:09 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "Libft/libft.h"
# include <sys/wait.h>
# include <dirent.h>

typedef struct s_com
{
	char			*word;
	char			*commad;
	char			**after_red;
	char			**arg;
	char			**slp;
	int				s_quot;
	int				d_quot;
	int				output;
	int				input;
	int				herdo;
	int				sq;
	char			**sp;
	int				dq;
	char			*var;
	int				var_len;
	struct s_com	*next;
}t_com;

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


void	rl_replace_line(const char *text, int clear_undo);
char	**split_arg(char *str);
int		ft_strcmp(char *s1, char *s2);
void	ft_echo(t_com *p);
int		ft_strcmp(char *s1, char *s2);
void	ft_pwd(t_val *env);
void	ft_export(t_com *com, t_zid *zone);
t_val	*ft_val_re_new(char *content);
void	ft_valadd_back(t_val **val, t_val *new);
void	custom_ls(char **args);
t_val	*int_env(char **env);
char	*save_before_equal(char *input);
char	*save_after_equal(char *input);
void	ft_unset(t_com *com, t_zid *zone);
int		search_for_redirection(t_com *com);
void	apply_fd(t_com *com);
void	sigintHandler(int signum);
int		vip_command_check(t_com *com);
void	exe_builtins(t_com *com, t_zid *zone);
void	execute_command(t_com *com ,t_zid *zone);
int		ft_cd(t_com *com, t_zid *zone);
t_com	*ft_comlast(t_com *com);
char	**pas_env(t_val *env);
char	**get_path(char *command, t_val *env);
char	*ft_strjoin_env(char const *s1, char const *s2);
void	ft_comadd_back(t_com **com, t_com *new);
char	*expansion(t_com *com, t_val *env, char *line);
int		check_quote(char *line);
int		ft_strcmp(char *s1, char *s2);
t_com	*ft_comnew(char *line);
char	*expd(t_com *com ,char *str, t_val	*env);
void	routine(char *str, int i,t_com *com, t_val *env);
char	*var_expand(t_com *sh, t_val *env);
int		count_var_size(char *str);
int		check_q(char *str);
char 	**split_with_quotes(char *str, char c);
#endif