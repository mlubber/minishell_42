# Name
NAME				= minishell

# Directories
LIBFT				= ./libraries/libft/libft.a
INC					= include/
SRC_DIR				= sources/
BLD_DIR				= build/
OBJ_DIR				= ./build/objects/

# Compiler and CFlags
CC					= cc
CFLAGS				= -Wall -Werror -Wextra -I #-g -fsanitize=address
RM					= rm -f

# Source Files
MAIN_DIR			=	$(SRC_DIR)main.c

ENV_DIR				=	$(SRC_DIR)env/building_env.c \
						$(SRC_DIR)env/create_env_node.c

SHELL_DIR			=	$(SRC_DIR)shell/ft_minishell_loop.c

PARSER_DIR			=	$(SRC_DIR)parser/input_checker.c \
						$(SRC_DIR)parser/parse_input.c \
						$(SRC_DIR)parser/parse_files.c \
						$(SRC_DIR)parser/parse_cmd.c \
						$(SRC_DIR)parser/get_wordlength.c \
						$(SRC_DIR)parser/copy_word.c \
						$(SRC_DIR)parser/parsing_utils.c

EXEC_DIR			=	$(SRC_DIR)exec/executor.c \
						$(SRC_DIR)exec/handling_redirs.c \
						$(SRC_DIR)exec/pipex_part.c

BUILTINS_DIR		=	$(SRC_DIR)builtins/ft_mini_echo.c \
						$(SRC_DIR)builtins/ft_mini_cd.c \
						$(SRC_DIR)builtins/ft_mini_pwd.c \
						$(SRC_DIR)builtins/ft_mini_export.c \
						$(SRC_DIR)builtins/ft_mini_unset.c \
						$(SRC_DIR)builtins/ft_mini_env.c \
						$(SRC_DIR)builtins/ft_mini_exit.c

UTILS_DIR			=	$(SRC_DIR)utils/ft_utils.c \
						$(SRC_DIR)utils/kill_program.c \
						$(SRC_DIR)utils/free_cmd_list.c

# Concatenate all source files
SRCS 				= $(MAIN_DIR) $(ENV_DIR) $(LEXER_DIR) $(SHELL_DIR) $(PARSER_DIR) $(EXEC_DIR) $(BUILTINS_DIR) $(UTILS_DIR) 

# Apply the pattern substitution to each source file in SRC and produce a corresponding list of object files in the OBJ_DIR
OBJ 				= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

# Specify the readline directory and library
READLINE_DIR		= /usr
READLINE_LIB 		= -lreadline -lhistory -L $(READLINE_DIR)/lib

# Build rules
start:
					@make all

$(LIBFT):
					@make -C ./libraries/libft

all: 				$(NAME)

$(NAME): 			$(OBJ) $(LIBFT)
					@$(CC) $(CFLAGS) $(INC) $(OBJ) $(LIBFT) $(READLINE_LIB) -o $(NAME)

# Compile object files from source files
$(OBJ_DIR)%.o:		$(SRC_DIR)%.c 
					@echo "Compiling ${notdir $<}"
					@mkdir -p $(@D)
					@$(CC) $(CFLAGS) $(INC) -c $< -o $@

# Cleanups
clean:
					@echo "Cleaning..."
					@$(RM) -r $(OBJ_DIR)
					@$(RM) -r $(BLD_DIR)
					@make clean -C ./libraries/libft

fclean: 			clean
					@$(RM) $(NAME)
					@$(RM) $(LIBFT)
					@echo "All clean"

re: 				fclean all

# Phony targets represent actions not files
.PHONY: 			start all clean fclean re