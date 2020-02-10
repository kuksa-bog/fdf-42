/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkuksa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 13:20:55 by bkuksa            #+#    #+#             */
/*   Updated: 2019/10/10 13:20:56 by bkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ft_key(int key, t_fdf *fdf)
{
	t_map	*map;

	map = &fdf->map;
	key == 0 ? ft_changes(fdf, &map->rt_y, -5, 2) : 0;
	key == 2 ? ft_changes(fdf, &map->rt_y, 5, 2) : 0;
	key == 13 ? ft_changes(fdf, &map->rt_x, -5, 2) : 0;
	key == 1 ? ft_changes(fdf, &map->rt_x, 5, 2) : 0;
	key == 12 ? ft_changes(fdf, &map->rt_z, -5, 2) : 0;
	key == 14 ? ft_changes(fdf, &map->rt_z, 5, 2) : 0;
	key == 126 ? ft_changes(fdf, &map->mv_y, -4, 1) : 0;
	key == 125 ? ft_changes(fdf, &map->mv_y, 4, 1) : 0;
	key == 123 ? ft_changes(fdf, &map->mv_x, -4, 1) : 0;
	key == 124 ? ft_changes(fdf, &map->mv_x, 4, 1) : 0;
	key == 27 ? ft_changes(fdf, &map->scal, -1, 3) : 0;
	key == 24 ? ft_changes(fdf, &map->scal, 1, 3) : 0;
	fdf->cnt = -1;
	key == 33 ? ft_changes(fdf, 0, -1, 4) : 0;
	fdf->cnt = 1;
	key == 30 ? ft_changes(fdf, 0, 1, 4) : 0;
	key == 25 ? fdf->command = 1 : 0;
	key == 53 ? exit(0) : 0;
	key == 29 ? ft_map(fdf) : 0;
	return (ft_key_2(key, fdf));
}

int		ft_key_2(int key, t_fdf *fdf)
{
	if (key == 35)
	{
		if (fdf->color == -1)
			fdf->color = 1;
		else
			fdf->color = -1;
		ft_put_imag(fdf);
	}
	if (key == 31)
	{
		if (fdf->command == 0)
			fdf->command = 1;
		else
			fdf->command = 0;
		ft_put_imag(fdf);
	}
	return (0);
}

void	ft_changes(t_fdf *fdf, int *a, int b, int c)
{
	if (c == 1)
		*a += b;
	else if (c == 2)
	{
		*a += b;
		if (*a < 0 || *a >= 360)
			*a = (*a < 0) ? 355 : 0;
	}
	else if (c == 3)
	{
		c = fdf->map.scal;
		if (b > 0 && (c += b))
		{
			if (c * fdf->colums > WIDTH * 4 || c * fdf->rows > HEIGHT * 4)
				c -= b;
		}
		else
			c = (c + b < 1) ? 1 : c + b;
		fdf->map.scal = c;
	}
	else if (c == 4)
		fdf->map.hght_z += fdf->cnt;
	ft_put_imag(fdf);
}

void	ft_put_str(t_fdf *fdf)
{
	char *str;

	mlx_string_put(fdf->mlx, fdf->window, 10, 650, 0xFF9922, "Map - ");
	mlx_string_put(fdf->mlx, fdf->window, 70, 650, 0xFF9922, fdf->name);
	if (fdf->color == 1)
		mlx_string_put(fdf->mlx, fdf->window, 10, 670,
												0xFF9922, "Color mod - on");
	else
		mlx_string_put(fdf->mlx, fdf->window, 10, 670,
											0xFF9922, "Color mod - off");
	mlx_string_put(fdf->mlx, fdf->window, 10, 690,
											0xFF9922, "Height counter - ");
	mlx_string_put(fdf->mlx, fdf->window, 180, 690, 0xFF9922,
										str = ft_itoa(fdf->map.hght_z * 10));
	free(str);
	mlx_string_put(fdf->mlx, fdf->window, 10, 710,
											0xFF9922, "Scale counter - ");
	mlx_string_put(fdf->mlx, fdf->window, 170, 710, 0xFF9922,
											str = ft_itoa(fdf->map.scal));
	free(str);
	mlx_string_put(fdf->mlx, fdf->window, 10, 730,
											0xFF9922, "Rot_X counter - ");
	mlx_string_put(fdf->mlx, fdf->window, 170, 730,
									0xFF9922, str = ft_itoa(fdf->map.rt_x));
	free(str);
}

void	ft_put_str_2(t_fdf *fdf)
{
	char	*str;

	mlx_string_put(fdf->mlx, fdf->window, 990, 20,
											0xFF9922, "-- Us 'o' --");
	mlx_string_put(fdf->mlx, fdf->window, 10, 750,
											0xFF9922, "Rot_Y counter - ");
	mlx_string_put(fdf->mlx, fdf->window, 170, 750,
									0xFF9922, str = ft_itoa(fdf->map.rt_y));
	free(str);
	mlx_string_put(fdf->mlx, fdf->window, 10, 770,
											0xFF9922, "Rot_Z counter - ");
	mlx_string_put(fdf->mlx, fdf->window, 170, 770,
									0xFF9922, str = ft_itoa(fdf->map.rt_z));
	free(str);
	if (fdf->command == 1)
	{
		mlx_string_put(fdf->mlx, fdf->window, 827, 40,
				0xFF9922, "Rot_X - (w s) | Rot_Y - (a d) | Rot_Z - (q e)");
		mlx_string_put(fdf->mlx, fdf->window, 827, 60,
				0xFF9922, "Scal - (+ -)  |  Color - 'p'  |  Reset - 0");
		mlx_string_put(fdf->mlx, fdf->window, 827, 80,
				0xFF9922, "X_mv - (up, dwn) | Y_mv - (right, left)");
	}
}
