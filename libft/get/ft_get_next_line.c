/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:52:48 by dehamad           #+#    #+#             */
/*   Updated: 2024/01/30 07:28:30 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get.h"

static char	*ft_appendline(char *arr_fd, char *buff)
{
	char	*join;

	if (!arr_fd && *buff)
	{
		arr_fd = ft_strdup(buff);
		if (!arr_fd)
			return (NULL);
		return (arr_fd);
	}
	if (arr_fd && *buff)
	{
		join = ft_strjoin(arr_fd, buff);
		ft_free(&arr_fd, 'p');
		if (!join)
			return (NULL);
		return (join);
	}
	return (NULL);
}

static char	*ft_ret(char **arr_fd)
{
	char	*ret;
	char	*temp;
	char	*newline_ptr;

	newline_ptr = ft_strchr(*arr_fd, '\n');
	if (newline_ptr)
	{
		*newline_ptr = '\0';
		ret = ft_strjoin(*arr_fd, "\n");
		if (*(newline_ptr + 1))
		{
			temp = ft_strdup(newline_ptr + 1);
			if (!temp)
				return (ft_free(&ret, 'p'), NULL);
			ft_free(arr_fd, 'p');
			*arr_fd = ft_strdup(temp);
			return (ft_free(&temp, 'p'), ret);
		}
		return (ft_free(arr_fd, 'p'), ret);
	}
	ret = ft_strdup(*arr_fd);
	return (ft_free(arr_fd, 'p'), ret);
}

static char	*ft_read(char **arr_fd, int fd, size_t size, bool *error)
{
	char	*buff;
	ssize_t	counter;

	counter = 1;
	buff = ft_calloc(size + 1, sizeof(*buff));
	if (!buff)
		return (NULL);
	while (counter > 0)
	{
		counter = read(fd, buff, size);
		if (counter > 0)
			*arr_fd = ft_appendline(*arr_fd, buff);
		else if (counter == -1)
			return (*error = true, ft_free(arr_fd, 'p'), free(buff), NULL);
		if (!counter || ft_strchr(buff, '\n'))
			break ;
		ft_bzero(buff, counter);
	}
	if (*arr_fd)
		return (free(buff), ft_ret(arr_fd));
	else
		return (free(buff), NULL);
}

t_gnl	ft_get_next_line(int fd)
{
	static char		*arr[OPEN_MAX];
	static t_gnl	ret;

	if (BUFFER_SIZE >= INT_MAX || BUFFER_SIZE <= 0 || fd < 0)
		return (ret.line = NULL, ret.error = true, ret);
	if (!arr[fd])
		arr[fd] = NULL;
	ret.line = ft_read(&arr[fd], fd, BUFFER_SIZE, &ret.error);
	return (ret);
}

/*
	t_gnl	ft_get_next_line(int fd)
	{
		if (BUFFER_SIZE >= INT_MAX || BUFFER_SIZE <= 0 || fd < 0)
			return ((t_gnl){.line = NULL, .error = true});
	}
	
	static char	*ft_read(char **arr_fd, int fd, size_t size, bool *err)
	{
		else if (counter == -1)
			return (*err = true, ft_free(arr_fd, 'p'), free(buff), NULL);
			1 - Assignment.
			2 - Functions || Return.
	}
*/
