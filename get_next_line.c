/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaalem <imaalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 15:05:11 by imaalem           #+#    #+#             */
/*   Updated: 2022/02/24 19:39:38 by imaalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// heure de depart : 15:02 fail -> seg auly pour des erreurs betes prnde le temps de bien faire et de relire au fur et a mesure

// depart 3: 16:13

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int	ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(char *str, int c)
{
	char *dup = (unsigned char *)str;

	if (!str)
		return NULL;
	while (*dup)
	{
		if (*dup == (unsigned char)c)
			return (dup);
		dup++;
	}
	return (NULL);
}

char *ft_strjoin(char *s1, char *s2)
{
	char	*dest;
	int		i = 0, j = 0;

	if (!s1 || !s2)
		return NULL;
	dest = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!dest)
		return NULL;
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	} 
	while (s2[j])
	{
		dest[i + j] = s2[j];
		j++;
	}
	dest[i + j] = '\0';
	free(s1);
	return (dest);
}

char	*ft_substr(char *str, int start, int len)
{
	char	*dest;
	int		i = 0;

	dest = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!dest)
		return NULL;
	while (i < len)
		dest[i++] = str[start++];
	dest[i] = '\0';
	return (dest);
}

char	*ft_read(char *tail, int fd)
{
	char 	buf[BUFFER_SIZE + 1];
	int		count_read = 1;

	while (count_read > 0 && !ft_strchr(tail, '\n'))
	{
		count_read = read(fd, buf, BUFFER_SIZE);
		if (count_read < 0)
			return (NULL);
		buf[count_read] = '\0';
		if (!tail)
			tail = ft_substr(buf, 0, count_read);
		else
			tail = ft_strjoin(tail, buf);
	}
	return (tail);
}

char	*ft_tail(char *tail, int *n)
{
	char *new_tail;

	new_tail = ft_substr(tail, *n + 1, ft_strlen(tail));
	free(tail);
	return (new_tail);
}

char	*ft_line(char *tail, int *n)
{
	char	*line;
	int		i;

	while (tail[i] != '\n' && tail[i])
		i++;
	line = ft_substr(tail, 0, i + 1);
	*n = i;
	return (line);
}

char	*get_next_line(int fd)
{
	static char *tail;
	char		*line;
	int 		n = 0;

	if (BUFFER_SIZE < 1 || fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	tail = ft_read(tail, fd);
	if (!tail[0])
	{
		free(tail);
		tail = NULL;
		return NULL;
	}
	line = ft_line(tail, &n);
	tail = ft_tail(tail, &n);
	return (line);
}

int	main()
{
	int		fd;
	char	*str;

	fd = open("file.c", O_RDONLY);
	str = get_next_line(fd);
	while (str != NULL)
	{
		printf("%s", str);
		str = get_next_line(fd);
	}
	return (0);
}