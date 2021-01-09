/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 16:25:08 by earnaud           #+#    #+#             */
/*   Updated: 2021/01/09 18:42:03 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#define EPSILON 0.000001

float dot_product(t_3d a, t_3d b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_3d cross_product(t_3d a, t_3d b)
{
	t_3d ret;
	ret.x = a.y * b.z - a.z * b.y;
	ret.y = a.z * b.x - a.x * b.z;
	ret.z = a.x * b.y - a.y * b.x;
	return (ret);
}

t_3d sub_product(t_3d a, t_3d b)
{
	t_3d ret;
	ret.x = a.x - b.x;
	ret.y = a.y - b.y;
	ret.z = a.z - b.z;
	return (ret);
}

int moller_trumbore(t_3d startpoint, t_3d endpoint, t_3d *triangle, float *rayt, float *bary_u, float *bary_v)
{
	t_3d edge1;
	t_3d edge2;
	t_3d tvec;
	t_3d pvec;
	t_3d qvec;
	float det, inv_det;

	edge1 = sub_product(triangle[1], triangle[0]);
	edge2 = sub_product(triangle[2], triangle[0]);

	pvec = cross_product(endpoint, edge2);
	det = dot_product(edge1, pvec);

	if (det > -EPSILON && det < EPSILON)
		return (0);
	inv_det = 1.0 / det;

	tvec = sub_product(startpoint, triangle[0]);
	*bary_u = dot_product(tvec, pvec) * inv_det;
	if (*bary_u < 0.0 || *bary_u > 1.0)
		return 0;

	*bary_v = dot_product(qvec, tvec) * inv_det;
}

int main(void)
{
	t_vars vars;
	t_data img;

	int y = 480;
	int x = 640;
	t_3d triangle[2];
	triangle[0].x = 120.f;
	triangle[0].y = 100.f;
	triangle[0].z = 800.f;
	triangle[1].x = 420.f;
	triangle[1].y = 300.f;
	triangle[1].z = 1.f;
	triangle[3].x = 200.f;
	triangle[3].y = 200.f;
	triangle[3].z = 50.f;

	//vars.mlx = mlx_init();
	//vars.win = mlx_new_window(vars.mlx, x, y, "Hello World!");
	//img = new_img(&vars, y, x);
	//projection(&img, triangle);
	//mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	//mlx_loop(vars.mlx);
	return (0);
}
