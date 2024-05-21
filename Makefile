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
CFLAGS				= -Wall -Werror -Wextra -I
RM					= rm -f

# Source Files
MAIN_DIR			=	$(SRC_DIR)main.c

UTILS_DIR			=	$(SRC_DIR)utils/utils.c

# Concatenate all source files
SRCS 				= $(UTILS_DIR) $(MAIN_DIR)

# Apply the pattern substitution to each source file in SRC and produce a corresponding list of object files in the OBJ_DIR
OBJ 				= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

# Specify the readline directory and library
READLINE_DIR		= /usr
READLINE_LIB 		= -lreadline -lhistory -L $(READLINE_DIR)/lib

# Build rules
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