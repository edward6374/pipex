# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vduchi <vduchi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/22 22:11:19 by vduchi            #+#    #+#              #
#    Updated: 2023/03/20 19:56:17 by vduchi           ###   ########.fr        #
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
SRC_DIR_MAN		=	src_mand
SRC_DIR_BON		=	src_bonus
OBJ_DIR_MAN		=	obj_mand
OBJ_DIR_BON		=	obj_bonus
DEPS_DIR_MAN	=	dep_mand
DEPS_DIR_BON	=	dep_bonus
GNL_DIR			=	get_next_line
INC_DIR			=	inc/ ft_printf/include/ get_next_line/

LIBFT			=	libft
PRINTF			=	ft_printf
ALL_LIBS		=	libft/libft.a ft_printf/libftprintf.a

SRCS			=	src_mand/main.c src_mand/check_command.c src_mand/run_commands.c \
					src_mand/free.c
#SRCS_BONUS		=	src_bonus/main_bonus.c
GNL_SRCS		=	get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
OBJS			=	$(patsubst $(SRC_DIR_MAN)/%, $(OBJ_DIR_MAN)/%, $(SRCS:.c=.o))
#OBJS_BONUS		=	$(patsubst $(SRC_DIR_BON)/%, $(OBJ_DIR_BON)/%, $(SRCS_BONUS:.c=.o))
GNL_OBJS		=	$(patsubst $(GNL_DIR)/%, $(GNL_DIR)/%, $(GNL_SRCS:.c=.o))
DEPS			=	$(patsubst $(SRC_DIR_MAN)/%, $(DEPS_DIR_MAN)/%, $(SRCS:.c=.d))
#DEPS_BONUS		=	$(patsubst $(SRC_DIR_BON)/%, $(DEPS_DIR_BON)/%, $(SRCS_BONUS:.c=.d))
GNL_DEPS		=	$(patsubst $(GNL_DIR)/%, $(GNL_DIR)/%, $(GNL_SRCS:.c=.d))

CFLAGS			+= 	-Wall -Werror -Wextra -g -O3 $(addprefix -I , $(INC_DIR))
LDFLAGS			= 	-L ft_printf -L libft -lft -lftprintf
DEPFLAGS_MAN	=	-MMD -MP -MF $(DEPS_DIR_MAN)/$*.d
DEPFLAGS_BON	=	-MMD -MP -MF $(DEPS_DIR_BON)/$*.d
DEPFLAGS_GNL	=	-MMD -MP -MF $(GNL_DIR)/$*.d

CC				=	gcc
RM				=	rm -rf
MKDIR			=	mkdir -p

$(OBJ_DIR_MAN)/%.o	:	$(SRC_DIR_MAN)/%.c
	@$(CC) $(CFLAGS) $(DEPFLAGS_MAN) -c $< -o $@
	@echo "$(YELLOW)$(patsubst $(SRC_DIR_MAN)/%,%, $<) \tcompiled!$(DEF_COLOR)"

$(OBJ_DIR_BON)/%.o	:	$(SRC_DIR_BON)/%.c
	@$(CC) $(CFLAGS) $(DEPFLAGS_BON) -c $< -o $@
	@echo "$(YELLOW)$(patsubst $(SRC_DIR_BON)/%,%, $<) \tcompiled!$(DEF_COLOR)"

$(GNL_DIR)/%.o		:	$(GNL_DIR)/%.c
	@$(CC) $(CFLAGS) $(DEPFLAGS_GNL) -D BUFFER_SIZE=1 -c $< -o $@
	@echo "$(YELLOW)$(patsubst $(GNL_DIR)/%,%, $<) \tcompiled!$(DEF_COLOR)"

all				:
	@$(MAKE) -C $(LIBFT)
	@$(MAKE) -C $(PRINTF)
	@$(MAKE) $(NAME)

#bonus			:
#	@$(MAKE) -C $(LIBFT)
#	@$(MAKE) -C $(PRINTF)
#	@$(MAKE) $(NAME_BON)

$(NAME)		::
	@echo "$(MAGENTA)\nChecking pipex...$(DEF_COLOR)"

$(NAME)		::	$(OBJ_DIR_MAN) $(DEPS_DIR_MAN) $(OBJS) $(ALL_LIBS)
	@echo "$(ORANGE)Compiling pipex exec...$(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $@

$(NAME)		::
	@echo "$(GREEN)Pipex executable ready!$(DEF_COLOR)"

#$(NAME_BON)		::
#	@echo "$(MAGENTA)\nChecking pipex bonus...$(DEF_COLOR)"

#$(NAME_BON)		::	$(OBJ_DIR_BON) $(DEPS_DIR_BON) $(OBJS_BONUS) $(GNL_OBJS) $(ALL_LIBS)
#	@echo "$(ORANGE)Compiling pipex bonus exec...$(DEF_COLOR)"
#	@$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS_BONUS) $(GNL_OBJS) -o $@

#$(NAME_BON)		::
#	@echo "$(GREEN)Pipex bonus executable ready!$(DEF_COLOR)"

$(OBJ_DIR_MAN)	:
	@$(MKDIR) $@

$(OBJ_DIR_BON)	:
	@$(MKDIR) $@

$(DEPS_DIR_MAN)	:
	@$(MKDIR) $@

$(DEPS_DIR_BON)	:
	@$(MKDIR) $@

clean		:
	@$(RM) $(OBJ_DIR_MAN)
	@$(RM) $(OBJ_DIR_BON)
	@$(RM) $(DEPS_DIR_MAN)
	@$(RM) $(DEPS_DIR_BON)
	@$(RM) $(GNL_OBJS)
	@$(RM) $(GNL_DEPS)

fclean		:	clean
	@$(RM) $(NAME) $(NAME_BON) $(LIBS_DIR)
	@$(MAKE) -C libft fclean
	@$(MAKE) -C ft_printf fclean
	@echo "$(BLUE)\nPush_swap cleaned!$(DEF_COLOR)"

re			:	fclean all

-include $(DEPS)
-include $(GNL_DEPS)
#-include $(DEPS_BONUS)

.PHONY: all clean fclean re

#
#valgrind:
#	valgrind --leak-check=yes --show-leak-kinds=all "nombre del executable" "nombre de argumentos"
#	valgrind --leak-check=yes --track-origins=yes "nombre del executable" "nombre de argumentos"
#
#	gcc $(CFLAGS) -fsanitize=address -g -O3 -fno-omit-frame-pointer $(LDFLAGS) $(SRCS) -o $@
