/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorneau <jmorneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:49:43 by jmorneau          #+#    #+#             */
/*   Updated: 2022/10/12 01:04:02 by jmorneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	initialize(t_mlx *game)
{
	game->alive = true;
	game->bonus.bonus = 0;
	game->bonus.nb_donut = 0;
	game->cote = 'D';
	game->frames = 0;
	game->nb_moves = 0;
	game->map.col = 0;
	game->map.raw = 0;
}

int	check_double_c(char **table)
{
	int	i;
	int	j;

	i = 0;
	while (table[i])
	{
		j = 0;
		while (table[i][j])
		{
			if (table[i][j] != 'E' && table[i][j] != 'P' &&
				table[i][j] != 'V' && table[i][j] != '1' &&
				table[i][j] != '0' && table[i][j] != 'C' &&
				table[i][j] != '\n')
				return (
					print_error("La map contient un caractère inconnue\n"));
			j++;
		}
		i++;
	}
	return (1);
}

bool	check_extension(char *str)
{
	char	*tmp;
	int		fd;

	tmp = ft_strrchr(str, '.');
	if (tmp == NULL)
	{
		ft_putstr_fd("Error\nMauvais type de fichier\n", 2);
		return (false);
	}
	if (ft_strncmp(tmp, ".ber", 10) != 0)
	{
		ft_putstr_fd("Error\nMauvais type de fichier\n", 2);
		return (false);
	}
	fd = open(str, O_RDONLY);
	if (fd < 0 || 1 <= 0 || read(fd, 0, 0) < 0)
	{
		ft_putstr_fd("Error\nFile failed to open\n", 2);
		close(fd);
		return (false);
	}
	close(fd);
	return (true);
}

int	main(int argc, char **argv)
{
	t_mlx	game;

	if (argc != 2)
	{
		if (argc == 1)
			ft_printf("Erreur, il manque un argument\n");
		else
			ft_printf("Erreur, plus que deux arguments.\n");
		return (0);
	}
	if (!check_extension(argv[1]))
		return (0);
	initialize(&game);
	if (!map_reader(argv[1], &game))
	{
		ft_free_chartable(game.map.map);
		return (0);
	}
	if (ft_strlen(game.map.map[0]) > 68)
		print_error("La map est trop grande\n");
	else
		game_init(&game);
	if (game.map.map)
		ft_free_chartable(game.map.map);
	return (0);
}
