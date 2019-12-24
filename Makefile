# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/10 16:17:49 by ysarsar           #+#    #+#              #
#    Updated: 2019/12/24 19:46:28 by ysarsar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT_PATH = libft/
INC = -I ./includes/ -I $(LIBFT_PATH)
SRC_DIR = src/
OBJ_DIR = obj/
FLAGS = -Wall -Wextra -Werror

SRC_NAME =	builtins.c \
			execute.c \
			file_check.c \
			ft_change_arg.c \
			ft_env_var.c \
			ft_modify_env.c \
			get_next_line.c \
			list_push.c \
			list_to_tab.c \
			main.c \
			msh_execute.c \
			msh_loop.c \
			print_error.c \
			split.c \
			ft_cd_c.c \

SRCS = $(addprefix $(SRC_DIR), $(SRC_NAME))
OBJS = $(addprefix $(OBJ_DIR), $(SRC_NAME:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
		@make -C $(LIBFT_PATH)
		@gcc $(FLAGS) $(OBJS) $(INC) -L $(LIBFT_PATH) -lft -o $(NAME)
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
		@mkdir -p obj
		@gcc -c $(INC) $^ -o $@
clean:
		@make clean -C $(LIBFT_PATH)
		@rm -rf $(OBJ_DIR)
fclean:
		@make clean -C $(LIBFT_PATH)
		@rm -f $(NAME)
		@rm -rf obj/ minishell.dSYM/
re: fclean all
