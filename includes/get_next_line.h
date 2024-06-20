/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 19:57:37 by artclave          #+#    #+#             */
/*   Updated: 2023/10/25 04:58:27 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 7
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
char	*dealloc(t_list **head, char *buffer);
char	*extract_line(t_list *head, char *line);
int		find_nl_char(t_list *head);
int		read_buffer(t_list **head, int fd);
int		buffer_to_stash(char *buffer, t_list **head);
int		new_node(t_list **head, t_list *last, int size);
int		clean_stash(t_list **head);
int		save_leftove_chars(t_list **head, t_list *curr, int i);
t_list	*get_last_node(t_list *head);

#endif
