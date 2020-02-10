/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grad.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkuksa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 15:45:50 by bkuksa            #+#    #+#             */
/*   Updated: 2019/11/05 15:45:53 by bkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static float	ft_percent(int start, int end, int now)
{
	float	a;
	float	b;

	a = now - start;
	b = end - start;
	return ((b == 0) ? 1.0 : ((a) / (b)));
}

static int		ft_rgb(int start, int end, float perc)
{
	return ((int)((1 - perc) * start + perc * end));
}

int				ft_grad(t_fdf *fdf, t_vk strt, t_vk end)
{
	int		red;
	int		grn;
	int		blu;
	float	percent;

	if (end.color == strt.color)
		return (strt.color);
	if (fdf->it.x > fdf->it.y)
		percent = ft_percent((end.x > strt.x) ? end.x - fdf->it.x
										: end.x + fdf->it.x, end.x, strt.x);
	else
		percent = ft_percent((end.y > strt.y) ? end.y - fdf->it.y
										: end.y + fdf->it.y, end.y, strt.y);
	red = ft_rgb((fdf->strt_color >> 16) & 255,
										(end.color >> 16) & 255, percent);
	grn = ft_rgb((fdf->strt_color >> 8) & 255,
											(end.color >> 8) & 255, percent);
	blu = ft_rgb(fdf->strt_color & 255, end.color & 255, percent);
	return ((red << 16) | (grn << 8) | blu);
}
