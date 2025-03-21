/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarrero <rmarrero@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 23:07:54 by rmarrero          #+#    #+#             */
/*   Updated: 2024/10/12 23:10:36 by rmarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	get_len(t_list *list)
{
	int	i;
	int	len;

	if (!list)
		return (0);
	len = 0;
	while (list)
	{
		i = 0;
		while (list->content[i])
		{
			if (list->content[i] == '\n')
				return (++len);
			++i;
			++len;
		}
		list = list->next;
	}
	return (len);
}

void	get_copy(t_list *list, char *line)
{
	int	i;
	int	j;

	if (!list)
		return ;
	j = 0;
	while (list)
	{
		i = 0;
		while (list->content[i])
		{
			if (list->content[i] == '\n')
			{
				line[j++] = '\n';
				line[j] = '\0';
				return ;
			}
			line[j++] = list->content[i++];
		}
		list = list->next;
	}
	line[j] = '\0';
}

int	find_new_line(t_list *list)
{
	int	i;

	if (!list)
		return (0);
	while (list)
	{
		i = 0;
		while (list->content[i] && i < BUFFER_SIZE)
		{
			if (list->content[i] == '\n')
				return (1);
			i++;
		}
		list = list->next;
	}
	return (0);
}

void	create_and_append(t_list **list, int fd)
{
	t_list	*new_node;
	t_list	*last_node;
	char	*buffer;
	int		bytes_read;

	while (!find_new_line(list[fd]))
	{
		buffer = malloc(BUFFER_SIZE + 1);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (!(buffer) || bytes_read <= 0)
			return (free(buffer), (void)0);
		buffer[bytes_read] = '\0';
		new_node = malloc(sizeof(t_list));
		if (!new_node)
			return ;
		new_node->content = buffer;
		new_node->next = NULL;
		if (!list[fd])
			list[fd] = new_node;
		else
		{
			last_node = ft_lstlast(list[fd]);
			last_node->next = new_node;
		}
	}
}
