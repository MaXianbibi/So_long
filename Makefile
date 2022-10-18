# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmorneau <jmorneau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/04 22:00:22 by jmorneau          #+#    #+#              #
#    Updated: 2022/09/27 21:37:17 by jmorneau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
LIBFT = libft/libft.a
CC = @gcc
CFLAGS = -Wall -Wextra -Werror -g
LFLAGS = -lmlx -framework OpenGL -framework AppKit
RM = @rm -f
INCLUDE = -I include/

SRC_DIR = src/
SRC_FILES =	error_map.c game_init.c if_tiles.c interaction.c keyhook.c map_reader.c so_long.c error_map2.c

OBJ_DIR = objs/
OBJS = ${addprefix ${OBJ_DIR}, $(SRC_FILES:.c=.o)}

${OBJ_DIR}%.o: ${SRC_DIR}%.c
	@echo "$(_BLUE)$(_BOLD)Compilation Printf: $< $(_END)"
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

#Couleurs!
_END=$'\x1b[0m
_BOLD=$'\x1b[1m
_UNDER=$'\x1b[4m
_RED=$'\x1b[31m
_GREEN=$'\x1b[32m
_YELLOW=$'\x1b[33m
_BLUE=$'\x1b[34m
_PURPLE=$'\x1b[35m
_WHITE=$'\x1b[37m
_IRED=$'\x1b[41m
_IGREEN=$'\x1b[42m
_IYELLOW=$'\x1b[43m
_IBLUE=$'\x1b[44m
_IPURPLE=$'\x1b[45m
_IWHITE=$'\x1b[47m

all: $(NAME)

$(NAME): ${OBJ_DIR} $(OBJS) ${LIBFT}
	${CC} $(LFLAGS) ${OBJS} ${LIBFT} -o $@

play :
	@make all
	@make display
	@echo "enter map id:"; \
	read ID; \
	make $$ID
	
display :
		clear
		@echo "$(_BLUE)$(_BOLD)MAPS DISPONIBLES: \n$< $(_END)"
		@echo "$(_GREEN)$(_BOLD)1. map.ber$(_GREEN) $< $(_END)"
		@echo "$(_GREEN)$(_BOLD)2. map2.ber$(_GREEN) $< $(_END)"
		@echo "$(_GREEN)$(_BOLD)3. map3.ber$(_GREEN) $< $(_END)"
		@echo "$(_GREEN)$(_BOLD)4. map.ber$(_GREEN) $< $(_END)"

1:
	clear
	@echo "$(_IYELLOW)LANCEMENT MAP 1$(_IYELLOW) $< $(_END)"
	./so_long ./map_files/map.ber
	
2 :
	clear
	@echo "$(_IYELLOW)LANCEMENT MAP 2$(_IYELLOW) $< $(_END)"
	./so_long ./map_files/map2.ber
	
3 :
	clear
	@echo "$(_IYELLOW)LANCEMENT MAP 3$(_IYELLOW) $< $(_END)"
	./so_long ./map_files/map3.ber
4 :
	clear
	@echo "$(_IYELLOW)LANCEMENT MAP 4$(_IYELLOW) $< $(_END)"
	./so_long ./map_files/map4.ber

${OBJ_DIR}:
	mkdir -p $@

${LIBFT}:
	@make -C ./libft

clean:
	@$(MAKE) clean -C ./libft
	@$(RM) -r ${OBJ_DIR}

fclean: clean
	@$(MAKE) fclean -C ./libft
	@$(RM) $(NAME)

re: fclean all



