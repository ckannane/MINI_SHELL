/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:46:50 by ckannane          #+#    #+#             */
/*   Updated: 2022/10/14 15:38:06 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t n)
{
	size_t	i;
	char	*p;
	char	o;

	p = (char *) b;
	o = (char) c;
	i = 0;
	while (i < n)
	{
		p[i] = o;
		i++;
	}
	return (p);
}
