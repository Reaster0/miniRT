/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 17:15:31 by earnaud           #+#    #+#             */
/*   Updated: 2021/02/16 15:06:24 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int inside_cyl(t_cylinder *cylinder, t_ray *ray, float t)
{
	t_3d hitpoint;
	t_3d bottom;
	t_3d top;

	hitpoint = add_product(ray->startpoint, multiply_v(t, ray->endpoint));
	bottom = sub_product(hitpoint, cylinder->point);
	top = sub_product(hitpoint, cylinder->pointup);

	if (dot_product(cylinder->orient, bottom) > 0.0 && dot_product(cylinder->orient, top) < 0.0)
		return (1);
	return (0);
}

int inter_cylinder(t_ray *ray, t_cylinder *cylinder)
{
	int ret;
	t_3d oc;
	t_3d dir;
	t_3d ocdir;
	t_3d quadra;
	t_2d t;
	float discriminant;
	ret = 0;

	oc = sub_product(ray->startpoint, cylinder->point);
	dir = sub_product(ray->endpoint, multiply_v(dot_product(ray->endpoint, cylinder->orient), cylinder->orient));
	ocdir = sub_product(oc, multiply_v(dot_product(oc, cylinder->orient), cylinder->orient));

	quadra.x = dot_product(dir, dir);
	quadra.y = 2.0 * dot_product(dir, ocdir);
	quadra.z = dot_product(ocdir, ocdir) - sqr(cylinder->rayon);

	discriminant = sqr(quadra.y) - (4.0 * quadra.x * quadra.z);
	if (discriminant < 0.0)
		return (0);

	t.x = (-quadra.y + sqrt(discriminant)) / (2.0 * quadra.x);
	t.y = (-quadra.y - sqrt(discriminant)) / (2.0 * quadra.x);

	if (t.x > 0.000001 && inside_cyl(cylinder, ray, t.x) && t.x < ray->t)
	{
		ray->t = t.x;
		ray->shape_point = cylinder->point;
		ray->shape_color = cylinder->color;
		ret = 1;
	}
	if (t.y > 0.000001 && inside_cyl(cylinder, ray, t.y) && t.y < ray->t)
	{
		ray->t = t.y;
		ray->shape_point = cylinder->point;
		ray->shape_color = cylinder->color;
		ret = 1;
	}
	if (ret)
	{
		t_3d hit_p = add_product(ray->startpoint, multiply_v(ray->t, ray->endpoint));
		//cas ou je touche les caps
		t_3d inter_vec = sub_product(cylinder->pointup, hit_p);
		// if (!dot_product(inter_vec, cylinder->orient))
		// 	ray->shape_normale = cylinder->orient;

		// inter_vec = sub_product(cylinder->point, hit_p);
		// if (!dot_product(inter_vec, cylinder->orient))
		// 	ray->shape_normale = cylinder->orient;

		t_3d cylinder_center = divide_vr(2, add_product(cylinder->point, cylinder->pointup));
		t_3d cyloritocenter = sub_product(cylinder_center, hit_p);

		inter_vec = multiply_v(dot_product(cyloritocenter, cylinder->orient), cylinder->orient);
		t_3d pcylaxis = add_product(cylinder_center, inter_vec);
		ray->shape_normale = get_norm(sub_product(hit_p, pcylaxis));
	}

	// if (length2(sub_product(multiply_v(ray->t, ray->endpoint), cylinder->pointup)) < cylinder->rayon)
	// 	ray->shape_normale = cylinder->orient;
	// if (length2(sub_product(multiply_v(ray->t, ray->endpoint), cylinder->point)) < cylinder->rayon)
	// 	ray->shape_normale = multiply_v(-1.f, cylinder->orient);
	// else
	// {
	// 	int t2 = dot_product(sub_product(multiply_v(ray->t, ray->endpoint), cylinder->point), cylinder->orient);
	// 	t_3d pt = add_product(cylinder->point, multiply_v(t2, cylinder->orient));
	// 	ray->shape_normale = get_norm(sub_product(multiply_v(ray->t, ray->endpoint), pt));
	// }
	return (ret);
}

void inter_lights(t_ray *ray, t_light **light, t_shapes *shapes)
{
	int i;
	i = 0;
	while (light[i])
	{
		inter_light(ray, light[i], shapes);
		i++;
	}
}

int inter_cylinders(t_ray *ray, t_cylinder **cylinder)
{
	int i = 0;
	int ret;
	ret = 0;
	while (cylinder[i])
	{
		if (inter_cylinder(ray, cylinder[i]))
			ret = 1;
		i++;
	}
	return (ret);
}

int inter_square(t_ray *ray, t_square *square)
{
	int result;

	t_triangle *triangle1;
	t_triangle *triangle2;
	result = 0;
	triangle1 = new_triangle(square->a, square->b, square->c, square->color);
	triangle2 = new_triangle(square->a, square->c, square->d, square->color);
	if (inter_triangle(ray, triangle1))
		result = (1);
	free(triangle1);
	if (inter_triangle(ray, triangle2))
		result = (1);
	free(triangle2);
	// if (result == 1)
	// {
	// 	//ray->shape_point = sub_product(square->c, divide_vr(2, square->a));
	// 	//ray->shape_normale = cross_product(sub_product(square->c, square->b), sub_product(square->a, square->b));
	// 	ray->shape_color = square->color;
	// }
	return (result);
}

int inter_squares(t_ray *ray, t_square **square)
{
	int i = 0;
	int ret;
	ret = 0;
	while (square[i])
	{
		if (inter_square(ray, square[i]))
			ret = 1;
		i++;
	}
	return (ret);
}

int inter_plane(t_ray *ray, t_plane *plane)
{
	float dDotN;
	float t;
	if (dot_product(ray->endpoint, plane->normal) > 0.f)
		plane->normal = multiply_v(-1, plane->normal);
	dDotN = dot_product(ray->endpoint, plane->normal);
	if (dDotN == 0.f)
		return (0);

	//maybe it's ray->startpoint
	t = dot_product(sub_product(plane->position, ray->startpoint), plane->normal) / dDotN;
	if (t <= 0.000001f || t >= ray->t)
		return (0);
	//ray->color = plane->color;
	ray->shape_color = plane->color;
	ray->t = t;
	ray->shape_point = plane->position;
	ray->shape_normale = plane->normal;
	return (1);
}

int inter_sphere(t_ray *ray, t_sphere *sphere)
{
	float a;
	float b;
	float c;
	float discriminant;
	float t1;
	float t2;
	t_ray localRay;
	localRay = *ray;
	localRay.startpoint = sub_product(localRay.startpoint, sphere->startpoint);

	a = length2(ray->endpoint);
	b = 2.f * dot_product(localRay.endpoint, localRay.startpoint);
	c = length2(localRay.startpoint) - sqr(sphere->r);
	discriminant = sqr(b) - 4 * a * c;
	if (discriminant < 0.0f)
		return (0);
	t1 = (-b - sqrt(discriminant)) / (2 * a);
	t2 = (-b + sqrt(discriminant)) / (2 * a);
	if (t1 > 0.0001f && t1 < ray->t)
		ray->t = t1;
	else if (t2 > 0.0001f && t2 < ray->t)
		ray->t = t2;
	else
		return (0);
	//ray->color = sphere->color;

	ray->shape_point = sphere->startpoint;
	ray->shape_color = sphere->color;

	ray->shape_normale = sub_product(ray->startpoint, sphere->startpoint);
	normalize(&ray->shape_normale);
	return (1);
}

int inter_planes(t_ray *ray, t_plane **plane)
{
	int i = 0;
	int ret;
	ret = 0;
	while (plane[i])
	{
		if (inter_plane(ray, plane[i]))
			ret = 1;
		i++;
	}
	return (ret);
}

int inter_spheres(t_ray *ray, t_sphere **sphere)
{
	int i = 0;
	int ret;
	ret = 0;
	while (sphere[i])
	{
		if (inter_sphere(ray, sphere[i]))
			ret = 1;
		i++;
	}
	return (ret);
}

int inter_triangles(t_ray *ray, t_triangle **triangle)
{
	int i = 0;
	int ret;
	ret = 0;
	while (triangle[i])
	{
		if (inter_triangle(ray, triangle[i]))
			ret = 1;
		i++;
	}
	return (ret);
}
//problemes sur les triangles qui sont derrieres la camera
int inter_triangle(t_ray *ray, t_triangle *triangle)
{
	t_3d edge1;
	t_3d edge2;
	t_3d orig_minus_vert0;
	t_3d cross_raydir_edge2;
	t_3d cross_oriminusvert0_edge1;
	float determinent, inv_determinent;
	float t;

	edge1 = sub_product(triangle->b, triangle->a);
	edge2 = sub_product(triangle->c, triangle->a);

	cross_raydir_edge2 = cross_product(ray->endpoint, edge2);
	determinent = dot_product(edge1, cross_raydir_edge2);

	if (determinent > -0.000001f && determinent < 0.000001f)
		return (0);
	inv_determinent = 1.0f / determinent;

	orig_minus_vert0 = sub_product(ray->startpoint, triangle->a);

	triangle->barycentric.y = dot_product(orig_minus_vert0, cross_raydir_edge2) * inv_determinent;
	if (triangle->barycentric.y < 0.0f || triangle->barycentric.y > 1.0f)
		return (0);

	cross_oriminusvert0_edge1 = cross_product(orig_minus_vert0, edge1);

	triangle->barycentric.z = dot_product(ray->endpoint, cross_oriminusvert0_edge1) * inv_determinent;
	if (triangle->barycentric.z < 0.0f || triangle->barycentric.z > 1.0f)
		return (0);
	triangle->barycentric.x = 1 - triangle->barycentric.y - triangle->barycentric.z;

	if (triangle->barycentric.x < 0.0f || triangle->barycentric.z > 1.0f)
		return (0);

	t = dot_product(edge2, cross_oriminusvert0_edge1) * inv_determinent;
	if (t < ray->t)
	{
		ray->shape_normale = cross_product(sub_product(triangle->b, triangle->a), sub_product(triangle->c, triangle->a));
		ray->shape_point = new_3d((triangle->a.x + triangle->b.x + triangle->c.x) / 2, (triangle->a.y + triangle->b.y + triangle->c.y) / 2, (triangle->a.z + triangle->b.z + triangle->c.z) / 2);
		ray->t = t;

		ray->color = triangle->color;
		ray->shape_color = triangle->color;
	}
	return (1);
}

//new version
t_camera world_to_cam(float **matrix, t_3d from)
{
	t_camera camera;
	outcol(matrix[3], &camera.startpoint);
	outcol(matrix[2], &camera.forward);
	outcol(matrix[1], &camera.up);
	outcol(matrix[0], &camera.right);
	return (camera);
}

float **cam_to_world(t_camera camera, t_3d to)
{
	float matrix[3][3];

	fillcol(matrix[0], camera.right);
	fillcol(matrix[1], camera.up);
	fillcol(matrix[2], camera.forward);
	fillcol(matrix[3], to);

	return (matrix);
}

t_camera cam_lookat(t_3d origin, t_3d target, float fov, float ratio)
{
	t_camera result;
	result.startpoint = origin;
	result.forward = get_norm(sub_product(origin, target));
	result.right = cross_product(get_norm(new_3d(0.f, 1.f, 0.f)), result.forward);

	matrix4(result);
}

//new version

t_ray make_ray(t_camera camera, t_2d point)
{
	t_ray result;
	result.startpoint = camera.startpoint;
	result.endpoint = camera.forward;
	result.endpoint = add_product(result.endpoint, multiply_v(point.x * camera.w, camera.right));
	result.endpoint = add_product(result.endpoint, multiply_v(point.y * camera.h, camera.up));
	normalize(&result.endpoint);
	// printf("x=%f,y=%f,z=%f\n", result.endpoint.x, result.endpoint.y, result.endpoint.z);
	result.t = 1.0e30f;
	result.color = 0;
	return (result);
}

t_camera new_camera(t_3d origin, t_3d target, t_3d upguide, float fov, float ratio)
{ //pensez a fix le cas ou upguide == target
	t_camera result;
	result.startpoint = origin;
	result.forward = get_norm(sub_product(target, origin));
	result.right = cross_product(result.forward, upguide);
	normalize(&result.right);
	result.up = cross_product(result.right, result.forward);
	//fov / 2
	result.h = tan(fov);
	result.w = result.h * ratio;
	return (result);
}