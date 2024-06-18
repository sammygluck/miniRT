/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:29:35 by wmarien           #+#    #+#             */
/*   Updated: 2024/04/11 16:29:56 by wmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct s_quaternion
{
	double	w;
	double	x;
	double	y;
	double	z;
}	t_quaternion;

//=== Vector Math ==//

double			vec_magnitude(t_vec3 vec);
double			dot_product(t_vec3 vec1, t_vec3 vec2);

t_vec3			normalize(t_vec3 vec);
t_vec3			scalar_multiplication(t_vec3 vec, double scalar);
t_vec3			sum_vectors(t_vec3 vec1, t_vec3 vec2);
t_vec3			diff_vectors(t_vec3 vec1, t_vec3 vec2);
t_vec3			cross_product(t_vec3 vec1, t_vec3 vec2);

//=== Quaternions ===//

t_quaternion	rotation_quaternion(t_vec3 from, t_vec3 to);
t_quaternion	normalize_quaternion(t_quaternion q);

t_vec3			vector_rotation(t_vec3 vec, t_quaternion rot);

#endif
