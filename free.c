/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:23:07 by ckannane          #+#    #+#             */
/*   Updated: 2023/09/15 16:37:12 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_t_com_list(t_com *head)
{
	t_com *temp;
    while (head != NULL)
	{
        temp = head;
        head = head->next;
        if (temp->after_red != NULL) {
            int i = 0;
            while (temp->after_red[i] != NULL) {
                free(temp->after_red[i]);
                i++;
            }
            free(temp->after_red);
        }
        if (temp->arg != NULL) {
            int i = 0;
            while (temp->arg[i] != NULL) {
                free(temp->arg[i]);
                i++;
            }
            free(temp->arg);
        }
        if (temp->slp != NULL) {
            int i = 0;
            while (temp->slp[i] != NULL) {
                free(temp->slp[i]);
                i++;
            }
            free(temp->slp);
        }
        if (temp->sp != NULL) {
            int i = 0;
            while (temp->sp[i] != NULL) {
                free(temp->sp[i]);
                i++;
            }
            free(temp->sp);
        }
        free(temp->word);
        free(temp->commad);
        free(temp->var);
        free(temp);
    }
}