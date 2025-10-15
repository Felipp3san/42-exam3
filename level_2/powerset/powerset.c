/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   powerset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:05:17 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/15 14:17:48 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Allowed functions: atoi, printf, fprintf, malloc, calloc, realloc, free, stdout,
write
*/

#include <stdlib.h>
#include <stdio.h>

int	sum_set(char **argv, int *include, size_t size)
{
	int		sum;
	size_t	i;

	i = 0;
	sum = 0;
	while (i < size)
	{
		if (include[i])
			sum += atoi(argv[i]);
		i++;
	}
	return (sum);
}

void	print_set(char **argv, int *include, size_t size)
{
	size_t	i;
	int		first;

	i = 0;
	first = 1;
	while (i < size)
	{
		if (include[i])
		{
			if (i > 0 && !first)
				printf(" ");
			printf("%s", argv[i]);
			first = 0;
		}
		i++;
	}
	printf("\n");
}

void	powerset(char **argv, int target, int *include, size_t idx, size_t size)
{
	if (idx == size)
	{
		if (sum_set(argv, include, size) == target)
			print_set(argv, include, size);
		return ;
	}
	include[idx] = 0;
	powerset(argv, target, include, idx + 1, size);
	include[idx] = 1;
	powerset(argv, target, include, idx + 1, size);
}

int	main(int argc, char **argv)
{
	size_t	size;
	int		*include;
	int		target;

	if (argc <= 1)
		return (1);
	target = atoi(argv[1]);
	size = argc - 2;
	include = (int *) calloc(size, sizeof(int));
	if (!include)
		return (1);
	powerset(&argv[2], target, include, 0, size);
	free(include);
	return (0);
}
