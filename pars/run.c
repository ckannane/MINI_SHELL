
#include "../minishell.h"

char	*fill_the_quotes(char *str,char curr_char, char curr, int res)
{
	char	*result;
	int		i;
	int		j;

	j = 0;
	i = 0;
	result = (char *)malloc(res + 1);
	curr = '\0';
	while (str[i] != '\0')
	{
		curr_char = str[i];
		if ((curr_char == '\'' || curr_char == '"') && curr == '\0')
			curr = curr_char;
		else if (curr_char == curr)
			curr = '\0';
		else
			result[j++] = curr_char;
		i++;
	}
	result[j] = '\0';
	return (result);
}

char	*return_without_quote(char *str)
{
	char	curr;
	int		res;
	char	curr_char;
	int		i;

	i = 0;
	curr = '\0';
	res = ft_strlen(str);
	while (str[i] != '\0')
	{
		curr_char = str[i];
		if ((curr_char == '\'' || curr_char == '"') && curr == '\0')
			curr = curr_char;
		else if (curr_char == curr)
		{
			curr = '\0';
			res--;
		}
		i++;
	}
	return (fill_the_quotes(str,curr_char,curr,res));
}

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

void	execute_command(t_com *com ,t_zid *zone)
{
	char	**path;
	int		i;
	char	**env_set;
	int		status;
	int exito;
	pid_t	pid;

	i = 0;
	env_set = pas_env(zone->env);
	pid = fork();
	if (pid == 0)
	{
		if (my_access(com->commad, X_OK) == 0)
		{
			execve(com->commad, com->slp, env_set);
			perror("execve");
			exit(126);
		}
		if (search_path(zone->env) == 1)
			path = get_path(com->commad, zone->env);
		else
		{
			ft_putendl_fd("command not found:", 2);
			exit(127);
		}
		while (path[i])
		{
			if (my_access(path[i], X_OK) == 0)
			{
				execve(path[i], com->after_red, env_set);
				perror("execve");
				exit(126);
			}
			i++;
		}
		ft_putendl_fd("command not found", 2);
		exit(127);
	}
	else if (pid > 0)
	{
		if (wait(&status) == -1)
		{
			perror("wait");
			exit(EXIT_FAILURE);
		}
		if (WIFEXITED(status) != 0)
			exito = WEXITSTATUS(status);
	}
	else
		perror("fork");
}

char	*set_command(char **slp)
{
	int	i;

	i = 0;
	if (slp == NULL)
	        return (ft_strdup(""));

	if ((ft_strcmp(slp[0], ">") == 0 || ft_strcmp(slp[0], ">>") == 0
	|| ft_strcmp(slp[0], "<") == 0 || ft_strcmp(slp[0], "<<") == 0))
	{
		if (slp[2] == NULL)
	        return (NULL);
		else
			return (ft_strdup(return_without_quote(slp[2])));
	}
	return (ft_strdup(return_without_quote(slp[0])));
}

int isSymbol(char c)
{
    return (c == '<' || c == '>');
}

char* redirection_split(char* input)
{
	int len;
	int i = 0;
	int j = 0;
	char c_tmp;
	char	*result;

	len = strlen(input);
	result = (char*)malloc((2 * len + 1) * sizeof(char));
	while (i < len)
	{
	    c_tmp = input[i];
	    if (isSymbol(c_tmp))
		{
	        result[j++] = ' ';
	        result[j++] = c_tmp;
	        if (i < len - 1 && isSymbol(input[i + 1]))
	            result[j++] = input[i++ + 1];
	        result[j++] = ' ';
	    } else
	        result[j++] = c_tmp;
	    i++;
	}
	result[j] = '\0';
	return (result);
}


