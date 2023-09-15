/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:47:46 by ckannane          #+#    #+#             */
/*   Updated: 2022/10/19 19:14:39 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	size_t		j;
	char		*d;
	size_t		s_len;

	s_len = ft_strlen(s);
	if (s == NULL || s_len < start)
		return (ft_strdup(""));
	if (start + len < s_len)
		d = (char *)malloc((len + 1) * sizeof(char));
	else
		d = (char *)malloc((s_len - start + 1) * sizeof(char));
	if (d == NULL)
		return (NULL);
	i = start;
	j = 0;
	while (i < (start + len) && s[i])
		d[j++] = s[i++];
	d[j] = '\0';
	return (d);
}
