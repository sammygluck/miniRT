/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <wmarien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 10:38:26 by wmarien           #+#    #+#             */
/*   Updated: 2024/06/04 12:41:53 by wmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# include <stdbool.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 8
# endif

char		*get_next_line(int fd, bool clear);

#endif
