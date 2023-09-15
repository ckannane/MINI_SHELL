/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 15:38:16 by ckannane          #+#    #+#             */
/*   Updated: 2022/10/16 19:25:30 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s && s[i] != '\0')
		ft_putchar_fd (s[i++], fd);
}
//#include<stdio.h>
//int main()
//{
//	int fd;
//	ft_putstr_fd("hello world",fd);
//	fd = open("text.txt", O_RDWR| O_CREAT);
//	close (fd);
//}