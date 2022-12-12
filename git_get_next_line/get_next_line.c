/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c	                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhabas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:55:50 by salhabas          #+#    #+#             */
/*   Updated: 2022/11/14 16:24:13 by salhabas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
/* Uses read to add characters to the stash */

void	read_and_stash(int fd, t_list **stash)
{
	char	*buf;
	int		i_read;

	i_read = 1;
	while (!find_newline(*stash) && i_read != 0)
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buf)
			return ;
		i_read = read(fd, buf, BUFFER_SIZE);
		if ((*stash == NULL && i_read == 0) || i_read == -1)
		{
			free(buf);
			return ;
		}
		buf[i_read] = '\0';
		move_to_stash(stash, buf, i_read);
		free(buf);
	}
}

/* move from buffer to end of stash */

void	move_to_stash(t_list **stash, char *buf, int i_read)
{
	int		i;
	t_list	*last;
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	new_node->next = NULL;
	new_node->content = malloc(sizeof(char) * (i_read + 1));
	if (new_node->content == NULL)
		return ;
	i = 0;
	while (buf[i] && i < i_read)
	{
		new_node->content[i] = buf[i];
		i++;
	}
	new_node->content[i] = '\0';
	if (!*stash)
	{
		*stash = new_node;
		return ;
	}
	last = ft_lstlast(*stash);
	last->next = new_node;
}

/* Extracts all characters from stash and stores them in line.
 * stop once you encounter the first \n  */

void	from_stash_to_line(t_list *stash, char **line)
{
	int	i;
	int	j;

	if (!stash)
		return ;
	make_line(line, stash);
	if (!*line)
		return ;
	j = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				(*line)[j++] = stash->content[i];
				break ;
			}
			(*line)[j++] = stash->content[i++];
		}
		stash = stash->next;
	}
	(*line)[j] = '\0';
}

/* This function clears the stash so only the characters that have
 * not been returned at the end of get_next_line remain in our static stash. */

void	clear_stash(t_list **stash)
{
	t_list	*last;
	t_list	*clean;
	int		i;
	int		j;

	clean = malloc(sizeof(t_list));
	if (!stash || !clean)
		return ;
	clean->next = NULL;
	last = ft_lstlast(*stash);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content && last->content[i] == '\n')
		i++;
	clean->content = malloc(sizeof(char) * (ft_strlen(last->content) - i) + 1);
	if (!clean->content)
		return ;
	j = 0;
	while (last->content[i])
		clean->content[j++] = last->content[i++];
	clean->content[j] = '\0';
	free_stash(*stash);
	*stash = clean;
}

char	*get_next_line(int fd)
{
	static t_list	*stash = NULL;
	char			*line;

	if (fd < 0 || fd > 1023 || BUFFER_SIZE < 1)
		return (0);
	line = NULL;
	read_and_stash(fd, &stash);
	if (!stash)
		return (NULL);
	from_stash_to_line(stash, &line);
	clear_stash(&stash);
	if (line[0] == '\0')
	{
		free_stash(stash);
		stash = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}
