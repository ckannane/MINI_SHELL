/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 10:05:00 by ckannane          #+#    #+#             */
/*   Updated: 2023/09/11 15:54:01 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void delete_val(t_val **head, char *str)
{
	t_val *current = *head;
	t_val *pre = NULL;

	if(current != NULL && ft_strcmp(current->name,str) == 0)
	{
		*head = current->next;
        free(current);
        return;
	}
	while (current != NULL && ft_strcmp(current->name,str) != 0) {
        pre = current;
        current = current->next;
    }
	if (current == NULL) {
		printf("nor found\n");
        return;
    }
	printf("we found him\n");
	pre->next = current->next;
	free(current);
}

void	ft_unset(t_com *com, t_zid *zone)
{
	int i = 0;
	while(com->arg[i])
	{
		printf("the unset applyed on (%s)\n",com->arg[i]);
		delete_val(&zone->env,com->arg[i]);
		delete_val(&zone->exp,com->arg[i]);
		i++;
	}
}