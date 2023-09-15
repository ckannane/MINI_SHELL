/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 10:07:29 by ckannane          #+#    #+#             */
/*   Updated: 2023/09/15 15:57:16 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(t_zid *zone)
{
	t_val	*current;

	current = zone->env;
	while(ft_strcmp(current->name, "PWD") != 0)
		current = current -> next;
 	if (current -> next != NULL)
		printf("%s\n", current->value);
	else
	{
		perror("pwd");
		zone->exito = 1;
	}
}