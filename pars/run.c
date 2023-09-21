/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 13:08:59 by ckannane          #+#    #+#             */
/*   Updated: 2023/09/21 11:53:01 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_the_line(char *str)
{
	int	i;
	int	n;
	int	j;

	n = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
		{
			n = 1;
			j = i;
			while (str[++j])
			{
				if (str[j] != ' ' && str[j] != '\t' && \
				str[j] != '\0' && str[j] != '|')
				{
					n = 0;
					break ;
				}
			}
		}
		i++;
	}
	return (n);
}

void	track_com(char *line, t_zid *zone, t_com *com)
{
	char	**all;
	int		i;
	t_com	*index;

	if (check_quote(line) || check_the_line(line))
	{
		zone->exito = 1;
		ft_putstr_fd("Syntax error\n", 2);
		return ;
	}
	i = 0;
	all = splitstring(line);
	if (all[0] == NULL)
		return ;
	com = NULL;
	while (all[i])
	{
		index = ft_comnew(all[i++]);
		ft_comadd_back(&com, index);
	}
	intial_com(com, zone, line);
	start_the_exe(zone, com);
	free_t_com_list(com);
	free_double(all);
}

void	siginthandler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	if (signum == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

t_zid	*lets_start(char **env)
{
	t_zid	*zone;

	zone = malloc(sizeof(t_zid));
	zone->env = int_env(env);
	zone->exp = int_env(env);
	zone->exito = 0;
	return (zone);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_zid	*zone;
	t_com	*com;

	(void)av;
	if (ac == 1)
	{
		zone = lets_start(env);
		com = malloc(sizeof(t_com));
		while (1)
		{
			signal(SIGINT, siginthandler);
			signal(SIGQUIT, siginthandler);
			line = readline("[minishell] $> ");
			if (line == NULL)
				break ;
			if (*line)
			{
				track_com(line, zone, com);
				add_history(line);
			}
			free(line);
		}
	}
	return (0);
}
