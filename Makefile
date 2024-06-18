SRCS =	\
		error.c					\
		\
		parser.c				\
		pars_env.c				\
		pars_objects.c			\
		parser_utils.c			\
		\
		mlx.c					\
		prep_win.c				\
		\
		viewport.c				\
		ray_tracer.c			\
		intersect.c				\
		intersect_cylinder.c	\
		\
		shader.c				\
		shadow.c				\
		color_utils.c			\
		\
		vec_math0.c				\
		vec_math1.c				\
		quaternion.c			\
		\
		tmp_prnt.c				\

LIBFT = libft/libft.a
MLX = mlx_linux/libmlx_Linux.a

NAME = miniRT

OBJS_DIR = objs/
OBJS = $(SRCS:.c=.o)
OBJS_PREFIXED = $(addprefix $(OBJS_DIR), $(OBJS))

CC = cc

CC_FLAGS = -Wall -Wextra -Werror -g

MLX_FLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

UP = \033[A
CUT = \033[K

$(OBJS_DIR)%.o : %.c minirt.h vector.h
	@mkdir -p $(OBJS_DIR)
	@echo "\033[38;5;226mCompiling: $<\033[0;39m"
	@$(CC) $(CC_FLAGS) -I/usr/include -Imlx_linux -c $< -o $@
	@printf "$(UP)$(CUT)"

$(NAME): $(OBJS_PREFIXED) main.c $(LIBFT)
	@echo "\033[92mCompiling Done!\033[0;39m"
	@$(CC) $(CC_FLAGS) main.c $(OBJS_PREFIXED) $(LIBFT) $(MLX_FLAGS) $(MLX) -o $(NAME)
	@echo "\033[0;92m$(NAME) Done!\033[0;39m"

$(LIBFT) :
	@$(MAKE) -C ./libft

all: $(NAME)

clean:
	rm -rf $(OBJS_DIR)
	@$(MAKE) clean -C libft/

fclean: clean
	rm -f $(NAME) $(OUT)
	@$(MAKE) fclean -C libft/


re: fclean all

.PHONY: all clean fclean re
