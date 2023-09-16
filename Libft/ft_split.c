/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 18:38:53 by ckannane          #+#    #+#             */
/*   Updated: 2023/09/16 19:43:43 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	pre_strlen(char const *s, char c, size_t i)
{
	size_t	j;

	j = 0;
	if (s[i] == 0)
		i--;
	while (s[i] && s[i] != c)
	{
		i--;
		j++;
	}
	return (j);
}

static size_t	start(size_t p, char const *s, char c, size_t l)
{
	size_t	i;
	size_t	x;

	i = 0;
	x = 0;
	if (s[0] != c && p == 1)
		return (0);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if ((s[i] != c && s[i + 1] == c) || (s[i] != c && s[i + 1] == '\0'))
			x++;
		if (x == p)
			break ;
		i++;
	}
	return (i - l + 1);
}

static size_t	lstr(size_t p, char const *s, char c)
{
	size_t	i;
	size_t	x;

	i = 0;
	x = 0;
	if (p == 1 && s[0] != c)
	{
		while (s[i] != c && s[i])
			i++;
		return (i);
	}
	while (s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c && s[i - 1] != c)
			x++;
		if (x == p)
		{
			i--;
			break ;
		}
		i++;
	}
	return (pre_strlen (s, c, i));
}

static size_t	nstr(char const *s, char c)
{
	size_t	j;
	size_t	i;
	int		hit;

	j = 0;
	i = 0;
	hit = 0;
	while (s[i])
	{
		if (s[i] != c && hit == 0)
		{
			hit = 1;
			j++;
		}
		else if (s[i] == c)
			hit = 0;
		i++;
	}
	return (j);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	i;
	size_t	sl;
	size_t	go;
	size_t	n;

	n = nstr (s, c);
	tab = (char **)malloc(sizeof(char *) * (n + 1));
	if (!tab)
		return (0);
	i = 0;
	while (i < n)
	{
		sl = lstr ((i + 1), s, c);
		go = start (i + 1, s, c, sl);
		tab[i] = ft_substr(s, go++, sl);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
