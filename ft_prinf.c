/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prinf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaalem <imaalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 14:43:41 by imaalem           #+#    #+#             */
/*   Updated: 2022/03/01 15:14:39 by imaalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>

void	ft_putchar_len(char c, int *len)
{
	write(1, &c, 1);
	*len += 1;
}

void	ft_nbr(int n, int *len)
{
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		*len+= 11;
	}
	if (n < 0)
	{
		ft_putchar_len('-', len);
		ft_nbr(-n, len);
	}
	else
	{
		if (n > 9) // faite bien attention a cet ordre
			ft_nbr(n / 10, len);
		ft_putchar_len(n % 10 + '0', len);
	}
}

void	ft_hex(unsigned int x, int *len)
{
	char 	str[25];
	char 	*base = "0123456789abcdef";
	int		i = 0;

	if (x == 0)
	{
		ft_putchar_len('0', len);
		return;
	}
	while (x != 0)
	{
		str[i] = base[x % 16];
		x /= 16;
		i++;
	}
	while (i--)
		ft_putchar_len(str[i], len);
}

void	ft_str(char *str, int *len)
{
	int	i = 0;

	if (!str)
	{
		write(1, "(null)", 6);
		len += 6;
	}
	while (str[i])
	{
		ft_putchar_len(str[i], len);
		i++;
	}
}

void	check_flag(va_list *list, int flag, int *len)
{
	if (flag == '%')
		ft_putchar_len('%', len);
	else if (flag == 'x')
		ft_hex(va_arg(*list, unsigned int), len); // faite bien attention a caster en UNSIGNED int
	else if (flag == 's')
		ft_str(va_arg(*list, char *), len);
	else if (flag == 'd')
		ft_nbr(va_arg(*list, int), len);
}


int	ft_printf(char* str, ...)
{
	va_list		list;
	int			len = 0;
	int			i = 0;

	if (!str)
		return (0);
	va_start(list, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			check_flag(&list, str[i + 1], &len);
			i++;
		}
		else
			ft_putchar_len(str[i], &len);
		i++;
	}
	va_end(list);
	return (len);
}

// int	main()
// {
// 	char *str = "salut";
// 	int	n = 897946; 
// 	ft_printf("str is %%\n");
// 	printf("strr is %%\n");
// 	return (0);
// }