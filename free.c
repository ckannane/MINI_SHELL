/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:23:07 by ckannane          #+#    #+#             */
/*   Updated: 2023/09/16 19:39:38 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_double(char **target)
{
	int	i;

	i = 0;
	while (target[i] != NULL)
	{
		free(target[i]);
		i++;
	}
	free(target);
}

void	free_t_com_list(t_com *head)
{
	t_com	*temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		if (temp->after_red != NULL)
			free_double(temp->after_red);
		if (temp->arg != NULL)
			free_double(temp->arg);
		if (temp->slp != NULL)
			free_double(temp->slp);
		if (temp->sp != NULL)
			free_double(temp->sp);
		free(temp->word);
		free(temp->commad);
		free(temp->var);
		free(temp);
	}
}
