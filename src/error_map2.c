/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorneau <jmorneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 22:37:11 by jmorneau          #+#    #+#             */
/*   Updated: 2022/09/14 23:31:05 by jmorneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	print_error(char *str)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	return (0);
}

static void	ft_check_way_c(char **map, int y, int x, int *items)
{
	if (map[y][x] != 'C' &&
		map[y][x] != '0' &&
		map[y][x] != 'P')
		return ;
	if (map[y][x] == 'C')
		*(items) += 1;
	map[y][x] = 'R';
	ft_check_way_c(map, y, x + 1, items);
	ft_check_way_c(map, y, x - 1, items);
	ft_check_way_c(map, y + 1, x, items);
	ft_check_way_c(map, y - 1, x, items);
	return ;
}

static void	ft_check_way_e(char **map, int y, int x, int *items)
{
	if (map[y][x] != 'E' &&
		map[y][x] != '0' &&
		map[y][x] != 'P' &&
		map[y][x] != 'C')
		return ;
	if (map[y][x] == 'E')
		*(items) += 1;
	map[y][x] = 'R';
	ft_check_way_e(map, y, x + 1, items);
	ft_check_way_e(map, y, x - 1, items);
	ft_check_way_e(map, y + 1, x, items);
	ft_check_way_e(map, y - 1, x, items);
	return ;
}

static char	**copy_map(t_mlx *game)
{
	int		i;
	int		j;
	char	**cstr;

	j = 0;
	i = 0;
	while (game->map.map[i] != NULL)
		i++;
	cstr = malloc(sizeof(char *) * i + 1);
	while (j < i)
	{
		cstr[j] = ft_strdup(game->map.map[j]);
		j++;
	}
	cstr[j] = NULL;
	return (cstr);
}

int	ft_init_the_way(t_mlx *game)
{
	int		sortie;
	int		bonus;
	char	**cmap;

	sortie = 0;
	bonus = 0;
	cmap = copy_map(game);
	ft_check_way_c(cmap, game->map.caracter.y, game->map.caracter.x, &bonus);
	ft_free_chartable(cmap);
	if (bonus != game->bonus.nb_donut)
		return (print_error("Tous les bonus ne sont pas accessible\n"));
	cmap = copy_map(game);
	ft_check_way_e(cmap, game->map.caracter.y, game->map.caracter.x, &sortie);
	ft_free_chartable(cmap);
	if (sortie == 0)
		return (print_error("Sortie inacessible\n"));
	return (1);
}
