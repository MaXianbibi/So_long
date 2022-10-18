/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorneau <jmorneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:20:31 by jmorneau          #+#    #+#             */
/*   Updated: 2022/10/01 20:18:14 by jmorneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

bool	exit_interaction(t_mlx *game, int key, char c)
{
	if (game->map.map[game->map.caracter.y][game->map.caracter.x + key] == 'E'
		&& game->bonus.bonus == game->bonus.nb_donut && c == 'x')
	{
		print_nb_moves(game, GOLD);
		ft_printf("Bien jouer ! \n");
		game->alive = false;
		return (true);
	}
	else if (game->map.map[game->map.caracter.y + key][game->map.caracter.x]
			== 'E' && game->bonus.bonus == game->bonus.nb_donut && c == 'y')
	{
		print_nb_moves(game, GOLD);
		ft_printf("Bien jouer ! \n");
		game->alive = false;
		return (true);
	}
	return (false);
}

bool	ennemies_interaction(t_mlx *game, int key, char c)
{
	if (game->map.map[game->map.caracter.y][game->map.caracter.x + key] == 'V'
		&& c == 'x')
	{
		print_nb_moves(game, RED);
		ft_printf("GAME OVER\n");
		tile_printer(game, game->map.caracter.x * 120,
			game->map.caracter.y * 120, "./xpm/mort.xpm");
		game->alive = false;
		return (false);
	}
	else if (game->map.map[game->map.caracter.y + key][game->map.caracter.x]
			== 'V' && c == 'y')
	{
		print_nb_moves(game, RED);
		ft_printf("GAME OVER\n");
		tile_printer(game, game->map.caracter.x * 120,
			game->map.caracter.y * 120, "./xpm/mort.xpm");
		game->alive = false;
		return (false);
	}
	return (true);
}

void	print_nb_moves(t_mlx *game, int color)
{
	char	*str_color;

	ft_printf("NOMBRES DE MOVES -> %d \n", ++game->nb_moves);
	str_color = ft_itoa(game->nb_moves);
	tile_printer(game, 0, 0, "./xpm/nuage1.xpm");
	mlx_string_put(game->basic.mlx, game->basic.win, 20, 15,
		color, str_color);
	free(str_color);
}
