/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljospin <ljospin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 16:52:20 by elmaleuv          #+#    #+#             */
/*   Updated: 2023/04/17 14:22:09 by ljospin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <fcntl.h>

# define BUFFER_SIZE 20

char	*ft_strjoin_gnl(char *s1, char *s2);
char	*get_line(char *storage);
char	*save_line(char *storage);
char	*line_reader(int fd, char *storage);
char	*get_next_line(int fd);
int		find_the_n(char *storage);
int		ft_strlen_gnl(const char *str);

#endif
