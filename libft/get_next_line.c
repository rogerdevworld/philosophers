/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarrero <rmarrero@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 21:11:16 by rmarrero          #+#    #+#             */
/*   Updated: 2024/10/28 20:58:15 by rmarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*get_next_line(int fd)
{
	static t_list	*list[4096];
	char			*line;

	line = NULL;
	if (BUFFER_SIZE < 0 || fd < 0)
		return (NULL);
	create_and_append(list, fd);
	line = malloc(get_len(list[fd]) + 1);
	if (!(list[fd]) || !(line))
		return (free(line), NULL);
	get_copy(list[fd], line);
	get_clear_remaining_data(&list[fd]);
	return (line);
}

void	get_free_list(t_list **list, t_list *replace, char *buffer)
{
	t_list	*tmp;

	if (NULL == *list)
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->content);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
	if (replace->content[0])
		*list = replace;
	else
	{
		free(buffer);
		free(replace);
	}
}

void	get_clear_remaining_data(t_list **list)
{
	char	*buffer;
	t_list	*last;
	t_list	*replace;
	int		i;
	int		j;

	i = 0;
	j = 0;
	buffer = malloc(BUFFER_SIZE + 1);
	replace = malloc(sizeof(t_list));
	if (!(buffer) || !(replace))
		return ;
	last = ft_lstlast(*list);
	while (last->content[i] && last->content[i] != '\n')
		++i;
	while (last->content[i] && last->content[++i])
		buffer[j++] = last->content[i];
	buffer[j] = '\0';
	replace->content = buffer;
	replace->next = NULL;
	get_free_list(list, replace, buffer);
}
//comand > 
//gcc -o get_next_line main.c get_next_line.c get_next_line_utils.c -I./includes
