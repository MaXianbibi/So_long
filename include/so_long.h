/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorneau <jmorneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:40:03 by jmorneau          #+#    #+#             */
/*   Updated: 2022/10/01 23:19:47 by jmorneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "./libft.h"
# include <mlx.h>
# include <stdbool.h>

# define RED 0xFFFF0000
# define BLACK 0
# define GOLD 0xFFD700

typedef struct s_img
{
	void	*img;
}	t_img;

typedef struct s_basic
{
	void	*mlx;
	void	*win;
}	t_basic;

typedef struct s_cord
{
	int	y;
	int	x;
}	t_cord;

typedef struct s_map
{
	char	**map;
	t_cord	caracter;
	t_cord	exit;
	t_cord	ijmap;
	t_cord	cordmap;
	int		col;
	int		raw;
}	t_map;

typedef struct s_bonus
{
	int	bonus;
	int	nb_donut;
}	t_bonus;

typedef struct s_mlx
{
	t_basic	basic;
	t_img	image;
	t_map	map;
	t_bonus	bonus;
	bool	alive;
	int		nb_moves;
	char	cote;
	int		frames;
}	t_mlx;

bool	map_reader(char *file, t_mlx *game);
void	game_init(t_mlx *game);
bool	error_map(t_mlx *game);
int		move(int keycode, t_mlx *vars);
void	tile_printer(t_mlx *game, int x, int y, char *path);
bool	exit_interaction(t_mlx *game, int key, char c);
bool	ennemies_interaction(t_mlx *game, int key, char c);
void	print_nb_moves(t_mlx *game, int color);
void	if_tile(t_mlx *game, int i, int j);
int		exit_animation(t_mlx *game);
int		ft_init_the_way(t_mlx *game);
int		print_error(char *str);
int		check_double_c(char **table);

#endif