/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorneau <jmorneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:54:19 by jmorneau          #+#    #+#             */
/*   Updated: 2022/10/12 01:08:27 by jmorneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static char	*check_newline(int fd)
{
	int		map_found;
	char	*str;

	map_found = 0;
	while (!map_found)
	{
		str = get_next_line(fd);
		if (!str)
			return (NULL);
		if (!ft_strlen(str))
			free(str);
		else
			map_found = 1;
	}
	return (str);
}

static int	line_count(char *file)
{
	int		col;
	char	*str;
	int		fd;

	fd = open(file, O_RDONLY);
	col = 0;
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
		{
			close (fd);
			return (col);
		}
		if (*str != '\n')
			col++;
		free(str);
	}
}

bool	map_reader(char *file, t_mlx *game)
{
	int	fd;
	int	i;

	i = 0;
	game->map.col = line_count(file);
	if (game->map.col == -1 || game->map.col > 68)
		return (print_error("La map ne correspond pas aux critères\n"));
	game->map.map = ft_calloc(sizeof(char *), game->map.col + 1);
	fd = open(file, O_RDONLY);
	game->map.map[0] = check_newline(fd);
	if (!game->map.map[0])
		return (print_error("La map ne correspond pas aux critères\n"));
	while (++i < game->map.col)
		game->map.map[i] = get_next_line(fd);
	game->map.map[i] = NULL;
	game->map.raw = ft_strlen(game->map.map[0]);
	return (error_map(game));
}
