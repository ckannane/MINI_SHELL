/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_par.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:44:27 by ckannane          #+#    #+#             */
/*   Updated: 2023/09/15 00:00:23 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int are_we_insid(char *str, int i) {
    return (str[i] == '"' && (i == 0 || str[i - 1] != '\\')) ? 1 : 0;
}

char *allocate_and_copy( char *str, int start, int end)
{
    int token_length = end - start;
    char *token = (char *)malloc(sizeof(char) * (token_length + 1));
    if (!token) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    strncpy(token, &str[start], token_length);
    token[token_length] = '\0';
    return token;
}

char **split_with_quotes(char *str, char c)
{
	char **tokens;
	int slp_num = 0;
	int i = 0;
	int slp_go = 0;
	int insid = 0;
	int len = strlen(str);

	tokens = (char **)malloc(sizeof(char *) * len);
	while (i <= len) {
	    if (are_we_insid(str, i)) {
	        insid = !insid;
	    } else if ((str[i] == c && !insid) || str[i] == '\0') {
	        tokens[slp_num] = allocate_and_copy(str, slp_go, i);
	        slp_num++;
	        slp_go = i + 1;
	    }
	    i++;
	}
return tokens;
}