/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:03:32 by lscarcel          #+#    #+#             */
/*   Updated: 2024/07/23 11:27:43 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
size_t		ft_strlen(const char *s);
void		*ft_memset(void *b, int c, size_t len);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
int			ft_toupper(int c);
int			ft_tolower(int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
int			ft_atoi(const char *str);
long int	ft_atol(char *str);
void		check_limits(long int result);
char		*ft_itoa(int n);
void		*ft_memmove(void *dst, const void *src, size_t len);
char		*ft_strdup(char *s1);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlen(const char *s);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
void		*ft_calloc(size_t count, size_t size);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char *s1, char const *s2);
char		*ft_strjoin_no_free(char *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
void		ft_putnbr_fd(int n, int fd);
char		**ft_split(char const *s, char c);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
int			ft_strcmp(const char *s1, const char *s2);

// GET_NEXT_LINE

//Buffer size
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

//Function Prototypes
char		*get_next_line(int fd);
char		*ft_read_line(int fd, char *stash);
char		*ft_get_line(char *stash);
char		*ft_remove_line(char *stash);

//Utility functions
char		*ft_strjoin_gnl(char *str1, char *str2);
void		free_buffers_gnl(char *buffer1, char *buffer2);

#endif
