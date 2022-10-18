/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorneau <jmorneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 15:30:01 by jmorneau          #+#    #+#             */
/*   Updated: 2022/10/01 19:17:59 by jmorneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	tile_printer(t_mlx *game, int x, int y, char *path)
{
	int	width;
	int	height;

	game->image.img = mlx_xpm_file_to_image
		(game->basic.mlx, path, &width, &height);
	mlx_put_image_to_window(game->basic.mlx,
		game->basic.win, game->image.img, x, y);
}

int	exit_animation(t_mlx *game)
{
	if (game->frames >= 29)
		game->frames = 0;
	if (game->frames >= 0 && game->frames < 5)
		tile_printer(game, game->map.exit.x * 120,
			game->map.exit.y * 120, "./xpm-animated/portail1v.xpm");
	else if (game->frames >= 5 && game->frames < 10)
		tile_printer(game, game->map.exit.x * 120,
			game->map.exit.y * 120, "./xpm-animated/portail2v.xpm");
	else if (game->frames >= 10 && game->frames < 15)
		tile_printer(game, game->map.exit.x * 120,
			game->map.exit.y * 120, "./xpm-animated/portail3v.xpm");
	else if (game->frames >= 15 && game->frames < 20)
		tile_printer(game, game->map.exit.x * 120,
			game->map.exit.y * 120, "./xpm-animated/portail4v.xpm");
	else if (game->frames >= 20 && game->frames < 25)
		tile_printer(game, game->map.exit.x * 120,
			game->map.exit.y * 120, "./xpm-animated/portail5v.xpm");
	else if (game->frames >= 25 && game->frames < 30)
		tile_printer(game, game->map.exit.x * 120,
			game->map.exit.y * 120, "./xpm-animated/portail6v.xpm");
	game->frames++;
	return (0);
}

void	tile_generetor(t_mlx *game)
{
	int	i;
	int	j;

	i = 0;
	game->map.cordmap.y = 0;
	while (game->map.map[i])
	{
		j = 0;
		game->map.cordmap.x = 0;
		while (game->map.map[i][j])
			if_tile(game, i, j++);
		game->map.cordmap.y += 120;
		i++;
	}
}

void	game_init(t_mlx *game)
{
	game->basic.mlx = mlx_init();
	game->basic.win = mlx_new_window(game->basic.mlx,
			(game->map.raw * 120), (game->map.col * 120), "./so_long");
	tile_generetor(game);
	mlx_hook(game->basic.win, 2, 1L << 0, move, game);
	mlx_hook(game->basic.win, 17, 0, (void *)exit, 0);
	mlx_loop(game->basic.mlx);
}
