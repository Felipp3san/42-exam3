/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 12:16:05 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/14 13:05:17 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Allowed functions: read, write, strlen, memmem, memmove, malloc, calloc,
realloc, free, printf, fprintf, stdout, stderr, perror
*/

#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

# define BUFFER_SIZE 1024

void	perform_replacements(char *buffer, char *filter_str)
{
	char	*substr;
	size_t	filter_len;
	size_t	buffer_len;
	size_t	i;

	filter_len = strlen(filter_str);
	buffer_len = strlen(buffer);
	substr = memmem(buffer, buffer_len, filter_str, filter_len);
	while (substr)
	{
		i = 0;
		while (substr[i] && i < filter_len)
		{
			substr[i] = '*';
			i++;
		}
	substr = memmem(buffer, buffer_len, filter_str, filter_len);
	}
}

int	filter(char	*buffer, char *filter_str)
{
	int	r;
	int size;

	size = 0;
	while ((r = read(STDIN_FILENO, buffer, BUFFER_SIZE)) > 0)
		size += r;
	if (r < 0)
	{
		perror("read");
		return(0);
	}
	buffer[size] = '\0';
	perform_replacements(buffer, filter_str);
	return (1);
}

int	main(int argc, char	**argv)
{
	char	buffer[1024];
	size_t	i;

	if (argc != 2)
		return (1);
	filter(buffer, argv[1]);

	i = 0;
	while (buffer[i])
		write(STDOUT_FILENO, &buffer[i++], 1);
	return (0);
}
