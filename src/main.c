/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:51:03 by ikozhina          #+#    #+#             */
/*   Updated: 2025/03/21 11:47:17 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((unsigned char)s1[i] != '\0' && (unsigned char)s2[i] != '\0')
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strrchr(const char *s, int c)
{
	char	*pnt_s;

	pnt_s = NULL;
	while (*s)
	{
		if ((unsigned char)*s == (unsigned char)c)
			pnt_s = (char *)s;
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (pnt_s);
}

void	check_extention(char *file_name)
{
	char *pnt_dot;
	int is_equal;

	pnt_dot = ft_strrchr(file_name, '.');
	if (pnt_dot == NULL)
	{
		printf("No extention\n");
		return ;
	}
	is_equal = ft_strcmp(pnt_dot, ".ber");
	if (!is_equal)
		printf("Equal\n");
	else
		printf("Not Equal\n");
}



int main(int argc, char **argv)
{
	if (argc == 2)
		printf("%s - ", argv[1]);
	check_argument(argv[1]);
}
