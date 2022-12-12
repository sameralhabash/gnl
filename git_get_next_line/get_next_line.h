/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhabas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:31:24 by salhabas          #+#    #+#             */
/*   Updated: 2022/11/24 15:31:33 by salhabas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <stddef.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# if BUFFER_SIZE < 0
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}				t_list;

int		find_newline(t_list *stash);
int		ft_strlen(const char *str);
char	*get_next_line(int fd);
t_list	*ft_lstlast(t_list *stash);
void	read_and_stash(int fd, t_list **stash);
void	move_to_stash(t_list **stash, char *buf, int readed);
void	from_stash_to_line(t_list *stash, char **line);
void	make_line(char **line, t_list *stash);
void	free_stash(t_list *stash);

#endif
