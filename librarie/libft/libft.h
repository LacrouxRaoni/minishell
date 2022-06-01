/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 22:33:28 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/01 13:15:11 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

# define INT_MIN -2147483648
# define INT_MAX 2147483647

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 128
# endif

/**
	*checks for an alphabetic character; in the standard "C" locale;
**/
int		ft_isalpha(int c);
/**
 	*checks for a digit (0 through 9); 
**/
int		ft_isdigit(int c);
/**
 	*checks for an alphanumeric character;
**/
int		ft_isalnum(int c);
/**
 	*checks whether c is a 7-bit unsigned char value
	*that fits into the ASCII character set;
**/
int		ft_isascii(int c);
/**
 	*checks for any printable character including space;
**/
int		ft_isprint(int c);
/**
 	*The  strlen()  function  calculates  the length of the string pointed to by s,
	 *excluding the terminating null byte ('\0');
**/
size_t	ft_strlen(const char *s);
/**
 	*The memset() function fills the first n bytes 
	*of the memory area pointed to by s with the constant byte c;
**/
void	*ft_memset(void *s, int c, size_t n);
/**
 	*The  bzero()  function erases the data in the n bytes of the memory
	*starting at the location pointed to by s, 
    *by writing zeros (bytes containing '\0') to that area;
**/
void	ft_bzero(void *s, size_t n);
/**
 	*The  memcpy()  function  copies  n bytes from memory area 
	*src to memory area dest. The memory areas must not overlap.
	*Use memmove(3) if the memory areas do overlap;
**/
void	*ft_memcpy(void *dest, const void *src, size_t n);
/**
 	*The  memmove()  function copies n bytes from memory area src 
	*to memory area dest.  The memory areas may over‐lap: 
	*copying takes place as though the bytes in src are first copied 
	*into a temporary  array that  does  not overlap src or dest, 
	*and the bytes are then copied from the temporary array to dest;
**/
void	*ft_memmove(void *dest, const void *src, size_t n);
/**
 	*The strlcpy() function copies up to size - 1 characters 
	*from the NUL-terminated string src to dst, NUL-terminating the result;
**/
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
/**
 	*The strlcat() function appends the NUL-terminated string src 
	*to the end of dst. It will append at most size - strlen(dst) - 1 bytes, 
	*NUL-terminating the result;
**/
size_t	ft_strlcat(char *dst, const char *src, size_t size);
/**
 	*These functions convert lowercase letters to uppercase;
**/
int		ft_toupper(int c);
/**
 	*These functions convert uppercase letters to lowercase;
**/
int		ft_tolower(int c);
/**
 	*The strchr() function returns a pointer 
	*to the first occurrence of the character c in the string s;
**/
char	*ft_strchr(const char *s, int c);
/**
 	*The strrchr() function returns a pointer 
	*to the last occurrence of the character c in the string s;
**/
char	*ft_strrchr(const char *s, int c);
/**
 	*The strcmp() function compares the two strings s1 and s2. 
	*it only compares the first (at most) n bytes of s1 and s2;
**/
int		ft_strncmp(const char *str1, const char *str2, size_t n);
/**
 	*The  memchr() function scans the initial n bytes 
	*of the memory area pointed to by s for the first instance of
    *c.  Both c and the bytes of the memory area pointed to by s 
	*are interpreted as unsigned char;
**/
void	*ft_memchr(const void *s, int c, size_t n);
/**
 	*The  memcmp()  function compares the first n bytes 
	*(each interpreted as unsigned char) of the memory areas s1
    *and s2;
**/
int		ft_memcmp(const void *s1, const void *s2, size_t n);
/**
 	*The strnstr() function locates the	first occurrence of the	null-termi-
    *nated string little in the	string big, where not more than	len characters
    *are searched.
**/

int		ft_strcmp(const char *s1, const char *s2);

char	*ft_strnstr(const char *big, const char *little, size_t len);
/**
 	*The  atoi()  function  converts the initial portion of the string
	*pointed to by nptr to int;
**/
int		ft_atoi(const char *nptr);
/**
 	*The  calloc()  function  allocates  memory  for  an  array of 
	*nmemb elements of size bytes each and returns a
    *pointer to the allocated memory.  The memory is set to zero;
**/
void	*ft_calloc(size_t nmemb, size_t size);
/**
 	*The strdup() function returns a pointer to a new string 
	*which is a duplicate of the string s.  Memory for the
    *new string is obtained with malloc(3), and can be freed with free(3);
**/
char	*ft_strdup(const char *s);
/**
 	*Allocates (with malloc(3)) and returns a substring
	*from the string ’s’.
	*The substring begins at index ’start’ and is of
	*maximum size ’len’;
**/
char	*ft_substr(char const *s, unsigned int start, size_t len);
/**
 	*The itoa() function constructs a string representation of an integer;
**/
char	*ft_itoa(int n);
/**
 	*The strjoin() function combines all strings in the
    *argument list, and puts the result into the returned
    *string with dynamically allocated memory;
**/
char	*ft_strjoin(char const *s1, char const *s2);
/**
 	*The str_superjoin() function combines all strings from any size
    *received from an argument list, and puts the result into the returned
    *string with dynamically allocated memory;
**/
char	*ft_str_superjoin(char **src);
/**
 	*The strtrim removes all whitespace characters 
	*from the beginning and the end of a string.
	*As whitespace is counted everything for which isspace(3) returns true;
**/
char	*ft_strtrim(char const *s1, char const *set);
/**
 	*Applies the function ’f’ to each character of the
	*string ’s’ to create a new string (with malloc(3))
	*resulting from successive applications of ’f’.;
**/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
/**
 	*Applies the function f to each character of the
	*string passed as argument, and passing its index
	*as first argument. Each character is passed by
	*address to f to be modified if necessary;
**/
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
/**
 	*Outputs the character ’c’ to the given file
	*descriptor;
**/
void	ft_putchar_fd(char c, int fd);
/**
 	*Outputs the string ’s’ to the given file
	*descriptor;
**/
void	ft_putstr_fd(char *s, int fd);
/**
 	*Outputs the string ’s’ to the given file
	*descriptor, followed by a newline;
**/
void	ft_putendl_fd(char *s, int fd);
/**
 	*Outputs the integer ’n’ to the given file
	*descriptor;
**/
void	ft_putnbr_fd(int n, int fd);
/**
 	*Allocates (with malloc(3)) and returns an array
	*of strings obtained by splitting ’s’ using the
	*character ’c’ as a delimiter. The array must be
	*ended by a NULL pointer;
**/
char	**ft_split(char const *s, char c);

t_list	*ft_lstnew(void *content);	

void	ft_lstadd_front(t_list **lst, t_list *new);

int		ft_lstsize(t_list *lst);

t_list	*ft_lstlast(t_list *lst);

void	ft_lstadd_back(t_list **lst, t_list *new);

void	ft_lstdelone(t_list *lst, void (*del)(void *));

void	ft_lstclear(t_list **lst, void (*del)(void *));

void	ft_lstiter(t_list *lst, void (*f)(void *));

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

//all functions below related to get_next_line
int		free_reader(char **backup_buffer, int bytes_read);

void	arrange_backup(char **backup_buffer, int *i);

char	*extract_line(char **buffer);

int		read_file(int fd, char **buffer, char **buffer_backup);

char	*get_line(int fd, char **buff, char **backup_buff);

char	*get_next_line(int fd);

char	*gnl_join(char **s1, char **s2);
// end of get_next line

#endif