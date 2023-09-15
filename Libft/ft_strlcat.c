/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 15:01:21 by ckannane          #+#    #+#             */
/*   Updated: 2022/10/09 16:51:52 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	ldst;
	size_t	lsrc;

	i = 0;
	if (!dst && dstsize == 0)
		return (0);
	ldst = ft_strlen(dst);
	lsrc = ft_strlen(src);
	if (dstsize < ldst + 1)
		return (dstsize + lsrc);
	if (dstsize > ldst + 1)
	{
		while (src[i] != '\0' && ldst + 1 + i < dstsize)
		{
			dst [ldst + i] = src[i];
			i++;
		}
	}
	dst [ldst + i] = '\0';
	return (ldst + lsrc);
}
