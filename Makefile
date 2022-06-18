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
				prompt.c \
				create_envp_list.c \
				extract_key_n_value.c \
				free_envp_list.c \
				parsing_n_exec.c \
				token_analysis.c \
				lexical_analysis.c \
				syntax_analysis.c \
				word_expansion.c \
				tild_expansion.c \
				quote_exapansion.c \
				assingment_expansion.c \
				handle_s_quote.c \
				handle_d_quotes.c \
				create_cmd_table.c \
				cmd_table.c \
				free_cmd_table.c \
				exec_cmds.c \
				treat_redirectsc.c \
				exec_here_doc.c \
				exec_redirects.c \
				validate_path.c \
				exec_child.c \
				built_ins.c \
				special_built_in.c \
				env.c \
				pwd.c \
				echo.c \
				cd.c \
				export.c \
				unset.c \
				exit.c \
				signal.c \
				count_line.c \
				len_subline.c \
				pre_assingment_expansion.c \
				pre_assingment_expansion_utils.c \
				clean_quotes.c \
				ft_str_check.c \
				ft_str_isnum.c \
				free_split.c

#system
#env
#parser
#expansions
#execs
#built_ins
#signals
#utils

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
	valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --track-origins=yes ./minishell

.PHONY: all clean fclean re