/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 00:22:21 by ckannane          #+#    #+#             */
/*   Updated: 2023/09/20 12:39:37 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

void	fill_them(t_slp_p	*val, char *word, char *input, char **words)
{
	if (val->i > val->word_start)
	{
		word = (char *)malloc(val->i - val->word_start + 1);
		ft_strncpy(word, input + val->word_start, val->i - val->word_start);
		word[val->i - val->word_start] = '\0';
		words[val->word_count++] = word;
		if (val->word_count == val->initial_capacity)
		{
			val->initial_capacity *= 2;
			words = (char **)realloc(words, val->initial_capacity * \
			sizeof(char *));
		}
	}
	val->word_start = val->i + 1;
}

char	**ft_splito(char *str)
{
	t_slp_p	*val;
	char	*word;
	char	**words;

	word = NULL;
	val = init_slp_p();
	words = (char **)malloc(val->initial_capacity * sizeof(char *));
	while (str[val->i] != '\0')
	{
		if (str[val->i] == '"')
			val->inside_quotes = !val->inside_quotes;
		else if (ft_isspace(str[val->i]) && !val->inside_quotes)
			fill_them(val, word, str, words);
		val->i++;
	}
	if (val->i > val->word_start)
	{
		word = (char *)malloc(val->i - val->word_start + 1);
		ft_strncpy(word, str + val->word_start, val->i - val->word_start);
		word[val->i - val->word_start] = '\0';
		words[val->word_count++] = word;
	}
	words[val->word_count] = NULL;
	free(val);
	return (words);
}
