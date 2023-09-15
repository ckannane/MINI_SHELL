/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 20:28:52 by ckannane          #+#    #+#             */
/*   Updated: 2023/09/15 20:54:24 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_val(t_val *zone, char *content)
{
	char *name;
	char *value;
	name = save_before_equal(content);
	value = save_after_equal(content);
	while(zone)
	{
		if(ft_strcmp(zone->name,name) == 0 && zone->value != NULL && value == NULL)
			return (0);
		if(ft_strcmp(zone->name,name) == 0)
		{
			free(zone->value);
			zone->value = ft_strdup(value);
			return (0);
		}
		zone = zone->next;
	}
	return (1);
}

void check_match_env(t_val *env, t_val *exp)
{
    t_val *current;
	current = malloc(sizeof(t_val));
    while (env)
    {
        current = exp;
        while (current)
        {
            if (ft_strcmp(env->name, current->name) == 0 && \
			ft_strcmp(env->value, current->value) != 0)
            {
                free(env->value);
                env->value = ft_strdup(current->value);
            }
            current = current->next;
        }
        env = env->next;
    }
}


int	check_it_equal(char *arg)
{
	int i =0;
	while(arg[i])
	{
		if(arg[i] == '=' && arg[i + 1] != '\0')
			return (1);
		else if(arg[i] == '=' && arg[i + 1] == '\0')
			return (0);
		i++;
	}
	return (0);
}

void    ft_export(t_com *com,t_zid *zone)
{
	int i = 0;
	t_val *index_env;
	t_val *index_exp;
	t_val	*cuurent_env;
	t_val	*current_exp;

	cuurent_env = zone->env;
	current_exp = zone->exp;
	if (com->arg[0] == NULL)
	{
		while(current_exp)
		{
			if(current_exp->value == NULL)
			{
				printf("declare -x %s=\'\'\n",current_exp->name);
			}
			else
			printf("declare -x %s=\"%s\"\n",current_exp->name,current_exp->value);
			current_exp = current_exp->next;
		}
	}
	else
	{
		while(com->arg[i])
		{
			if(check_it_equal(com->arg[i]) == 1)
			{
				if(check_val(current_exp,com->arg[i])== 1)
				{
					index_exp = ft_val_re_new(com->arg[i]);
					ft_valadd_back(&current_exp,index_exp);
				}
				if(check_val(cuurent_env,com->arg[i])== 1)
				{
					index_env = ft_val_re_new(com->arg[i]);
					ft_valadd_back(&cuurent_env,index_env);
				}
			}
			else if (check_it_equal(com->arg[i]) == 0)
			{
				if(check_val(current_exp,com->arg[i])== 1)
				{
					index_exp = ft_val_re_new(com->arg[i]);
					ft_valadd_back(&current_exp,index_exp);
				}
			}
			i++;
		}
	}
}
