/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:47:24 by ckannane          #+#    #+#             */
/*   Updated: 2023/08/30 15:47:27 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#define MAX_PATH_LENGTH 1024

void custom_ls_for_directory(const char *path) {
    struct dirent *entry;
    DIR *dir = opendir(path);

    if (dir == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    closedir(dir);
}

void custom_ls(char **args) {
    // Check if args is NULL (no arguments provided)
    if (args == NULL) {
        char cwd[MAX_PATH_LENGTH];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            custom_ls_for_directory(cwd);
        } else {
            perror("getcwd");
            return;
        }
    } else {
        // Check if the first argument is NULL (only 'ls' command provided)
        if (args[0] == NULL) {
            char cwd[MAX_PATH_LENGTH];
            if (getcwd(cwd, sizeof(cwd)) != NULL) {
                custom_ls_for_directory(cwd);
            } else {
                perror("getcwd");
                return;
            }
        } else {
            custom_ls_for_directory(args[0]);
        }
    }
}