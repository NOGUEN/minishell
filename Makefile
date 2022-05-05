CC 				= gcc -g
RM				= rm -rf
CFLAGS 			= -Wall -Wextra -Werror
NAME 			= minishell

LIBFT		= libft.a
LIBFT_DIR	= libft

READLINE_LIB	= -lreadline -L/opt/homebrew/opt/readline/lib
READLINE_INC	= -I/opt/homebrew/opt/readline/include

SRC_DIR 	= src
SRC 		= src/alloc_token.c \
			  src/alloc_word.c \
			  src/check.c \
			  src/get_env.c \
			  src/get_parse_size.c \
			  src/minishell.c \
			  src/new_cmd.c \
			  src/parse.c \
			  src/quote_count.c \
			  src/signal.c \
			  src/split_cmd.c \
			  src/split_count.c \
			  src/utils.c		\
			  src/exec.c		\
			  src/inout.c		\
			  src/utils/util1.c	\
			  src/utils/util2.c	\
			  src/get_next_line/get_next_line.c\
			  src/get_next_line/get_next_line_utils.c

OBJ_DIR 	= objs
OBJ 		= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all : 		$(NAME)

$(NAME) : 	$(LIBFT) $(OBJ)
			$(CC) -o $@ $(OBJ) $(READLINE_LIB) $(READLINE_INC)\
			$(LIBFT)
			

$(LIBFT) :
			cd $(LIBFT_DIR); make
			cp $(LIBFT_DIR)/$(LIBFT) ./

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
			mkdir -p $(OBJ_DIR)
			mkdir -p $(OBJ_DIR)/utils
			mkdir -p $(OBJ_DIR)/get_next_line
			$(CC) -c $< -o $(<:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o) \
			$(READLINE_INC)

clean :
			cd $(LIBFT_DIR); make clean
			$(RM) $(OBJ) $(OBJ_DIR)

fclean : 	clean
			cd $(LIBFT_DIR); make fclean
			$(RM) $(NAME) $(LIBFT)

re : 		fclean all

.PHONY :	all clean fclean
