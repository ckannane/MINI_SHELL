/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 10:05:00 by ckannane          #+#    #+#             */
/*   Updated: 2023/09/21 01:14:25 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	delete_val(t_val **head, char *str)
{
	t_val	*current;
	t_val	*pre;

	current = *head;
	if (current != NULL && ft_strcmp(current->name, str) == 0)
	{
		*head = current->next;
		free(current);
		return ;
	}
	while (current != NULL && ft_strcmp(current->name, str) != 0)
	{
		pre = current;
		current = current->next;
	}
	if (current == NULL)
		return ;
	pre->next = current->next;
	free(current);
}

void	ft_unset(t_com *com, t_zid *zone)
{
	int	i;

	i = 0;
	while (com->arg[i])
	{
		if (ft_strcmp(com->arg[i], "_"))
		{
			delete_val(&zone->exp, com->arg[i]);
			delete_val(&zone->env, com->arg[i]);
		}
		i++;
	}
}
