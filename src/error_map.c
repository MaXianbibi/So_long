/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorneau <jmorneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:17:33 by jmorneau          #+#    #+#             */
/*   Updated: 2022/10/01 20:17:02 by jmorneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

bool	error_items(t_mlx *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map.map[i] != NULL)
	{
		j = 0;
		while (game->map.map[i][j])
		{
			if (game->map.map[i][j] == 'C')
				game->bonus.nb_donut++;
			j++;
		}
		i++;
	}
	if (game->bonus.nb_donut == 0)
	{
		ft_putstr_fd("Error\nAucun 'C' n'est présent dans la map \n", 2);
		return (true);
	}
	return (false);
}

bool	error_exit(t_mlx *game)
{
	int	i;
	int	j;
	int	items;

	i = 0;
	items = 0;
	while (game->map.map[i] != NULL)
	{
		j = 0;
		while (game->map.map[i][j])
		{
			if (game->map.map[i][j] == 'E')
				items++;
			j++;
		}
		i++;
	}
	if (items != 1)
	{
		ft_putstr_fd("Error\nLa map doit contenir une sortie\n", 2);
		return (true);
	}
	return (false);
}

bool	error_player(t_mlx *game)
{
	int	i;
	int	j;
	int	items;

	i = 0;
	items = 0;
	while (game->map.map[i] != NULL)
	{
		j = 0;
		while (game->map.map[i][j])
		{
			if (game->map.map[i][j] == 'P')
			{
				game->map.caracter.x = j;
				game->map.caracter.y = i;
				items++;
			}
			j++;
		}
		i++;
	}
	if (items == 1)
		return (false);
	ft_putstr_fd("Error\nLa map doit contenir un 'P'\n", 2);
	return (true);
}

bool	error_mapj(t_mlx *game)
{
	int	j;

	j = 0;
	while (j < game->map.raw)
	{
		if (game->map.map[0][j] != '1' ||
			game->map.map[game->map.col - 1][j] != '1')
		{
			ft_putstr_fd("Error\nLa map n'est pas entouré de murs. \n", 2);
			return (false);
		}
		j++;
	}
	return (true);
}

bool	error_map(t_mlx *game)
{
	int	i;

	i = 0;
	if (error_items(game) || error_exit(game) || !check_double_c(game->map.map)
		|| error_player(game) || !error_mapj(game))
		return (false);
	while (i < game->map.col)
	{
		if (ft_strlen(game->map.map[i]) != ft_strlen(game->map.map[0]))
			return (print_error("Map non rectangulaire"));
		if (game->map.map[i][0] != '1' ||
			game->map.map[i][game->map.raw - 1] != '1')
		{
			ft_putstr_fd("Error\nLa map n'est pas entouré de murs. \n", 2);
			return (false);
		}
		i++;
	}
	if (ft_init_the_way(game) == 0)
		return (false);
	return (true);
}
