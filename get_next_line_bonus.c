/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoldman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 14:50:30 by vgoldman          #+#    #+#             */
/*   Updated: 2019/10/25 17:59:08 by vgoldman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int		get_next_line(int fd, char **line)
{
	static char		*res[4096];
	char			buffer[BUFFER_SIZE];
	int				status;

	*line = NULL;
	status = 2;
	if (!res[fd])
		if (!(res[fd] = ft_calloc(1, sizeof(char))))
			return (-1);
	while (!breaks_checker(res[fd]) &&
		(status = read(fd, buffer, BUFFER_SIZE)) > 0)
		res[fd] = ft_strappend(res[fd], buffer, status);
	if (status < 0)
		return (-1);
	else if (status == 0)
	{
		*line = get_first_line(res[fd]);
		res[fd] = get_rest_buffer(res[fd]);
		free(res[fd]);
		res[fd] = NULL;
		return (0);
	}
	*line = get_first_line(res[fd]);
	res[fd] = get_rest_buffer(res[fd]);
	return (1);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;

	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	if (!(ptr = (char *)malloc(count * size)))
		return (NULL);
	if (ptr)
		ft_bzero(ptr, count * size);
	return (ptr);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char *ptr;

	ptr = b;
	while (len-- > 0)
		*ptr++ = c;
	return (b);
}
