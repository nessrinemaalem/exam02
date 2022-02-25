/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaalem <imaalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 15:05:11 by imaalem           #+#    #+#             */
/*   Updated: 2022/02/25 11:12:34 by imaalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

//meilleur temps 48min (avec quelques bavardages)

int	ft_strlen(char *str)
{
	int i = 0;

	while (str[i])
		i++;
	return (i);
}

char *ft_substr(char *str, int start, int len)
{
	char 	*dest;
	int		i = 0;

	if (!str)
		return (NULL);
	dest = (unsigned char *)malloc(sizeof(char) * (len + 1));
	while (i < len)
	{
		dest[i] = str[start++];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char *ft_strchr(char *str, int c)
{
	char	*dup = (unsigned char *)str;

	if (!str)
		return (NULL);
	while (*dup)
	{
		if (*dup == (unsigned char)c)
			return (dup);
		dup++;
	}
	return (NULL);
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
	int		i = 0;
	char 	*line;

	while (tail[i] && tail[i] != '\n')
		i++;
	*n = i;
	line = ft_substr(tail, 0, *n + 1);
	return (line);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char 	*dest;
	int		i = 0, j = 0;

	if (!s1 || !s2 )
		return (NULL);
	dest = (unsigned char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!dest)
		return (NULL);
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

char	*ft_read(char *tail, int fd)
{
	char	buf[BUFFER_SIZE + 1];
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

char	*get_next_line(int fd)
{
	static char *tail;
	char 		*line;
	int 		n = 0;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
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
	return(line);	
}

int	main()
{
	char	*str;
	int		fd;

	fd = open("file.c", O_RDONLY);
	str = get_next_line(fd);
	while (str != NULL)
	{
		printf("%s", str);
		str = get_next_line(fd);
	}
	return (0);
}