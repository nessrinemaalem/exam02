/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaalem <imaalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:09:50 by imaalem           #+#    #+#             */
/*   Updated: 2022/02/22 15:04:16 by imaalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>

int	main(int ac, char **av)
{
	int	i, j, tab[255];
	i = 0;
	if (ac == 3)
	{
		while (i < 255)
		{
			tab[i] = 0;
			i++;
		}
		i = 2;
		while (0 < i)
		{
			j = 0;
			while (av[i][j])
			{
				if (i == 2 && tab[(unsigned char)av[i][j]] == 0)
					tab[(unsigned char)av[i][j]] = 1;
				if (i == 1 && tab[(unsigned char)av[i][j]] == 1)
				{
					tab[(unsigned char)av[i][j]] = 2;
					write(1, &av[i][j], 1);
				}
				j++;
			}
			i--;
		}
	}
	write(1, "\n", 1);
	return (0);
}

// total 23 min, 
// total 12 min record à battre