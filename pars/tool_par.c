/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_par.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:44:27 by ckannane          #+#    #+#             */
/*   Updated: 2023/09/18 14:32:47 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_slp_p	*init_slp_p(void)
{
	t_slp_p	*val;

	val = malloc(sizeof(t_slp_p));
	val->initialCapacity = 10;
	val->wordCount = 0;
	val->insideQuotes = 0;
	val->wordStart = 0;
	val->i = 0;
	return (val);
}
void	fill_it(t_slp_p	*val, char* word, char *input, char** words)
{
	if (val->i > val->wordStart)
	{
		word = (char*)malloc(val->i - val->wordStart + 1);
		ft_strncpy(word, input + val->wordStart, val->i - val->wordStart);
		word[val->i - val->wordStart] = '\0';
		words[val->wordCount++] = word;
		if (val->wordCount == val->initialCapacity)
		{
			val->initialCapacity *= 2;
			words = (char**)realloc(words, val->initialCapacity * sizeof(char*));
		}
	}
	val->wordStart = val->i + 1;
}


char	**splitstring(char *input)
{
	t_slp_p	*val;
	char*	word;
	char**	words;

	word = NULL;
	val = init_slp_p();
	words = (char**)malloc(val->initialCapacity * sizeof(char*));
	while (input[val->i] != '\0')
	{
		if (input[val->i] == '"')
			val->insideQuotes = !val->insideQuotes;
		else if (input[val->i] == '|' && !val->insideQuotes)
			fill_it(val, word, input, words);
		val->i++;
	}
	if (val->i > val->wordStart)
	{
		word = (char*)malloc(val->i - val->wordStart + 1);
		ft_strncpy(word, input + val->wordStart, val->i - val->wordStart);
		word[val->i - val->wordStart] = '\0';
		words[val->wordCount++] = word;
	}
	words[val->wordCount] = NULL;
	free(val);
	return (words);
}
void	read_com(t_com *com, t_zid *zone, char *line)
{
	char	*tmp;
	int		num_args;

	com->sp = ft_split(com->word, ' ');
	free(com->word);
	tmp = expansion(com, zone, line);
	tmp = return_without_quote(tmp);
	tmp = redirection_split(tmp);
	com->slp = ft_split(tmp, ' ');
	free(tmp);
	if (com->slp[0] == NULL)
		return ;
	com->commad = set_command(com->slp);
	if (com->commad == NULL)
		return ;
	num_args = set_arg_size(com);
	if (num_args == 0)
		return ;
	install_arg(com, num_args);
}
