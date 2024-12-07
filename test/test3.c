/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herizrak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 14:33:10 by herizrak          #+#    #+#             */
/*   Updated: 2024/11/23 14:33:15 by herizrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define BUFFER_SIZE 100
#define LINE_SIZE 100
#define MAX_LINE 29

typedef struct s_ligne {
    long number;
    char *value;
} t_ligne;

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_str_copy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

long	ft_str_to_long(char *str)
{
	long	res;
	int		sign;

	res = 0;
	sign = 1;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	return (res * sign);
}

/*void	clean_str(char *str, long *cle, char *value)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] == ' ')
		i++;
	*cle = ft_str_to_long(&str[i]);
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	while (str[i] == ' ')
		i++;
	j = 0;
	while (str[i])
	{
		value[j] = str[i];
		j++;
		i++;
	}
	value[j] = '\0';
}
*/
void	clean_str(char *str, long *cle, char *value)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str == ' ')
		{
			str++;
			i = 0;
			while (str[i])
			{
				value[i] = str[i];
				i++;
			}
			value[i] = '\0';
			return ;
		}
		str++;
	}
}
int	read_numbers_into_dict(t_ligne *dict_centaine)
{
	int		fd;
	int		size;
	int		index;
	int		i;
	char	buffer[BUFFER_SIZE];
	char	line[LINE_SIZE];

	fd = open("numbers.dict", O_RDONLY);
	if (fd < 0)
		return (-1);
	index = 0;
	i = 0;
	while ((size = read(fd, &buffer[i], 1)) > 0)
	{
		if (buffer[i] == '\n' || i == BUFFER_SIZE - 1)
		{
			buffer[i] = '\0';
			clean_str(buffer, &dict_centaine[index].number, line);
			dict_centaine[index].value = malloc(ft_strlen(line) + 1);
			if (!dict_centaine[index].value)
			{
				close(fd);
				return (-1);
			}
			ft_str_copy(dict_centaine[index].value, line);
			index++;
			if (index == MAX_LINE)
				break ;
			i = 0;
		}
		else
			i++;
	}
	close(fd);
	return (index);
}
#include<stdio.h>
int	main(void)
{
	t_ligne	dict_centaine[MAX_LINE];
	int		count;
	int		i;

	count = read_numbers_into_dict(dict_centaine);
	if (count < 0)
	{
		write(2, "Error reading file\n", 19);
		return (1);
	}
	printf("%s ",dict_centaine[1].value);
	printf("%s",dict_centaine[15].value);
	i = 0;
	while (i < count)
	{
		free(dict_centaine[i].value);
		i++;
	}
	return (0);
}

