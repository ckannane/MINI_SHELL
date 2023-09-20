/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 22:07:17 by ckannane          #+#    #+#             */
/*   Updated: 2023/09/20 12:06:57 by ckannane         ###   ########.fr       */
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
	int				output;
	int				input;
	int				herdo;
	int				sq;
	int				dq;
	int				var_len;
	char			*var;
	char			**sp;
	char			**after_red;
	char			**arg;
	char			**slp;
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
	int		exito;
}t_zid;

typedef struct s_slp_p
{
	int	initial_capacity;
	int	word_count;
	int	inside_quotes;
	int	word_start;
	int	i;
}t_slp_p;

void	rl_replace_line(const char *text, int clear_undo);
char	**split_arg(char *str);
int		ft_strcmp(char *s1, char *s2);
void	ft_echo(t_com *p);
int		ft_strcmp(char *s1, char *s2);
void	ft_pwd(t_zid *zone);
void	ft_export(t_com *com, t_zid *zone);
t_val	*ft_val_re_new(char *content);
void	ft_valadd_back(t_val **val, t_val *new);
t_val	*int_env(char **env);
char	*save_before_equal(char *input);
char	*save_after_equal(char *input);
void	ft_unset(t_com *com, t_zid *zone);
int		search_for_redirection(t_com *com);
void	apply_fd(t_com *com);
void	sigintHandler(int signum);
int		vip_command_check(t_com *com);
void	exe_builtins(t_com *com, t_zid *zone);
void	execute_command(t_com *com, t_zid *zone);
void	ft_cd(t_com *com, t_zid *zone);
t_com	*ft_comlast(t_com *com);
char	**pas_env(t_val *env);
char	**get_path(char *command, t_val *env);
char	*ft_strjoin_env(char *s1, char *s2);
void	ft_comadd_back(t_com **com, t_com *new);
char	*expansion(t_com *com, t_zid *zone);
int		check_quote(char *line);
int		ft_strcmp(char *s1, char *s2);
t_com	*ft_comnew(char *line);
char	*expd(t_com *com, char *str, t_zid	*zone);
void	routine(char *str, int i, t_com *com, t_zid *zone);
char	*var_expand(t_com *sh, t_val *env);
int		count_var_size(char *str);
int		check_q(char *str);
char	**split_with_quotes(char *str, char c, int slp_num, int slp_go);
char	*return_without_quote(char *str);
char	*set_command(char **slp);
void	read_com(t_com *com, t_zid *zone, char *line);
char	**splitstring(char *input);
void	free_t_com_list(t_com *head);
void	run_child(t_com *com, t_zid *zone, int	*fid);
void	in_the_verse(t_zid *zone, int status, pid_t child_pid);
void	run_parent(pid_t child_pid, int status, int *fid, t_zid *zone);
void	exe_with_fork(t_zid *zone, t_com *com);
void	turn_on(t_com *com, t_zid *zone);
void	intial_com(t_com *com, t_zid *zone, char *line);
int		how_much_com(t_com *com);
int		vip_command_check(t_com *com);
void	exe_builtins(t_com *com, t_zid *zone);
void	start_the_exe(t_zid *zone, t_com *com);
void	execute_command(t_com *com, t_zid *zone);
void	launch_execve(t_com *com, t_zid *zone, char **env_set, int i);
void	acces(char *com, char **all_com, char **env_set);
int		search_path(t_val *env);
int		my_access(char *path, int mode);
void	install_arg(t_com *com, int num_args);
int		set_arg_size(t_com *com);
char	*redirection_split(char *input);
char	*fill_the_red(int len, int i, int j, char *input);
char	*ft_strncpy(char *dest, char *src, unsigned int n);
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);
void	sigcheck(int sig);
int		looking_for_her(char **slp);
char	*detect_file(char **spl);
int		search_for_redirection(t_com *com);
int		check_val(t_val *zone, char *content);
void	free_double(char **target);
void	ft_exit(t_com *com, t_zid *zone);
char	**ft_splito(char *str);
void	free_zone(t_zid *zone);
t_slp_p	*init_slp_p(void);
void	fill_it(t_slp_p	*val, char *word, char *input, char **words);
#endif