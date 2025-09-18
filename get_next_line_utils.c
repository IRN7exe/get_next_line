/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhanenk <ikhanenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 14:53:13 by ikhanenk          #+#    #+#             */
/*   Updated: 2024/09/21 19:11:26 by ikhanenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	i;
	size_t	counter;

	i = 0;
	counter = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		counter += 1;
		i++;
	}
	return (counter);
}

char	*copy_str(char *str, int len, int start)
{
	int		i;
	char	*temp;

	if (!len)
		return (NULL);
	i = 0;
	temp = malloc(len + 1);
	if (!temp)
		return (NULL);
	while (i < len)
		temp[i++] = str[start++];
	temp[i] = '\0';
	return (temp);
}

char	*add_stor(char *str, int len, char *stor)
{
	int		i;
	int		k;
	char	*new_stor;

	i = 0;
	k = 0;
	new_stor = malloc(len + ft_strlen(stor) + 1);
	if (!new_stor)
		return (NULL);
	while (stor && stor[i])
		new_stor[k++] = stor[i++];
	i = 0;
	while (str[i])
		new_stor[k++] = str[i++];
	new_stor[k] = '\0';
	if (stor)
		free(stor);
	if (*str && new_stor[0])
		return (new_stor);
	else
	{
		free(new_stor);
		return (NULL);
	}
}

char	*check_stor(char **stor, char *dest, char *str)
{
	int	i;
	int	k;
	int	len;

	i = 0;
	k = 0;
	len = 0;
	while ((*stor)[i])
	{
		if ((*stor)[i] == '\n')
		{
			dest = copy_str((*stor), ++i, 0);
			len = ft_strlen((*stor) + i);
			while (k < len)
				(*stor)[k++] = (*stor)[i++];
			(*stor)[k] = '\0';
			if (!(*stor)[0])
				free_all(stor, NULL);
			free_all(NULL, &str);
			return (dest);
		}
		i++;
	}
	return (NULL);
}

ssize_t	check_read(int fd, char **str)
{
	ssize_t	check;

	if (!*str)
		*str = malloc(BUFFER_SIZE + 1);
	if (!(*str))
		return (0);
	check = read(fd, *str, BUFFER_SIZE);
	if (check <= 0)
	{
		free_all(NULL, str);
		return (check);
	}
	(*str)[check] = '\0';
	return (check);
}
