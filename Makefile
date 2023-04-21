# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vduchi <vduchi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/22 22:11:19 by vduchi            #+#    #+#              #
#    Updated: 2023/04/20 20:32:56 by vduchi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
DEL_LINE		=	\033[2K
ITALIC			=	\033[3m
BOLD			=	\033[1m
DEF_COLOR		=	\033[0;39m
GRAY			=	\033[0;90m
RED				=	\033[0;91m
GREEN			=	\033[0;92m
YELLOW			=	\033[0;93m
BLUE			=	\033[0;94m
MAGENTA			=	\033[0;95m
CYAN			=	\033[0;96m
WHITE			=	\033[0;97m
BLACK			=	\033[0;99m
ORANGE			=	\033[38;5;209m
BROWN			=	\033[38;2;184;143;29m
DARK_GRAY		=	\033[38;5;234m
MID_GRAY		=	\033[38;5;245m
DARK_GREEN		=	\033[38;2;75;179;82m
DARK_YELLOW		=	\033[38;5;143m

NAME		=	pipex
NAME_BON		=	pipex_bonus

LIBS_DIR		=	libs
SRC_DIR_MAN		=	src
OBJ_DIR_MAN		=	obj
DEPS_DIR_MAN	=	deps
INC_DIR			=	inc/ ft_printf/include/

LIBFT			=	libft
PRINTF			=	ft_printf
LIBFT_A			=	libft/libft.a
PRINTF_A		=	ft_printf/libftprintf.a
ALL_LIBS		=	libs/libft.a libs/libftprintf.a

SRCS			=	src/main.c src/check_command.c src/run_commands.c \
					src/free.c
OBJS			=	$(patsubst $(SRC_DIR_MAN)/%, $(OBJ_DIR_MAN)/%, $(SRCS:.c=.o))
DEPS			=	$(patsubst $(SRC_DIR_MAN)/%, $(DEPS_DIR_MAN)/%, $(SRCS:.c=.d))

CFLAGS			+= 	-Wall -Werror -Wextra -g -O3 $(addprefix -I , $(INC_DIR))
LDFLAGS			= 	-L $(LIBS_DIR) -lft -lftprintf
DEPFLAGS_MAN	=	-MMD -MP -MF $(DEPS_DIR_MAN)/$*.d

CC				=	gcc
RM				=	rm -rf
MKDIR			=	mkdir -p

$(OBJ_DIR_MAN)/%.o	:	$(SRC_DIR_MAN)/%.c
	@$(CC) -c $< $(CFLAGS) $(LDFLAGS) $(DEPFLAGS_MAN) -o $@
	@echo "$(YELLOW)$(patsubst $(SRC_DIR_MAN)/%,%, $<) \tcompiled!$(DEF_COLOR)"

all				:	$(LIBS_DIR) $(ALL_LIBS)
	@$(MAKE) $(NAME)

$(NAME)		::
	@echo "$(MAGENTA)\nChecking pipex...$(DEF_COLOR)"

$(NAME)		::	$(OBJ_DIR_MAN) $(DEPS_DIR_MAN) $(OBJS)
	@$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) -o $@
	@echo "$(ORANGE)Compiling pipex exec...$(DEF_COLOR)"

$(NAME)		::
	@echo "$(GREEN)Pipex executable ready!$(DEF_COLOR)"

$(ALL_LIBS)	: $(LIBFT_A) $(PRINTF_A)
	@cp $(LIBFT)/libft.a $(LIBS_DIR)
	@cp $(PRINTF)/libftprintf.a $(LIBS_DIR)

$(LIBFT_A)	:
	@$(MAKE) -C $(LIBFT)

$(PRINTF_A)	:
	@$(MAKE) -C $(PRINTF)

$(LIBS_DIR)	:
	@$(MKDIR) $@

$(OBJ_DIR_MAN)	:
	@$(MKDIR) $@

$(DEPS_DIR_MAN)	:
	@$(MKDIR) $@

clean		:
	@$(RM) $(OBJ_DIR_MAN)
	@$(RM) $(DEPS_DIR_MAN)

fclean		:	clean
	@$(RM) $(NAME) $(LIBS_DIR)
	@$(MAKE) -C libft fclean
	@$(MAKE) -C ft_printf fclean
	@echo "$(BLUE)\nPipex cleaned!$(DEF_COLOR)"

re			:	fclean all

-include $(DEPS)

.PHONY: all clean fclean re

#
#valgrind:
#	valgrind --leak-check=yes --show-leak-kinds=all "nombre del executable" "nombre de argumentos"
#	valgrind --leak-check=yes --track-origins=yes "nombre del executable" "nombre de argumentos"
#
#	gcc $(CFLAGS) -fsanitize=address -g -O3 -fno-omit-frame-pointer $(LDFLAGS) $(SRCS) -o $@
