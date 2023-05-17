# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vduchi <vduchi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/22 22:11:19 by vduchi            #+#    #+#              #
#    Updated: 2023/05/17 11:41:24 by vduchi           ###   ########.fr        #
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

NAME			=	pipex

SRC_DIR_MAN		=	src
OBJ_DIR_MAN		=	obj
DEPS_DIR_MAN	=	deps
INC_DIR			=	inc/

LIBFT			=	libft

SRCS			=	src/main.c src/run_command.c
OBJS			=	$(patsubst $(SRC_DIR_MAN)/%, $(OBJ_DIR_MAN)/%, $(SRCS:.c=.o))
DEPS			=	$(patsubst $(SRC_DIR_MAN)/%, $(DEPS_DIR_MAN)/%, $(SRCS:.c=.d))

CFLAGS			+= 	-Wall -Werror -Wextra -g -O3 $(addprefix -I , $(INC_DIR))
LDFLAGS			= 	-L $(LIBFT) -lft
DEPFLAGS_MAN	=	-MMD -MP -MF $(DEPS_DIR_MAN)/$*.d

CC				=	gcc
RM				=	rm -rf
MKDIR			=	mkdir -p

$(OBJ_DIR_MAN)/%.o	:	$(SRC_DIR_MAN)/%.c
	@$(CC) -c $< $(CFLAGS) $(DEPFLAGS_MAN) -o $@
	@echo "$(YELLOW)$(patsubst $(SRC_DIR_MAN)/%,%, $<) \tcompiled!$(DEF_COLOR)"

all				:
	@$(MAKE) -C $(LIBFT)
	@$(MAKE) $(NAME)

$(NAME)		::
	@echo "$(MAGENTA)\nChecking pipex...$(DEF_COLOR)"

$(NAME)		::	$(OBJ_DIR_MAN) $(DEPS_DIR_MAN) $(OBJS)
	@$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) -o $@
	@echo "$(ORANGE)Compiling pipex exec...$(DEF_COLOR)"

$(NAME)		::
	@echo "$(GREEN)Pipex executable ready!$(DEF_COLOR)"

$(OBJ_DIR_MAN)	:
	@$(MKDIR) $@

$(DEPS_DIR_MAN)	:
	@$(MKDIR) $@

clean		:
	@$(RM) $(OBJ_DIR_MAN)
	@$(RM) $(DEPS_DIR_MAN)

fclean		:	clean
	@$(RM) $(NAME)
	@$(MAKE) -C libft fclean
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
