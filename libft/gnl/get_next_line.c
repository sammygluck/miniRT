/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <wmarien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:19:38 by wmarien           #+#    #+#             */
/*   Updated: 2024/06/04 12:41:03 by wmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"
#include "../libft.h"

char	*ft_read(int fd, char *og_str)
{
	int		ctr;
	char	*buff;

	buff = malloc((sizeof(char) * BUFFER_SIZE) + 1);
	if (!buff)
		return (NULL);
	ctr = 1;
	while (ctr > 0)
	{
		ctr = read(fd, buff, BUFFER_SIZE);
		if (ctr < 0)
			break ;
		buff[ctr] = '\0';
		og_str = ft_strjoin(og_str, buff);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	free(buff);
	if (ctr < 0 || (ctr == 0 && *og_str == '\0'))
	{
		free(og_str);
		return (NULL);
	}
	return (og_str);
}

char	*get_next_line(int fd, bool clear)
{
	static char	*og_str;
	char		*tmp;
	char		*line;
	int			ctr;

	if (clear)
		return (free(og_str), NULL);
	ctr = 0;
	if (fd < 0 || fd == 1 || fd == 2 || BUFFER_SIZE <= 0)
		return (0);
	og_str = ft_read(fd, og_str);
	if (!og_str)
	{
		free(og_str);
		return (NULL);
	}
	while (og_str[ctr] != '\n' && og_str[ctr])
		ctr++;
	line = ft_substr(og_str, 0, ctr);
	if (og_str[ctr] == '\n')
		line = ft_strjoin(line, "\n\0");
	tmp = ft_substr(og_str, ctr + 1, ft_strlen(og_str) - ctr);
	free(og_str);
	og_str = tmp;
	return (line);
}
