/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhanenk <ikhanenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 14:53:23 by ikhanenk          #+#    #+#             */
/*   Updated: 2024/09/21 19:10:10 by ikhanenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <malloc.h>
# include <sys/stat.h>
# include <sys/types.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	1
# endif

char	*get_next_line(int fd);
char	*add_stor(char *str, int len, char *stor);
char	*copy_str(char *str, int len, int start);
char	*check_stor(char **stor, char *dest, char *str);
void	*free_all(char **stor, char **str);
ssize_t	check_read(int fd, char **str);
size_t	ft_strlen(char *s);

#endif