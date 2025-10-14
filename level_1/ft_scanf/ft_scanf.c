/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scanf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 19:38:20 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/13 22:58:51 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f)
{
	int	c;

	while ((c = fgetc(f)) != EOF && isspace(c))
		;
	if (c == EOF)
		return (-1);
	if (ungetc(c, f) == EOF)
		return (-1);
	return (0);
}

int match_char(FILE *f, char c)
{
	int	ch;

	ch = fgetc(f);
	if (ch == EOF)
		return (-1);
	if (ch == c)
	{
		ungetc(c, f);
		return (1);
	}
	return (0);
}

int scan_char(FILE *f, va_list ap)
{
	int		c;
	char	*ptr;

	ptr = va_arg(ap, char *);
	c = fgetc(f);
	if (c == EOF)
		return (-1);
	*ptr = (char) c;
	return (1);
}

int scan_int(FILE *f, va_list ap)
{
	int	*ptr;
	int	c;
	int	found;

	found = 0;
	ptr = va_arg(ap, int *);
	*ptr = 0;
	while ((c = fgetc(f)) != EOF && isdigit(c))
	{
		*ptr = ((*ptr) * 10) + (c - '0');
		found = 1;
	}
	if (c != EOF)
		ungetc(c, f);
	if (!found)
		return (0);
	if (c == EOF && !found)
		return (-1);
	return (1);
}

int scan_string(FILE *f, va_list ap)
{
	char	*ptr;
	int	c;
	int	found;

	found = 0;
	ptr = va_arg(ap, char *);
	*ptr = 0;
	while ((c = fgetc(f)) != EOF && !isspace(c))
	{
		*ptr = c;
		ptr++;
		found = 1;
	}
	if (c != EOF)
		ungetc(c, f);
	if (!found)
		return (0);
	if (c == EOF && !found)
		return (-1);
	return (1);
}


int	match_conv(FILE *f, const char **format, va_list ap)
{
	switch (**format)
	{
		case 'c':
			return scan_char(f, ap);
		case 'd':
			match_space(f);
			return scan_int(f, ap);
		case 's':
			match_space(f);
			return scan_string(f, ap);
		case EOF:
			return -1;
		default:
			return -1;
	}
}

int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int nconv = 0;

	int c = fgetc(f);
	if (c == EOF)
		return EOF;
	ungetc(c, f);

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (match_conv(f, &format, ap) != 1)
				break;
			else
				nconv++;
		}
		else if (isspace(*format))
		{
			if (match_space(f) == -1)
				break;
		}
		else if (match_char(f, *format) != 1)
			break;
		format++;
	}
	
	if (ferror(f))
		return EOF;
	return nconv;
}


int ft_scanf(const char *format, ...)
{
	va_list	ap;

	va_start(ap, format);

	int ret = ft_vfscanf(stdin, format, ap);

	va_end(ap);
	return ret;
}

int	main(void)
{
	int		nbr, nbr2, nbr3;
	char	ch, ch2, ch3;
	char	str[50], str2[50];

	printf("Enter a str: ");
	ft_scanf("A%s", str);
	printf("The str is: %s \n", str);

	printf("Enter str and a nbr: ");
	ft_scanf("%s %d", str, &nbr);
	printf("The str is: %s and the nbr is: %d\n", str, nbr);

	printf("Enter nbr and ch: ");
	ft_scanf("%d %c", &nbr, &ch);
	printf("The nbr is: %d and the char: %c\n", nbr, ch);

	printf("Enter nbr: ");
	ft_scanf("%d", &nbr);
	printf("The nbr is: %d\n", nbr);

	printf("Enter chars: ");
	ft_scanf("%c %c %c", &ch, &ch2, &ch3);
	printf("The chars are: %c %c %c\n", ch, ch2, ch3);

	printf("Enter nbrs: ");
	ft_scanf("%d %d %d", &ch, &ch2, &ch3);
	printf("The nbrs are: %d %d %d\n", nbr, nbr2, nbr3);
	return (0);
}
