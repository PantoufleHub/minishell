########################## VARIABLES ###############################

NAME			= minishell

SRC_FOLDER		= ./src/
BUILTIN_FOLDER	= ./builtins/

MAIN			= main
SRCS_BLANK		= prompt signal commands_1 path utils split split_utils parsing_1 \
				parsing_2 parsing_3 parsing_main syntax broken_pipe string env_variables \
				bags_1 bags_2 bags_main terminal commands_2
BUILTINS_BLANK	= echo cd

SRCS_NOMAIN		= $(addsuffix .c, $(addprefix $(SRC_FOLDER), $(SRCS_BLANK)))
SRCS			= $(SRCS_NOMAIN) $(addsuffix .c, $(addprefix $(SRC_FOLDER), $(MAIN))) \
				$(addsuffix .c, $(addprefix $(BUILTIN_FOLDER), $(BUILTINS_BLANK)))

LIBFLAGS		= -L./libft -lft -L$(HOME)/.brew/opt/readline/lib -lreadline -ledit
BREWFLAGS		= -I$(HOME)/.brew/opt/readline/include
FLAGS			= -g -Wall -Wextra -Werror -fsanitize=address
ALLFLAGS		= $(FLAGS) $(LIBFLAGS) $(BREWFLAGS)

CC				= gcc

RM				= rm -f
RM_ALL			= rm -rf

TO_CLEAN		= *.dSYM *.o *test .vscode

########################## TARGETS ###############################

all: $(NAME) run

$(NAME): $(SRCS)
	$(CC) $(ALLFLAGS) $(SRCS) -o $@

test:
	@echo "Running test..."
	$(CC) $(ALLFLAGS) $(SRCS_NOMAIN) -o $@

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