/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkuksa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 15:41:40 by bkuksa            #+#    #+#             */
/*   Updated: 2019/10/02 15:41:43 by bkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_error(char *er)
{
	ft_putstr("\033[1;31mFDF: ");
	ft_putstr(er);
	ft_putstr("\033[m\n");
	exit(1);
}

void	init_fdf(t_fdf *fdf, char *str)
{
	fdf->mlx = mlx_init();
	fdf->window = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, "fdf");
	fdf->name = ft_strdup(str);
	fdf->mx_z = 0;
	fdf->img = NULL;
}

void	init_iter(t_it *iter)
{
	iter->i = 0;
	iter->j = 0;
	iter->k = 0;
	iter->x = 0;
	iter->y = 0;
	iter->z = 0;
}

int		ft_abs(int t)
{
	return (t > 0 ? t : -t);
}

void	ft_background(t_fdf *fdf)
{
	int		i;
	int		*wind;

	if (fdf->img == NULL)
	{
		fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
		wind = (int *)mlx_get_data_addr(fdf->img, &i, &i, &i);
		i = WIDTH * HEIGHT;
		while (i-- > 0)
			*wind++ = GREY;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->img, 0, 0);
}
