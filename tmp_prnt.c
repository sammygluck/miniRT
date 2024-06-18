#include "minirt.h"

void	prnt_viewport(t_viewport vp)
{
	t_vec3	tmp;

	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			tmp = pix_to_cord(vp, x ,y);
			printf("X: %i, Y: %i\tvX: %.3f, vY: %.3f, vZ: %.3f\n", x, y, tmp.x, tmp.y, tmp.z);
		}
	}
}

void	prnt_world(t_world *world)
{
	t_list	*lst = world->objects;
	t_object	*obj;

	printf("\nAmbient\n");
	printf("Intensity: %.1f\n", world->amb.intensity);
	printf("Color: 0x%6x\n", world->amb.color);
	printf("\nCamera:\n");
	printf("Origin: [%.1f,%.1f,%.1f]\n", world->cam.origin.x, world->cam.origin.y, world->cam.origin.z);
	printf("Normal: [%.1f,%.1f,%.1f]\n", world->cam.normal.x, world->cam.normal.y, world->cam.normal.z);
	printf("FOV: %i\n", world->cam.fov);
	printf("\nLight\n");
	printf("Origin: [%.1f,%.1f,%.1f]\n", world->light.origin.x, world->light.origin.y, world->light.origin.z);
	printf("Intensity: %.1f\n", world->light.intensity);
	printf("\nParsed Objects: %i", world->obj_parsed);
	while (lst)
	{
		obj = (t_object *)lst->content;
		printf("\nType: %d\n", obj->type);
		printf("Center: [%.1f,%.1f,%.1f]\n", obj->center.x, obj->center.y, obj->center.z);
		printf("Normal: [%.1f,%.1f,%.1f]\n", obj->normal.x, obj->normal.y, obj->normal.z);
		printf("Radius: %.2f\nHeight: %.2f\n", obj->r, obj->h);
		printf("Color: 0x%6x\n", obj->color);
		lst = lst->next;
	}
}
