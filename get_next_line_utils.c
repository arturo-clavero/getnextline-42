/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 21:38:48 by artclave          #+#    #+#             */
/*   Updated: 2023/10/30 21:56:44 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	buffer_to_stash(char *buffer, t_list **head)
{
	t_list	*curr;
	int		i;

	curr = NULL;
	i = -1;
	if (!new_node(head, get_last_node(*head), BUFFER_SIZE))
		return (0);
	curr = get_last_node(*head);
	while (++i < BUFFER_SIZE + 1)
		curr->content[i] = buffer[i];
	return (1);
}

int	read_buffer(t_list **head, int fd)
{
	int		bytes;
	char	*buffer;

	bytes = 0;
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return ((int)dealloc(head, NULL));
	while (find_nl_char(*head) < 1)
	{
		bytes = (int)read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1 || (bytes == 0 && *head == NULL))
			return ((int)dealloc(head, buffer));
		if (bytes == 0)
			break ;
		buffer[bytes] = '\0';
		if (!buffer_to_stash(buffer, head))
			return ((int)dealloc(head, buffer));
	}
	free (buffer);
	return (1);
}

char	*extract_line(t_list *head, char *line)
{
	int	len;
	int	i;
	int	j;

	j = 0;
	len = find_nl_char(head);
	if (len < 0)
		len *= -1;
	line = (char *)malloc(len + 1);
	if (!line)
		return (NULL);
	while (head != NULL && j < len)
	{
		i = 0;
		while (head->content && head->content[i] != '\0' && j < len)
			line[j++] = head->content[i++];
		head = head->next;
	}
	line[j] = '\0';
	return (line);
}

int	save_leftover_chars(t_list **head, t_list *curr, int i)
{
	t_list	*new;
	int		s;

	s = BUFFER_SIZE;
	if (s < 1000)
		s = 1000;
	new = malloc(sizeof(t_list));
	if (!new)
		return (0);
	new->next = NULL;
	new->content = (char *)malloc(s + 1);
	if (!(new->content))
	{
		free(new);
		return (0);
	}
	s = 0;
	while (curr->content[i] != '\0')
		new->content[s++] = curr->content[i++];
	new->content[s] = '\0';
	dealloc(head, NULL);
	*head = new;
	return (1);
}

int	clean_stash(t_list **head)
{
	int		i;
	t_list	*curr;

	if (find_nl_char(*head) < 0)
		return ((int)dealloc(head, NULL) + 1);
	curr = *head;
	while (curr != NULL)
	{
		i = 0;
		while (curr->content[i] != '\0' && curr->content[i] != '\n')
			i++;
		if (curr->content[i] == '\n')
			break ;
		curr = curr->next;
	}
	if (curr->content[++i] == '\0')
		return ((int)dealloc(head, NULL) + 1);
	return (save_leftover_chars(head, curr, i));
}
