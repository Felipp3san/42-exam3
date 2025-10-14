/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permutations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 19:02:04 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/14 21:25:50 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Allowed functions: puts, malloc, calloc, realloc, free, write
*/

#include <stdlib.h>
#include <stdio.h>

void	swap(char *a, char *b)
{
	char	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

size_t	ft_strlen(char *str)
{
	size_t	size;

	size = 0;
	while (str[size])
		size++;
	return (size);
}

void	permute(char *str, size_t start, size_t end)
{
	size_t	i;

	if (start == end)
	{
		puts(str);
		return ;
	}
	i = start;
	while (i <= end)
	{
		swap(&str[start], &str[i]);
		permute(str, start + 1, end);
		swap(&str[start], &str[i]);
		i++;
	}
}

void	sort(char *str)
{
	size_t	i;
	size_t	j;
	
	i = 0;
	while (str[i])
	{
		j = i;
		while (str[j])
		{
			if (str[j] < str[i])
				swap(&str[i], &str[j]);
			j++;
		}
		i++;
	}
}

int	main(int argc, char	**argv)
{
	size_t	size;

	if (argc != 2 || !*argv[1])
		return (1);
	size = ft_strlen(argv[1]);
	sort(argv[1]);
	printf("%s\n", argv[1]);
	permute(argv[1], 0, size - 1);
	return (0);
}
