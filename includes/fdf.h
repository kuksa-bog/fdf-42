/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkuksa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 13:52:22 by bkuksa            #+#    #+#             */
/*   Updated: 2019/10/02 13:52:24 by bkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "mlx.h"
# include <math.h>
# define BUFF_SIZE		128
# define WIDTH			1300
# define HEIGHT			800
# define GREY			0x202020
# define RED			0xCC0000
# define GREEN			0xAABB22

typedef struct	s_vk
{
	int			x;
	int			y;
	int			z;
	int			color;
}				t_vk;

typedef struct	s_it
{
	int			i;
	int			j;
	int			k;
	int			x;
	int			y;
	int			z;
}				t_it;

typedef	struct	s_map
{
	float		hght_z;
	int			cntr_x;
	int			cntr_y;
	int			scal;
	int			mv_x;
	int			mv_y;
	int			rt_x;
	int			rt_y;
	int			rt_z;
	float		beta;
}				t_map;

typedef struct	s_fdf
{
	t_map		map;
	t_it		it;
	t_vk		*vk;
	void		*mlx;
	void		*img;
	void		*window;
	char		**y_line;
	char		**x_point;
	char		**if_color;
	char		buf[BUFF_SIZE + 1];
	char		*file;
	char		*name;
	char		*tmp;
	int			mx_z;
	int			rows;
	int			count;
	int			colums;
	int			color;
	int			command;
	int			strt_color;
	float		cnt;
}				t_fdf;

void			ft_read_map(t_fdf *fdf, char *str, int fd, int r);
void			ft_sort_1(t_fdf *fdf);
void			ft_sort_2(t_fdf *fdf);
void			ft_hex(char *str, int *col);

void			init_fdf(t_fdf *fdf, char *str);
void			init_iter(t_it *it);
void			ft_error(char *er);
int				ft_abs(int t);
void			ft_background(t_fdf *fdf);

void			ft_map(t_fdf *fdf);
int				ft_color(t_fdf *fdf, t_vk *v);
void			ft_transform(t_fdf *fdf, t_vk *v);
void			ft_put_imag(t_fdf *fdf);
void			ft_draw_line(t_fdf *fdf, t_vk srt, t_vk end);

int				ft_key(int key, t_fdf *fdf);
int				ft_key_2(int key, t_fdf *fdf);
void			ft_changes(t_fdf *fdf, int *a, int b, int c);
void			ft_put_str(t_fdf *fdf);
void			ft_put_str_2(t_fdf *fdf);

int				ft_grad(t_fdf *fdf, t_vk strt, t_vk end);

#endif
