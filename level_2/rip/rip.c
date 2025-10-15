/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rip.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:08:44 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/15 18:10:56 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Allowed functions: puts, write
*/

#include <unistd.h>
#include <stdio.h>

size_t	ft_strlen(char *str)
{
	size_t	size;

	size = 0;
	while (str[size])
		size++;
	return (size);
}

void	count_invalid(char *str, size_t size, int *rem_open, int *rem_closed)
{
	size_t	i;

	*rem_open = 0;
	*rem_closed = 0;
	i = 0;
	while (i < size)
	{
		if (str[i] == '(')
			(*rem_open)++;
		else if (str[i] == ')')
		{
			if (*rem_open > 0)
				(*rem_open)--;
			else
				(*rem_closed)++;
		}
		i++;
	}
}

void	rip(char *str, int open, int rem_open, int rem_closed, size_t idx, size_t size)
{
	char	temp;

	if (idx == size)
	{
		if (open == 0 && rem_open == 0 && rem_closed == 0)
			puts(str);
		return ;
	}
	if (str[idx] == '(')
	{
		if (rem_open > 0)
		{
			temp = str[idx];
			str[idx] = ' ';
			rip(str, open, rem_open - 1, rem_closed, idx + 1, size);
			str[idx] = temp;
 		}
		rip(str,open + 1, rem_open, rem_closed, idx + 1, size);
	}
	else if (str[idx] == ')')
	{
		if (rem_closed > 0)
		{
			temp = str[idx];
			str[idx] = ' ';
			rip(str, open, rem_open, rem_closed - 1, idx + 1, size);
			str[idx] = temp;
		}
		if (open > 0)
			rip(str, open - 1, rem_open, rem_closed, idx + 1, size);
	}
}

int	main(int argc, char **argv)
{
	size_t	size;
	int		rem_open;
	int		rem_closed;

	if (argc != 2)
		return (1);
	size = ft_strlen(argv[1]);
	count_invalid(argv[1], size, &rem_open, &rem_closed);
	rip(argv[1], 0, rem_open, rem_closed, 0, size);
	return (0);
}
