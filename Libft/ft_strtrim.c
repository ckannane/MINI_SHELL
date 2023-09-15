/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 23:10:21 by ckannane          #+#    #+#             */
/*   Updated: 2022/10/19 20:15:38 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*result(char const *s1, int start, int len)
{
	int		i;
	char	*s2;

	i = 0;
	s2 = (char *)malloc(sizeof(char) * len + 1);
	if (!s2)
	{
		free (s2);
		return (NULL);
	}
	while (len-- > 0)
		s2[i++] = s1[start++];
	s2[i] = '\0';
	return (s2);
}

static int	finish(char const *s1, char const *set, int len)
{
	int	i;
	int	j;
	int	x;

	i = 0;
	while (len-- > 0)
	{
		j = 0;
		x = 0;
		while (set[j] && x == 0)
		{
			if (set[j] == s1[len])
			{
				x = 1;
			}
			j++;
		}
		if (x == 0)
			return (len);
	}
	return (0);
}

static int	begin(char const *s1, char const *set)
{
	int	i;
	int	j;
	int	x;

	i = 0;
	while (s1[i])
	{
		j = 0;
		x = 0;
		while (set[j] && x == 0 && s1[i + 1] != '\0')
		{
			if (set[j] == s1[i])
			{
				x = 1;
			}
			j++;
		}
		if (x == 0)
			return (i);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		l;
	int		n;
	char	*newstr;

	if (set == 0)
		return ((char *)s1);
	if (s1 == 0)
		return (0);
	l = ft_strlen(s1);
	start = begin(s1, set);
	end = finish(s1, set, l);
	n = end - start + 1;
	if (n < 0)
		return (ft_strdup(""));
	newstr = result(s1, start, n);
	return (newstr);
}
