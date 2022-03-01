/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_union.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaalem <imaalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 13:36:18 by imaalem           #+#    #+#             */
/*   Updated: 2022/03/01 15:16:46 by imaalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	main(int ac, char **av)
{
	if (ac == 3)
	{
		int		i = 0, j = 0;
		char	*tab[255]; // c'est bien un tab de char et pas d'int

		while (i < 255)
		{
			tab[i++] = 0;
		}
		i = 1;
		while (i < 3)
		{
			j = 0;
			while (av[i][j])
			{
				if (tab[(unsigned char)av[i][j]] == 0)
				{
					tab[(unsigned char)av[i][j]] = 1;
					write(1, &av[i][j], 1);
				}
				j++;
			}
			i++;
		}
	}
	write(1, "\n", 1);
	return (0);
}