/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_queens.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:23:04 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/14 16:09:04 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
Allowed functions : atoi, fprintf, write, calloc, malloc, free,
realloc, stdout, stderr
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int		has_queen_diagonal(int *board, int col, int row)
{
	int	i;

	i = 0;
	while (i < col)
	{
		// Diagonal up
		if (board[i] == row - col + i)
			return (1);
		// Diagonal down
		if (board[i] == row + col - i)
			return (1);
		i++;
	}
	return (0);
}

int		has_queen_horizontal(int *board, int col, int row)
{
	int	i;

	i = 0;
	while (i < col)
	{
		if (board[i] == row)
			return (1);
		i++;
	}
	return (0);
}

void	print_combinations(int *board, int total_cols)
{
	int		i;

	i = 0;
	while (i < total_cols)
	{
		if (i != total_cols - 1)
			fprintf(stdout, "%d ", board[i]);
		else
			fprintf(stdout, "%d\n", board[i]);
		i++;
	}
}

void	n_queens(int total_cols, int *board, int col)
{
	int	row;

	if (col == total_cols)
	{
		print_combinations(board, total_cols);
		return ;
	}
	row = 0;
	while (row < total_cols)
	{
		if (!has_queen_horizontal(board, col, row)
			&& !has_queen_diagonal(board, col, row))
		{
			board[col] = row;
			n_queens(total_cols, board, col + 1);
		}
		row++;
	}
}

int	main(int argc, char	**argv)
{
	int	*board;
	int	cols;

	if (argc != 2 || !*argv[1])
		return (1);
	cols = atoi(argv[1]);
	if (cols <= 0)
		return (1);
	board = calloc(cols, sizeof(int));
	if(!board)
		return (1);
	n_queens(cols, board, 0);
	free(board);
	return (0);
}
