/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonein <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 06:10:07 by gmonein           #+#    #+#             */
/*   Updated: 2017/04/26 17:32:20 by gmonein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>
# include "get_next_line.h"

# define BUF_SIZE 20

typedef struct s_list
{
	void	*content;
	size_t	content_size;
	void	*next;
	void	*past;
	void	*begin;
}				t_list;

void		ft_bzero(void *s, size_t n);
void		ft_lstadd(t_list **alst, t_list *ne);
void		ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void		ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void		ft_lstiter(t_list *lst, void (*f)(t_list *elem));
void		*ft_memalloc(size_t size);
void		*ft_memccpy(void *s1, const void *s2, int c, size_t n);
void		*ft_memchr(const void *ptr, int c, size_t n);
void		*ft_memcpy(void *s1, const void *s2, size_t n);
void		ft_memdel(void **ap);
void		*ft_memmove(void *dst, const void *src, size_t n);
void		*ft_memset(void *ptr, int value, size_t num);
void		ft_putchar(char c);
void		ft_putchar_fd(char c, int fd);
void		ft_putendl(char const *s);
void		ft_putendl_fd(char const *s, int fd);
void		ft_putnbr(int n);
void		ft_putnbr_fd(int n, int fd);
void		ft_putstr(char const *s);
void		ft_putstr_fd(char const *s, int fd);
void		ft_strclr(char *s);
void		ft_strdel(char **as);
void		ft_striter(char *s, void (*f)(char *));
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
long int	ft_atoi(char *str);
int			ft_double_sign(double num);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
int			ft_numtotwo(int num);
int			ft_pow(int nb, int pow);
int			ft_square(int num);
int			ft_strcmp(char *s1, char *s2);
int			ft_strequ(char const *s1, char const *s2);
int			ft_strncmp(char *s1, char *s2, size_t n);
int			ft_strnequ(char const *s1, char const *s2, size_t n);
int			ft_tolower(int c);
int			ft_toupper(int c);
char		*ft_itoa(int n);
char		*ft_read(char *file);
char		*ft_strcat(char *dst, const char *src);
char		*ft_strchr(const char *str, int c);
char		*ft_strcpy(char *dest, const char *src);
char		*ft_strdup(char *src);
char		*ft_strmap(char const *s, char (*f)(char));
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		*ft_strncat(char *dst, char *src, size_t n);
char		*ft_strncpy(char *dst, char *src, size_t n);
char		*ft_strnew(size_t size);
char		*ft_strnstr(char *s, const char *find, size_t n);
char		*ft_strrchr(const char *str, int c);
char		**ft_strsplit(char const *s, char c);
char		*ft_strstr(const char *s, const char *find);
char		*ft_strsub(char const *s, unsigned int start, size_t len);
char		*ft_strtrim(char const *s);
char		*ft_uitoa_base(unsigned int num, int base);
t_list		*ft_strsplit_lst(char const *s, char c);
t_list		*ft_lstnew(void const *content, size_t content_size);
t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void		ft_lstadd(t_list **alst, t_list *ne);
void		ft_lstdel(t_list **alst, void (*del)(void *, size_t));
size_t		ft_strlen(const char *str);
size_t		ft_strlcat(char *dst, char *src, size_t n);
char		*ft_strjoin(char const *s1, char const *s2);

#endif