void	read_com(t_com *com, t_zid *zone, char *line)
{
	int		i;
	char	*tmp;
	int		num_args;
	int		j;

	i = 0;
	com->sp = ft_split(com->word, ' ');
	//printf("1");
	tmp = expansion(com ,zone->env, line);
	//printf("1");
	tmp = return_without_quote(tmp);
	//printf("1");
	tmp = redirection_split(tmp);
	com->slp = ft_split(tmp, ' ');
	if (com->slp[0] == NULL)
		return ;
	com->commad = set_command(com->slp);
	//printf("this is %s",com->commad);
	//exit(0);
	num_args = 0;
	if ((ft_strcmp(com->slp[0], "<<") == 0) || \
	(ft_strcmp(com->slp[0],"<") == 0))
		i = i + 2;
	while (com->slp[i])
	{
		if ((ft_strcmp(com->slp[i], ">") == 0 || \
		ft_strcmp(com->slp[i],">>") == 0 || ft_strcmp(com->slp[i], "<") == 0 \
		|| ft_strcmp(com->slp[i], "<<") == 0))
			break ;
	num_args++;
	i++;
	}
	if (num_args == 0)
		return ;
	com->after_red = (char **)malloc((num_args + 1) * sizeof(char *));
	if (!com->after_red)
		com->after_red = NULL;
	com->arg = (char **)malloc((num_args + 1) * sizeof(char *));
	if (!com->arg)
		com->arg = NULL;
	i = 1;
	j = 0;
	while (j < num_args - 1)
		com->arg[j++] = ft_strdup(com->slp[i++]);
	com->arg[j] = NULL;
	j = 0;
	while (j < num_args)
	{
		com->after_red[j] = ft_strdup(com->slp[j]);
		j++;
	}
	com->after_red[j] = NULL;
}

void	exe_builtins(t_com *com, t_zid *zone)
{
	if (ft_strcmp(com->commad, "cd") == 0)
		ft_cd(com, zone);
	else if (ft_strcmp(com->commad, "pwd") == 0)
		ft_pwd(zone->env);
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
	{
		while (zone->env)
		{
			printf("%s=%s\n", zone->env->name, zone->env->value);
			zone->env = zone->env->next;
		}
	}
}

int	vip_command_check(t_com *com)
{
	if (ft_strcmp(com->commad, "cd") == 0 || ft_strcmp(com->commad, "pwd") == 0 \
	|| ft_strcmp(com->commad, "echo") == 0 || ft_strcmp(com->commad,"export") == 0 \
	|| ft_strcmp(com->commad, "unset") == 0 \
	|| ft_strcmp(com->commad, "env") == 0 || ft_strcmp(com->commad,"exit") == 0)
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
		read_com(com , zone, line);
		com = com->next;
	}
}

void	exe_with_fork(t_zid *zone, t_com *com)
{
	pid_t	child_pid;
	int		status;
	int		fid[2];
	int		exito;
	int stdi = dup(0);
	int stdo = dup(1);
	while (com){
		pipe(fid);
		child_pid = fork();
		if (!child_pid){
			close(fid[0]);
			if (com->next)
				dup2(fid[1], 1);
			turn_on(com,zone);
			close(fid[1]);
			exit(0);
		}
		close(fid[1]);
		dup2(fid[0], 0);
		waitpid(child_pid, &status, WNOHANG);
		exito = WEXITSTATUS(status);
		close(fid[0]);
		com = com->next;
	}
	int uid = wait(&status);
	while (uid > 0)
	{
		if (uid < child_pid)
			exito = WEXITSTATUS(status);
		uid = wait(&status);
	}
	exito = WEXITSTATUS(status);
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
		//shell->exito = 1;
		ft_putstr_fd("Syntax error\n", 2);
		return ;
	}
	i = 0;
	all = split_with_quotes(line, '|');
	i =0;
	while (all[i])
	{
		index = ft_comnew(all[i]);
		ft_comadd_back(&com, index);
		i++;
	}
	i = 0;
	intial_com(com, zone, line);
	//printf("this is %s\n",com->commad);
	if (com->slp[0] == NULL)
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
	return zone;
}

int main(int ac, char **av, char **env)
{
	char *line;
	t_zid *zone;
	t_zid	*current = NULL;
	(void)ac;
	(void)av;
	t_com *com;
	current = malloc(sizeof(t_zid));
	com = malloc(sizeof(t_com));
	com = NULL;
	zone = lets_start(env);
	signal(SIGQUIT, SIG_IGN);
	while (1) {
		*current = *zone;
		signal(SIGINT, sigintHandler);
		line = readline("[minishell] $> ");
		if (line == NULL)
			break;
		if (*line) {
			track_com(line, current,com);
			add_history(line);
		}
		free(line);
	}
	//free(current);
	//free(shell->zone->env);
	//free(shell->zone->exp);
	//free(shell->zone);
	//free(shell);
	return 0;
}
