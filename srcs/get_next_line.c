/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1get_next_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 21:36:59 by artclave          #+#    #+#             */
/*   Updated: 2023/10/30 21:56:05 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*dealloc(t_list **head, char *buffer)
{
	t_list	*curr;
	t_list	*copy;

	curr = NULL;
	copy = NULL;
	if (buffer)
		free(buffer);
	if (*head == NULL)
		return (NULL);
	curr = *head;
	while (curr != NULL)
	{
		copy = curr->next;
		if (curr->content)
			free(curr->content);
		free(curr);
		curr = copy;
	}
	*head = NULL;
	return (NULL);
}

int	find_nl_char(t_list *head)
{
	int	i;
	int	len;

	if (head == NULL)
		return (0);
	i = 0;
	len = 0;
	while (head != NULL && head->content)
	{
		while (head->content[i] != '\0')
		{
			if (head->content[i] == '\n')
				return (len + 1);
			i++;
			len++;
		}
		i = 0;
		head = head->next;
	}
	return (len * -1);
}

t_list	*get_last_node(t_list *head)
{
	if (head == NULL)
		return (NULL);
	while (head->next != NULL)
		head = head->next;
	return (head);
}

int	new_node(t_list **head, t_list *last, int size)
{
	t_list	*new_node;
	int		i;

	i = 0;
	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (0);
	new_node->next = NULL;
	new_node->content = (char *)malloc(size + 1);
	if (!(new_node->content))
	{
		free(new_node);
		return (0);
	}
	while (i < size + 1)
		new_node->content[i++] = 0;
	if (*head == NULL)
		*head = new_node;
	else
		last->next = new_node;
	return (1);
}

char	*get_next_line(int fd)
{
	static t_list	*head = NULL;
	char			*line;

	line = NULL;
	if (fd < 0 || fd > 1023 || BUFFER_SIZE < 1 || read(fd, line, 0) == -1)
		return (dealloc(&head, NULL));
	if (find_nl_char(head) < 1 && !read_buffer(&head, fd))
		return (NULL);
	line = extract_line(head, line);
	if (line == NULL || !clean_stash(&head))
	{
		if (line)
			free(line);
		return (dealloc(&head, NULL));
	}
	return (line);
}
