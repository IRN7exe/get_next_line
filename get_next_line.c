/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhanenk <ikhanenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 14:53:03 by ikhanenk          #+#    #+#             */
/*   Updated: 2024/09/23 15:45:17 by ikhanenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*free_all(char **stor, char **str)
{
	if (stor != NULL)
	{
		free(*stor);
		(*stor) = NULL;
	}
	if (str != NULL)
	{
		free(*str);
		(*str) = NULL;
	}
	return (NULL);
}

static char	*check_str(char **str, char **stor, ssize_t check)
{
	int		i;
	char	*dest;

	i = 0;
	if (check <= 0)
		return (NULL);
	else if (check > 0)
	{
		while ((*str)[i])
		{
			if ((*str)[i] == '\n')
			{
				dest = copy_str((*str), i + 1, 0);
				*stor = copy_str((*str), check - (i + 1), i + 1);
				free_all(NULL, str);
				return (dest);
			}
			i++;
		}
		*stor = copy_str((*str), i, 0);
	}
	return (NULL);
}

static char	*no_stor(char **stor, ssize_t *check, char **str, int fd)
{
	char	*dest;

	dest = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (*stor == NULL)
	{
		*check = check_read(fd, str);
		if (*check <= 0)
			return (NULL);
		dest = check_str(str, stor, *check);
		if (dest != NULL)
			return (dest);
	}
	if (*stor)
		dest = check_stor(stor, dest, *str);
	return (dest);
}

static char	*without_n(char **stor, char *dest, char **str)
{
	dest = copy_str((*stor), ft_strlen(*stor), 0);
	free_all(stor, str);
	return (dest);
}

char	*get_next_line(int fd)
{
	char			*str;
	char			*dest;
	static char		*stor;
	ssize_t			check;

	str = NULL;
	dest = no_stor(&stor, &check, &str, fd);
	while (!dest && stor)
	{
		dest = check_stor(&stor, dest, str);
		if (dest)
			return (dest);
		check = check_read(fd, &str);
		if (check < 0)
			return (free_all(&stor, &str));
		if (check > 0)
			stor = add_stor(str, check, stor);
		else if (check == 0 && stor == NULL)
			break ;
		else
			dest = without_n(&stor, dest, &str);
	}
	return (dest);
}

// int  main(int argc, char **argv)
// {
//  int     i;
//  int     fd;
//  char    *dest;

//  i = 0;
//  if (argc < 2)
//  {
//      printf("Error! Missing file!\n");
//      return (1);
//  }
//  fd = open(argv[1], O_RDONLY);
//  if (fd < 0)
//  {
//      printf("Error! Failed to read!\n");
//      return (1);
//  }
//  while (i < 12)
//  {
//      dest = get_next_line(fd);
//      if (!dest)
//      {
//          printf("BREAK i = |%d|", i);
//          break;
//      }
//      printf("RESULT = |%s|\n", dest);
//      i++;
//  }
//  free(dest);
//  close (fd);
//  return (0);
// }