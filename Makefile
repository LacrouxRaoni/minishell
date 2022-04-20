NAME	=	minishell

PATH_LIBFT	=	./librarie/libft
LIBFT	=	$(PATH_LIBFT)/libft.a

I_MINISHELL	=	-I ./include

I_OBJ	=	-I ./ -I ./librarie/libft/
LINK	=	-I ./ -I ./librarie/libft/ -L ./librarie/libft/ -lft
LDFLAGS	=	-lreadline

CC	=	gcc
CFLAGS	=	-Wall -Wextra -Werror -lreadline

SRC_DIR		=	sources
SRC_FILES	=	minishell.c \
				cmd_output_line.c \
				split_minishell.c
SRC	=	$(addprefix $(SRC_DIR)/, $(SRC_FILES))

OBJ_DIR	=	objects
OBJ	=	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

FS	=	-g3

all:	$(NAME)

$(NAME):	$(LIBFT) $(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LINK) $(LDFLAGS) -o $(NAME) $(I_MINISHELL)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(FS) -c $< -o $@ $(I_OBJ) $(I_MINISHELL)

$(LIBFT):
	make -C $(PATH_LIBFT)

$(OBJ_DIR):
	mkdir objects

clean:
	rm -rf $(OBJ_DIR)
	make -C $(PATH_LIBFT) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(PATH_LIBFT) fclean

re:	fclean all

valgrind:
	make
	valgrind --leak-check=full ./minishell

.PHONY: all clean fclean re