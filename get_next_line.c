/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaalem <imaalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 15:05:11 by imaalem           #+#    #+#             */
/*   Updated: 2022/02/22 22:11:05 by imaalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// heure de depart : 18:57

char	*ft_substr(char *str, int start, int len)
{
	char	*dest;
	int		i = 0;

	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (dest == NULL)
		return (NULL);
	while (i < len)
	{
		dest[i] = str[start];
		i++;
		start++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strchr(char *str, char c)
{
	int	i = 0;

	if (!str)
		return (NULL);
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c)
		return ("ok");
	return (NULL);
}

int	ft_strlen(char *str)
{
	int	i = 0;

	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (NULL);
	char	*dest;
	int		i = 0;
	int		j = 0;

	dest = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!dest)
		return (NULL);
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	while (s2[i])
	{
		dest[i + j] = s2[j];
		j++;
	}
	dest[i] = '\0';
	free (s1);
	return (dest);
}

char	*ft_tail(char *tail, int *n)
{
	char	*dest;

	dest = ft_substr(tail, *n + 1, ft_strlen(tail));
	free(tail);
	return (dest); 
}

char	*ft_line(char *tail, int *n)
{
	char	*line;
	int		i = 0;

	while (tail[i] && tail[i] != '\n')
		i++;
	*n = i;
	line = ft_substr(tail, 0, i + 1);
	return (line);
}

char	*ft_read(char *tail, int fd)
{
	char	buf[BUFFER_SIZE + 1];
	int		count;

	count = 1;
	printf("mais\n");
	while (count > 0 && !ft_strchr((char *)tail, '\n'))
	{
		count = read(fd, buf, BUFFER_SIZE);
		if (count < 0)
			return (NULL);
		buf[count] = '\0';
		printf("ok\n");
		if (!tail)
			tail = ft_substr(buf, 0, count);
		else
			tail = ft_strjoin(tail, buf);
	}
	return (tail);
}

char	*get_next_line(int fd)
{
	int			n;
	static char *tail = NULL;
	char		*line;

	n = 0;
	printf("test\n");
	if (fd < 0 || BUFFER_SIZE < 1 || (read(fd, 0, 0) < 0))
		return (NULL);
	tail = ft_read(tail, fd);
	printf("test1\n");
	if (!tail[0])
	{	
		free(tail);
		tail = NULL;
		return (NULL);
	}
	line = ft_line(tail, &n);
	printf("test2\n");
	tail = ft_tail(tail, &n);
	printf("test3\n");
	return (line);
}

int	main(int ac, char **av)
{
	char	*str;
	int		fd;

	fd = open("file.c", O_RDONLY);
	str = get_next_line(fd);
	while (str != NULL)
	{
		printf("%s\n", str);
		str = get_next_line(fd);
	}
	close(fd);
	return (0);
}