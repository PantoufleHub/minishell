########################## VARIABLES ###############################

NAME		= minishell

SRC_FOLDER	= ./src/

SRCS_BLANK	= main prompt signal command path utils split split_utils parsing_1 \
			parsing_2 parsing_3 parsing_main syntax broken_pipe

SRCS		= $(addsuffix .c, $(addprefix $(SRC_FOLDER), $(SRCS_BLANK)))

LIBFLAGS	= -L./libft -lft -L$(HOME)/.brew/opt/readline/lib -lreadline -ledit
BREWFLAGS	= -I$(HOME)/.brew/opt/readline/include
FLAGS		= -g -Wall -Wextra -Werror -fsanitize=address $(LIBFLAGS) $(BREWFLAGS)
ALLFLAGS	= $(FLAGS) $(LIBFLAGS) $(BREWFLAGS)

CC			= gcc

RM			= rm -f
RM_ALL		= rm -rf

TO_CLEAN	= *.dSYM *.o *test .vscode

########################## TARGETS ###############################

all: $(NAME) run

$(NAME): $(SRCS)
	$(CC) $(ALLFLAGS) $(SRCS) -o $@

test:
	@echo "Running test..."
	$(CC) -g -Wextra -Wall $(SRCS) -o $@
	@./$@

run:
	@./$(NAME)

%.o: %.c
	@echo compiling file $<...
	$(CC) $(FLAGS) $< -o $@

clean:
	@$(RM_ALL) $(TO_CLEAN)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all run clean fclean re test libft

###################################################################