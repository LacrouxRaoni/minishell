NAME		= minishell

PATH_LIBFT	= ./librarie/libft
LIBFT		= $(PATH_LIBFT)/libft.a

SRC_DIR		= sources
PATH_OBJ	= objects

BUILTIN		= built_ins/
ENVP		= envp/
EXEC		= execs/
EXPANSION	= expansions/
PARSER		= parser/
SIGNAL		= signals/
SYSTEM		= system/
UTILS		= utils/

HEADERS		= include/minishell.h

CC			= gcc
RM			= rm -rf
# LEAK		= -fsanitize=address
# CFLAGS		= -Wall -Wextra -Werror -lreadline


SRC_FILES	=	$(SYSTEM)minishell.c \
				$(SYSTEM)prompt.c \
				$(ENVP)create_envp_list.c \
				$(UTILS)extract_key_n_value.c \
				$(ENVP)free_envp_list.c \
				$(PARSER)parsing_n_exec.c \
				$(PARSER)token_analysis.c \
				$(PARSER)lexical_analysis.c \
				$(PARSER)syntax_analysis.c \
				$(EXPANSION)word_expansion.c \
				$(EXPANSION)tild_expansion.c \
				$(EXPANSION)quote_expansion.c \
				$(EXPANSION)assingment_expansion.c \
				$(EXPANSION)handle_s_quote.c \
				$(EXPANSION)handle_d_quotes.c \
				$(EXEC)create_cmd_table.c \
				$(EXEC)cmd_table.c \
				$(EXEC)free_cmd_table.c \
				$(EXEC)exec_cmds.c \
				$(EXEC)treat_redirectsc.c \
				$(EXEC)exec_here_doc.c \
				$(EXEC)exec_redirects.c \
				$(EXEC)validate_path.c \
				$(EXEC)exec_child.c \
				$(BUILTIN)built_ins.c \
				$(BUILTIN)special_built_in.c \
				$(BUILTIN)env.c \
				$(BUILTIN)pwd.c \
				$(BUILTIN)echo.c \
				$(BUILTIN)cd.c \
				$(BUILTIN)export.c \
				$(BUILTIN)unset.c \
				$(BUILTIN)exit.c \
				$(SIGNAL)signal.c \
				$(UTILS)count_line.c \
				$(UTILS)len_subline.c \
				$(UTILS)pre_assingment_expansion.c \
				$(UTILS)pre_assingment_expansion_utils.c \
				$(UTILS)clean_quotes.c \
				$(UTILS)ft_str_check.c \
				$(UTILS)ft_str_isnum.c \
				$(UTILS)free_split.c

SRC 		= $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ			= $(SRC:$(SRC_DIR)/%.c=$(PATH_OBJ)/%.o)

NAME		= minishell

all: make_libft $(NAME)

$(NAME): $(OBJ)
	@echo done!!
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LEAK) -lreadline -g -o $(NAME)

$(PATH_OBJ)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(PATH_OBJ)
	@mkdir -p $(PATH_OBJ)/$(BUILTIN)
	@mkdir -p $(PATH_OBJ)/$(ENVP)
	@mkdir -p $(PATH_OBJ)/$(EXEC)
	@mkdir -p $(PATH_OBJ)/$(EXPANSION)
	@mkdir -p $(PATH_OBJ)/$(PARSER)
	@mkdir -p $(PATH_OBJ)/$(SIGNAL)
	@mkdir -p $(PATH_OBJ)/$(SYSTEM)
	@mkdir -p $(PATH_OBJ)/$(UTILS)
	$(CC) -g $(CFLAGS) -c -Iincludes -o $@ $<

make_libft:
	@make -C $(PATH_LIBFT)

clean:
	@$(RM) $(PATH_OBJ)
	@make -C $(PATH_LIBFT) clean
	@echo obj removed!

fclean: clean
	@$(RM) $(NAME)
	@make -C $(PATH_LIBFT) clean fclean
	@echo clean everything

re: fclean all

valgrind:
	make
	valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --track-origins=yes ./minishell

.PHONY: all clean fclean re