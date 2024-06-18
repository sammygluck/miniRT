/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <wmarien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:12:13 by wmarien           #+#    #+#             */
/*   Updated: 2024/04/16 16:03:52 by wmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>
# include <math.h>
# include <float.h>
# include "./libft/libft.h"
# include "./libft/get_next_line.h"
# include "./mlx_linux/mlx.h"

# include "vector.h"

# define HEIGHT 450
# define WIDTH 800

//=== MLX Macros ==//

# define KEYPRESS 2
# define KEYRELEASE 3
# define BUTTONPRESS 4
# define BUTTONRELEASE 5
# define MOTIONNOTIFY 6
# define ENTERNOTIFY 7
# define LEAVENOTIFY 8
# define FOCUSIN 9
# define FOCUSOUT 10
# define KEYMAPNOTIFY 11
# define EXPOSE 12
# define GRAPHICSEXPOSE 13
# define NOEXPOSE 14
# define VISIBILITYNOTIFY 15
# define CREATENOTIFY 16
# define DESTROYNOTIFY 17
# define UNMAPNOTIFY 18
# define MAPNOTIFY 19
# define MAPREQUEST 20
# define REPARENTNOTIFY 21
# define CONFIGURENOTIFY 22
# define CONFIGUREREQUEST 23
# define GRAVITYNOTIFY 24

//=== Keycodes ===//

# define ESC_KEY 65307

//=== Data Structs ===//

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}	t_ray;

typedef enum e_objtype
{
	SPHERE,
	PLANE,
	CYLINDER
}	t_objtype;

typedef struct s_object
{
	t_objtype		type;
	t_vec3			center;
	t_vec3			normal;
	float			r;
	float			h;
	unsigned int	color;
}	t_object;

typedef struct s_camera
{
	t_vec3	origin;
	t_vec3	normal;
	int		fov;
}	t_camera;

typedef struct s_light
{
	t_vec3			origin;
	float			intensity;
	unsigned int	color;
}	t_light;

typedef struct s_ambient
{
	float			intensity;
	unsigned int	color;
}	t_ambient;

typedef struct s_world
{
	t_list		*objects;
	t_camera	cam;
	t_light		light;
	t_ambient	amb;
	int			parsed[3];
	int			obj_parsed;
}	t_world;

typedef struct s_viewport
{
	double	width;
	double	height;
	t_vec3	tlp;
	t_vec3	right;
	t_vec3	down;
	double	x_step;
	double	y_step;
}	t_viewport;

typedef struct s_mlx
{
	void	*image;
	char	*buff;
	int		size_line;
	void	*window;
	void	*mlx;
	int		bpp;
	int		endian;
}	t_mlx;

typedef struct s_mrt
{
	t_world		world;
	t_mlx		mlx;
	t_viewport	vp;
}	t_mrt;

typedef struct s_closest
{
	double		t;
	t_object	*object;
}	t_closest;

int				mrt_exit(t_mrt *mrt);

//=== Error ===//

int				err_msg(char *str);
int				perr_msg(char *type, char *str);

//=== Parser ===//

int				parser(t_world *world, char *line);

int				parse_ambient(t_world *world, char *line);
int				parse_camera(t_world *world, char *line);
int				parse_light(t_world *world, char *line);
int				parse_sphere(t_world *world, char *line);
int				parse_plane(t_world *world, char *line);
int				parse_cylinder(t_world *world, char *line);

char			*skip_spaces(char *line);
int				parse_rgb(unsigned int *color, char **line);
int				parse_cords(t_vec3 *cords, char **line);
int				is_normalized(t_vec3 vec);
int				parse_double(float *val, char **line);

//=== Viewport ===//

void			init_viewport(t_mrt *mrt);
t_vec3			pix_to_cord(t_viewport vp, int x, int y);

//=== Ray-Tracer ===//

int				ray_tracer(t_mrt *mrt);
t_ray			cast_ray(t_vec3 origin, t_vec3 point);

//=== Intersect ===//

t_closest		iterate_obj(t_mrt *mrt, t_ray ray);
double			intersect(t_ray ray, t_object *object);
double			intersect_cylinder(t_ray ray, t_object *cylinder,
					t_vec3 *normal);
double			intersect_cap(t_ray ray, t_object *cylinder);
double			intersect_side(t_ray ray, t_object *cylinder);
t_ray			transform_ray(t_ray old_ray, t_object *cylinder);
void			normal_cap(double cap, t_object *cylinder, t_vec3 *normal);

//=== Shader ===//

unsigned int	shader(t_mrt *mrt, t_object *object, double t, t_ray ray);
unsigned int	add_colors(unsigned int color1, unsigned int color2);
unsigned int	multiply_colors(unsigned int color1, unsigned int color2);
unsigned int	scalar_color(unsigned int color, double scalar);

int				in_shadow(t_mrt *mrt, t_ray ray);
int				cam_in_cylinder(t_camera *cam, t_object *cylinder);

//=== MLX ===///

void			put_pixel(t_mlx *mlx, int x, int y, unsigned int color);

int				display_win(t_mrt *mrt);
void			prep_win(t_mrt *mrt);
int				key_hook(int keycode, t_mrt *mrt);

//=== Test Functions ===//

void			prnt_viewport(t_viewport vp);
void			prnt_world(t_world *world);

#endif
