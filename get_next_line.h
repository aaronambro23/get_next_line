/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaambros <aaambros@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 16:20:17 by aaambros          #+#    #+#             */
/*   Updated: 2023/12/27 16:23:19 by aaambros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <stdlib.h>
# include <unistd.h>

//#include <stdlib.h> and <unistd.h> for *malloc(), free(), & read()*.

char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strlen(char *str);
char	*ft_strchr(const char *s, int i);
char	*ft_strdup(char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*get_next_line(int fd);

#endif
