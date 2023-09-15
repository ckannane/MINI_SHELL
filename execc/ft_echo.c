/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 09:26:50 by ckannane          #+#    #+#             */
/*   Updated: 2023/09/13 00:29:53 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_echo_flag(char	*str)
{
	int i = 0;
	if(str[i] != '-' && str[i+1] != 'n')
		return 0;
	i++;
	while(str[i])
	{
		if(str[i] != 'n')
			return 0;
		i++;
	}
	return 1;
}


void ft_echo(t_com *p)
{
	int i = 0;
	int j = 0;
	int x = 0;
	int fl = 0;

	if (ft_strcmp(p->commad,"echo" )!= 0)
		return ;
	if (p->arg == NULL)
		return ;
	if(p->arg[0] == NULL)
		return;
	if (check_echo_flag(p->arg[0]) == 1)
	{
		fl = 1;
		i++;
	}
	while (p->arg[i])
	{
		j = 0;
		if(x == 1)
		{
			x = 0;
			write(1," ",1);
		}
		while (p->arg[i][j])
		{
			//if(p->arg[i][j] == '\"' || p->arg[i][j] == '\'')
			//	j++;
			//else if(p->arg[i][j])
			x = 1;
			write(1,&p->arg[i][j++],1);
		}
		i++;
	}
	if(fl == 0)
		write(1,"\n",1);
}