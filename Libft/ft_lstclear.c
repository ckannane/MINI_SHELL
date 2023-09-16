/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 01:01:27 by ckannane          #+#    #+#             */
/*   Updated: 2023/09/16 19:42:38 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*list;
	t_list	*go;

	if (lst == NULL || del == NULL)
		return ;
	list = *lst;
	while (list)
	{
		go = list->next;
		ft_lstdelone (list, del);
		list = go;
	}
	*lst = NULL;
}
