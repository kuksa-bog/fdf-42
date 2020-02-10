/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkuksa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 14:21:37 by bkuksa            #+#    #+#             */
/*   Updated: 2019/10/02 14:21:39 by bkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		main(int ac, char **av)
{
	t_fdf	*fdf;

	if (ac != 2)
		ft_error("ERROR: usage: ./fdf map");
	fdf = (t_fdf *)ft_memalloc(sizeof(t_fdf));
	init_fdf(fdf, av[1]);
	ft_read_map(fdf, av[1], -1, 0);
	ft_map(fdf);
	mlx_hook(fdf->window, 2, 0, ft_key, fdf);
	mlx_loop(fdf->mlx);
	return (0);
}

void	ft_read_map(t_fdf *fdf, char *str, int fd, int r)
{
	if ((fd = open(str, O_RDONLY, 0)) <= 0)
		ft_error(ft_strjoin("ERROR: open -> ", fdf->name));
	fdf->file = ft_memalloc(1);
	while ((r = read(fd, fdf->buf, BUFF_SIZE)) > 0)
	{
		fdf->buf[r] = '\0';
		fdf->tmp = fdf->file;
		fdf->file = ft_strjoin(fdf->tmp, fdf->buf);
		free(fdf->tmp);
	}
	close(fd);
	if (!fdf->file)
		ft_error(ft_strjoin("ERROR: read -> ", fdf->name));
	init_iter(&fdf->it);
	fdf->y_line = ft_strsplit(fdf->file, '\n');
	fdf->x_point = ft_strsplit(fdf->y_line[0], ' ');
	while (fdf->x_point[fdf->it.i])
		free(fdf->x_point[fdf->it.i++]);
	fdf->colums = fdf->it.i;
	while (fdf->y_line[fdf->it.j])
		fdf->it.j++;
	fdf->rows = fdf->it.j;
	free(fdf->x_point);
	ft_sort_1(fdf);
}

void	ft_sort_1(t_fdf *fdf)
{
	init_iter(&fdf->it);
	fdf->vk = (t_vk *)ft_memalloc(sizeof(t_vk) * (fdf->rows * fdf->colums));
	while (fdf->y_line[fdf->it.y])
	{
		fdf->it.x = 0;
		fdf->x_point = ft_strsplit(fdf->y_line[fdf->it.y], ' ');
		while (fdf->x_point[fdf->it.x] && fdf->it.x < fdf->colums)
		{
			ft_sort_2(fdf);
			free(fdf->x_point[fdf->it.x++]);
			fdf->it.i++;
		}
		if (fdf->colums > fdf->it.x)
			ft_error("ERROR: rows");
		free(fdf->x_point);
		fdf->it.y++;
	}
	while (fdf->y_line[fdf->it.k])
		free(fdf->y_line[fdf->it.k++]);
	free(fdf->y_line);
}

void	ft_sort_2(t_fdf *fdf)
{
	fdf->vk[fdf->it.i].x = fdf->it.x;
	fdf->vk[fdf->it.i].y = fdf->it.y;
	fdf->vk[fdf->it.i].z = ft_atoi(fdf->x_point[fdf->it.x]);
	fdf->mx_z = (fdf->vk[fdf->it.i].z > fdf->mx_z)
						? fdf->vk[fdf->it.i].z : fdf->mx_z;
	if (ft_strchr(fdf->x_point[fdf->it.x], ','))
	{
		fdf->it.j = 0;
		while (fdf->x_point[fdf->it.x][fdf->it.j] != ',')
			fdf->it.j++;
		fdf->it.j += 3;
		if (fdf->x_point[fdf->it.x][fdf->it.j])
			ft_hex(&fdf->x_point[fdf->it.x][fdf->it.j],
										&fdf->vk[fdf->it.i].color);
	}
	else
		fdf->vk[fdf->it.i].color = (fdf->vk[fdf->it.i].z == 0) ? GREEN : RED;
}

void	ft_hex(char *str, int *col)
{
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			*col = *col * 16 + *str - '0';
		else if (*str >= 'a' && *str <= 'f')
			*col = *col * 16 + *str - 'a' + 10;
		else
			*col = *col * 16 + *str - 'A' + 10;
		str++;
	}
}
