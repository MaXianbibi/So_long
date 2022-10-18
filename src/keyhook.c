/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorneau <jmorneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:35:34 by jmorneau          #+#    #+#             */
/*   Updated: 2022/09/19 22:09:16 by jmorneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

bool	stop_player(t_mlx *game, int key, char c)
{
	if (c == 'x')
	{
		if (game->map.map[game->map.caracter.y][game->map.caracter.x + key]
			== '1' || (game->map.map[game->map.caracter.y]
			[game->map.caracter.x + key] == 'E'
			&& game->bonus.bonus != game->bonus.nb_donut))
			return (false);
	}
	else
	{
		if (game->map.map[game->map.caracter.y + key][game->map.caracter.x]
			== '1' || (game->map.map[game->map.caracter.y + key]
			[game->map.caracter.x] == 'E'
			&& game->bonus.bonus != game->bonus.nb_donut))
			return (false);
	}
	return (true);
}

void	bonus_interaction(t_mlx *game, int key, char c)
{
	if (game->map.map[game->map.caracter.y]
		[game->map.caracter.x + key] == 'C' && c == 'x')
	{
		game->map.map[game->map.caracter.y][game->map.caracter.x + key] = '0';
		game->bonus.bonus++;
	}
	else if (game->map.map[game->map.caracter.y + key]
		[game->map.caracter.x] == 'C' && c == 'y')
	{
		game->map.map[game->map.caracter.y + key][game->map.caracter.x] = '0';
		game->bonus.bonus++;
	}
}

int	move_x(t_mlx *game, int key)
{
	if (stop_player(game, key, 'x') == false)
		return (0);
	bonus_interaction(game, key, 'x');
	game->cote = 'D';
	if (ennemies_interaction(game, key, 'x'))
		tile_printer(game, game->map.caracter.x * 120,
			game->map.caracter.y * 120, "./xpm/void.xpm");
	if (exit_interaction(game, key, 'x') == false && game->alive == true)
	{
		game->map.caracter.x += (key * 1);
		print_nb_moves(game, BLACK);
		if (key < 0)
		{
			game->cote = 'G';
			tile_printer(game, game->map.caracter.x * 120,
				game->map.caracter.y * 120, "./xpm/homer-gauche.xpm");
		}
		else
			tile_printer(game, game->map.caracter.x * 120,
				game->map.caracter.y * 120, "./xpm/homer.xpm");
	}
	return (0);
}

int	move_y(t_mlx *game, int key)
{
	if (stop_player(game, key, 'y') == false)
		return (0);
	bonus_interaction(game, key, 'y');
	if (ennemies_interaction(game, key, 'y'))
		tile_printer(game, game->map.caracter.x * 120,
			game->map.caracter.y * 120, "./xpm/void.xpm");
	if (exit_interaction(game, key, 'y') == false && game->alive == true)
	{
		print_nb_moves(game, BLACK);
		game->map.caracter.y += (key * 1);
		if (game->cote == 'G')
			tile_printer(game, game->map.caracter.x * 120,
				game->map.caracter.y * 120, "./xpm/homer-gauche.xpm");
		else
			tile_printer(game, game->map.caracter.x * 120,
				game->map.caracter.y * 120, "./xpm/homer.xpm");
	}
	return (0);
}

int	move(int keycode, t_mlx *game)
{
	if (game->alive == true)
	{
		if (keycode == 2)
			move_x(game, 1);
		if (keycode == 0)
			move_x(game, -1);
		if (keycode == 1)
			move_y(game, 1);
		if (keycode == 13)
			move_y(game, -1);
	}
	if (keycode == 53 || game->alive == false)
	{
		game->alive = false;
		ft_free_chartable(game->map.map);
		mlx_destroy_image(game->basic.mlx, game->image.img);
		mlx_hook(game->basic.win, 17, 0, (void *)exit, 0);
		exit(0);
	}
	return (0);
}
