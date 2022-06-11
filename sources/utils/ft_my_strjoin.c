/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_my_strjoin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyago-ri <tyago-ri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 22:44:45 by tyago-ri          #+#    #+#             */
/*   Updated: 2022/06/06 22:44:45 by tyago-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.c"

char	*ft_my_strjoin(char *s1, char *s2)
{
	char	*s;
	int		count;
	int		count2;

	count = -1;
	count2 = 0;
	if (s1 == NULL && s2 != NULL)
		return (ft_strdup(s2));
	s = malloc ((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (s == NULL || s2 == NULL)
		return (NULL);
	while (s1[++count] != '\0')
		s[count] = s1[count];
	while (s2[count2] != '\0')
	{
		s[count] = s2[count2];
		count++;
		count2++;
	}
	s[count] = '\0';
	free (s1);
	return (s);
}
