/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 13:36:25 by ckannane          #+#    #+#             */
/*   Updated: 2022/10/19 20:18:38 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	x;

	i = 0;
	if (!*needle)
		return ((char *)haystack);
	if (len > ft_strlen (haystack))
		len = ft_strlen (haystack);
	while (i < len)
	{
		x = i;
		j = 0;
		while (haystack[x] == needle[j] && (x < len))
		{
			x++;
			j++;
			if (needle[j] == '\0')
				return ((char *) &haystack[i]);
		}
		i++;
	}
	return (0);
}
