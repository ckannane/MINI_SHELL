/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_par.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:44:27 by ckannane          #+#    #+#             */
/*   Updated: 2023/09/15 22:44:02 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **splitString(const char *input) {
    int i = 0;
    char **result = NULL;
    int token_start = 0;
    int inside_double_quotes = 0;
    int inside_single_quotes = 0;

    for (int j = 0; input[j] != '\0'; j++) {
        if (input[j] == '|' && !inside_double_quotes && !inside_single_quotes) {
            int token_len = j - token_start;
            if (token_len > 0) {
                result = realloc(result, (i + 1) * sizeof(char *));
                result[i] = malloc(token_len + 1);
                strncpy(result[i], &input[token_start], token_len);
                result[i][token_len] = '\0';
                i++;
            }
            token_start = j + 1;
        } else if (input[j] == '"') {
            inside_double_quotes = !inside_double_quotes;
        } else if (input[j] == '\'') {
            inside_single_quotes = !inside_single_quotes;
        }
    }

    int token_len = strlen(input) - token_start;
    if (token_len > 0) {
        result = realloc(result, (i + 1) * sizeof(char *));
        result[i] = malloc(token_len + 1);
        strncpy(result[i], &input[token_start], token_len);
        result[i][token_len] = '\0';
        i++;
    }

    result = realloc(result, (i + 1) * sizeof(char *));
    result[i] = NULL;
    return result;
}
//hello | world = [hello] [world] [NULL]
//hello | "world | hi" = [hello] ["world | hi"] [NULL]
//hello = [hello] [NULL]
//| NULL = [NULL]
