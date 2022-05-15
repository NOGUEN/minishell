CC 				= gcc
RM				= rm -rf
CFLAGS 			= -Wall -Wextra -Werror
NAME 			= minishell

LIBFT		= libft.a
LIBFT_DIR	= libft

#READLINE_LIB 	= -lreadline -L/usr/local/opt/readline/lib
#READLINE_INC	= -I/usr/local/opt/readline/include

READLINE_LIB 	= -lreadline -L /Users/$(USER)/.brew/opt/readline/lib
READLINE_INC	= -I /Users/$(USER)/.brew/opt/readline/include

#READLINE_LIB	= -lreadline -L/opt/homebrew/opt/readline/lib
#READLINE_INC	= -I/opt/homebrew/opt/readline/include

SRC_DIR 		= src
PARSE_PATH		= src/parse/
BUILTIN_PATH	= src/built_in/
UTILS_PATH		= src/utils/
GNL_PATH		= src/get_next_line/

PARSE			= alloc_token.c			\
				  alloc_word.c			\
				  alloc_env.c			\
				  check.c				\
				  find_cmdpath.c		\
				  get_env.c				\
				  get_parse_size.c		\
				  new_cmd.c				\
				  parse.c				\
				  quote_count.c			\
				  split_cmd.c			\
				  split_count.c			\
				  utils.c				\

BUILTIN			= unset.c				\
				  exit.c				\
				  export.c				\
				  export_utils.c		\
				  env.c					\
				  cd.c					\

UTILS			= util1.c				\
				  util2.c				\

GNL				= get_next_line.c		\
				  get_next_line_utils.c	\

MAIN			= minishell.c			\
				  signal.c				\
				  exec.c				\
				  cmd_info.c			\

SRC 			= $(addprefix $(PARSE_PATH), $(PARSE))		\
				  $(addprefix $(BUILTIN_PATH), $(BUILTIN))	\
				  $(addprefix $(UTILS_PATH), $(UTILS))		\
				  $(addprefix $(GNL_PATH), $(GNL))			\
				  $(addprefix src/, $(MAIN))				\

OBJ_DIR 		= objs
OBJ 			= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all : 		$(NAME)

$(NAME) : 	$(LIBFT) $(OBJ)
			@$(CC) $(CFLAGS) -o $@ $(OBJ) $(READLINE_LIB) $(READLINE_INC)\
			$(LIBFT)

$(LIBFT) :
			@cd $(LIBFT_DIR); make
			@cp $(LIBFT_DIR)/$(LIBFT) ./

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
			@mkdir -p $(OBJ_DIR)/built_in
			@mkdir -p $(OBJ_DIR)/parse
			@mkdir -p $(OBJ_DIR)/utils
			@mkdir -p $(OBJ_DIR)/get_next_line
			@$(CC) $(CFLAGS) -c $< -o $(<:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o) \
			$(READLINE_INC)

clean :
			@cd $(LIBFT_DIR); make clean
			@$(RM) $(OBJ) $(OBJ_DIR)

fclean : 	clean
			@cd $(LIBFT_DIR); make fclean
			@$(RM) $(NAME) $(LIBFT)

re : 		fclean all

.PHONY :	all clean fclean
