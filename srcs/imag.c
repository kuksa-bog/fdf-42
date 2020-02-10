/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkuksa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 13:20:45 by bkuksa            #+#    #+#             */
/*   Updated: 2019/10/10 13:20:48 by bkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_map(t_fdf *fdf)
{
	fdf->map.mv_x = 0;
	fdf->map.mv_y = 0;
	fdf->map.rt_x = 270;
	fdf->map.rt_y = 0;
	fdf->map.rt_z = 0;
	fdf->map.scal = 0;
	fdf->color = -1;
	fdf->command = 0;
	if ((WIDTH / fdf->colums) < (HEIGHT / fdf->rows))
		fdf->map.scal = (WIDTH / fdf->colums) / 2;
	else
		fdf->map.scal = (HEIGHT / fdf->rows) / 2;
	fdf->map.cntr_x = WIDTH / 2;
	fdf->map.cntr_y = HEIGHT / 2;
	fdf->map.hght_z = 4;
	ft_put_imag(fdf);
}

void	ft_put_imag(t_fdf *fdf)
{
	t_vk	prv;
	t_vk	dwn;
	t_vk	now;

	mlx_clear_window(fdf->mlx, fdf->window);
	ft_background(fdf);
	init_iter(&fdf->it);
	while (fdf->it.i < (fdf->colums * fdf->rows))
	{
		now = fdf->vk[fdf->it.i];
		ft_transform(fdf, &now);
		if (fdf->it.i < (fdf->colums * fdf->rows) - fdf->colums)
		{
			dwn = fdf->vk[fdf->it.i + fdf->colums];
			ft_transform(fdf, &dwn);
			ft_draw_line(fdf, now, dwn);
		}
		(fdf->it.i > 0 && fdf->it.i % fdf->colums != 0)
										? ft_draw_line(fdf, prv, now) : 0;
		prv = now;
		fdf->it.i++;
	}
	ft_put_str(fdf);
	ft_put_str_2(fdf);
}

void	ft_transform(t_fdf *fdf, t_vk *v)
{
	int		x;
	int		y;
	int		z;

	v->x = (v->x == fdf->colums / 2) ? 0 : v->x - (fdf->colums / 2);
	v->y = (v->y == fdf->rows / 2) ? 0 : v->y - (fdf->rows / 2);
	x = v->x * fdf->map.scal;
	y = v->y * fdf->map.scal;
	fdf->map.beta = (fdf->map.rt_z == 0) ? 0 : (fdf->map.rt_z * (M_PI / 180));
	v->x = x * cos(fdf->map.beta) - y * sin(fdf->map.beta);
	v->y = x * sin(fdf->map.beta) + y * cos(fdf->map.beta);
	z = ft_color(fdf, v);
	x = v->x;
	fdf->map.beta = (fdf->map.rt_y == 0) ? 0 : (fdf->map.rt_y * (M_PI / 180));
	v->x = x * cos(fdf->map.beta) + z * sin(fdf->map.beta);
	v->z = z * cos(fdf->map.beta) - x * sin(fdf->map.beta);
	y = v->y;
	z = v->z;
	fdf->map.beta = (fdf->map.rt_x == 0) ? 0 : (fdf->map.rt_x * (M_PI / 180));
	v->y = y * cos(fdf->map.beta) + z * sin(fdf->map.beta);
	v->z = z * cos(fdf->map.beta) - y * sin(fdf->map.beta);
	v->x += fdf->map.mv_x;
	v->y += fdf->map.mv_y;
	v->x += fdf->map.cntr_x;
	v->y += fdf->map.cntr_y;
}

int		ft_color(t_fdf *fdf, t_vk *v)
{
	int		z;
	int		z1;

	z = v->z * (fdf->map.hght_z);
	z1 = fdf->mx_z * (fdf->map.hght_z);
	if (fdf->color == 1)
	{
		if (z == z1 || z == -z1)
			v->color = RED;
		else if (ft_abs(z) > ft_abs(z1) * 0.8)
			v->color = 0xFF5522;
		else if (ft_abs(z) > ft_abs(z1) * 0.6)
			v->color = 0XFF2299;
		else if (ft_abs(z) > ft_abs(z1) * 0.4)
			v->color = 0XFF22FF;
		else if (ft_abs(z) > ft_abs(z1) * 0.2)
			v->color = 0X9922FF;
		else if (ft_abs(z) > 0)
			v->color = 0x2222FF;
		else
			v->color = 0X2299FF;
	}
	return (z);
}

void	ft_draw_line(t_fdf *fdf, t_vk strt, t_vk end)
{
	t_it	it;

	fdf->it.x = ft_abs(end.x - strt.x);
	fdf->it.y = ft_abs(end.y - strt.y);
	it.y = (end.y > strt.y) ? 1 : -1;
	it.x = (end.x > strt.x) ? 1 : -1;
	it.j = fdf->it.x - fdf->it.y;
	mlx_pixel_put(fdf->mlx, fdf->window, end.x, end.y, end.color);
	fdf->strt_color = strt.color;
	while (strt.x != end.x || strt.y != end.y)
	{
		mlx_pixel_put(fdf->mlx, fdf->window, strt.x, strt.y,
											ft_grad(fdf, strt, end));
		it.k = it.j * 2;
		if (it.k > -fdf->it.y)
		{
			it.j -= fdf->it.y;
			strt.x += it.x;
		}
		if (it.k < fdf->it.x)
		{
			it.j += fdf->it.x;
			strt.y += it.y;
		}
	}
}
