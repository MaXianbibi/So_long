/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_tiles.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorneau <jmorneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:12:33 by jmorneau          #+#    #+#             */
/*   Updated: 2022/10/01 19:11:32 by jmorneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	if_donut(t_mlx *game, int i, int j)
{
	tile_printer(game, j * 120, i * 120, "./xpm/donut-au-sucre.xpm");
}

void	if_player(t_mlx *game, int i, int j)
{
	tile_printer(game, j * 120, i * 120, "./xpm/homer.xpm");
	game->map.caracter.x = j;
	game->map.caracter.y = i;
}

void	if_exit(t_mlx *game, int i, int j)
{
	game->map.exit.y = i;
	game->map.exit.x = j;
	mlx_loop_hook(game->basic.mlx, exit_animation, game);
}

void	if_tile(t_mlx *game, int i, int j)
{
	if (game->map.map[i][j] == '1')
		tile_printer(game, j * 120, i * 120, "./xpm/nuage1.xpm");
	else if (game->map.map[i][j] == '0')
		tile_printer(game, j * 120, i * 120, "./xpm/void.xpm");
	else if (game->map.map[i][j] == 'C')
		if_donut(game, i, j);
	else if (game->map.map[i][j] == 'P')
		if_player(game, i, j);
	else if (game->map.map[i][j] == 'E')
		if_exit(game, i, j);
	else if (game->map.map[i][j] == 'V')
		tile_printer(game, j * 120, i * 120, "./xpm/ennemie.xpm");
}
