/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaalem <imaalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 15:05:11 by imaalem           #+#    #+#             */
/*   Updated: 2022/02/23 16:12:37 by imaalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// heure de depart : 15:02

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//start: 15.05

int	ft_strlen(char *str)
{
	int 	i = 0;

	while (str[i])
		i++;
	return (i);
}

int		ft_strchr(char *str, char c)
{
	int	i;
	char c;

	c = (char)str; 
	if (!str)
		return NULL;
	while (str)
	{
		if (c != '\n')
			return (c);
	}
	return (NULL);
	
}

char *ft_substr(char *str, int start, int len)
{
	int 	i = 0;
	char 	*dest;

	if (!str)
		return NULL;
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (!dest)
		return NULL;
	while (i < len)
	{	
		dest[i++] = str[start++];
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char* s1, char *s2)
{
	int		i = 0;
	int		j = 0;
	char	*dest;

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
	while (s2)
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
	int		count = 1;
	char 	buf[BUFFER_SIZE + 1];

	while (count > 0 && !ft_strchr(tail, '\n'))
	{
		printf("read\n");
		count = read(fd, buf, BUFFER_SIZE);
		if (!tail)
			tail = ft_substr(buf, 0, count);
		else
			tail = ft_strjoin(tail, buf);
	}
	return (tail);
}

char	*ft_line(char *tail, int *n)
{
	char	*line;
	int		i = 0;

	while (tail[i] != '\n')
		i++;
	*n = i;
	line = ft_substr(tail, 0, i + 1);
	return (line);
}

char *ft_tail(char *str, int *n)
{
	char *tail;

	tail = ft_substr(str, *n + 1, ft_strlen(str));
	free(str);
	return (tail);
}

char	*get_next_line(int fd)
{
	static char	*tail;
	char		*line;
	int			n;

	if (BUFFER_SIZE < 1 || fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	tail = ft_read(tail, fd);
	printf("test\n");
	if (tail[0] = '\0')
	{
		free(tail);
		tail = NULL;
		return (NULL);
	}
	line = ft_line(tail, &n);
	printf("test1\n");
	tail = ft_tail(tail, &n);
	printf("test2\n");
	return (NULL);
}

int	main()
{
	int	fd;
	char *str;

	fd = open("file.c", O_RDONLY);
	printf("mais\n");
	str = get_next_line(fd);
	printf("ou et donc or ni car\n");
	while (str != NULL)
	{
		printf("%s", str);
		free(str);
		str = get_next_line(fd);
	}
	return (0);
}