########################## VARIABLES ###############################

NAME			= minishell

BUILTIN_FOLDER	= ./builtins/
BUILTINS_BLANK	= echo cd pwd exit
SRCS_BUILTIN	= $(addsuffix .c, $(addprefix $(BUILTIN_FOLDER), $(BUILTINS_BLANK)))
SRCS_B 			= $(wildcard $(BUILTIN_FOLDER)*.c)
EXECS			 = $(patsubst $(BUILTIN_FOLDER)%.c,%,$(SRCS_B))

SRC_FOLDER		= ./src/
MAIN			= main
SRCS_BLANK		= prompt signal commands_1 path utils split split_utils parsing_1 \
				parsing_2 parsing_3 parsing_main syntax broken_pipe string env_variables \
				bags_1 bags_2 bags_main terminal commands_2

SRCS_NOMAIN		= $(addsuffix .c, $(addprefix $(SRC_FOLDER), $(SRCS_BLANK)))
SRCS			= $(SRCS_NOMAIN) $(addsuffix .c, $(addprefix $(SRC_FOLDER), $(MAIN)))

LIBFLAGS		= -L./libft -lft -L$(HOME)/.brew/opt/readline/lib -lreadline -ledit
BREWFLAGS		= -I$(HOME)/.brew/opt/readline/include
FLAGS			= -g -Wall -Wextra -Werror -fsanitize=address
ALLFLAGS		= $(FLAGS) $(LIBFLAGS) $(BREWFLAGS)

CC				= gcc

RM				= rm -f
RM_ALL			= rm -rf

TO_CLEAN		= *.dSYM *.o *test .vscode $(BUILTIN_FOLDER)/*.dSYM

########################## TARGETS ###############################

all: $(NAME) builtins run

$(NAME): $(SRCS)
	@$(CC) $(ALLFLAGS) $(SRCS) -o $@
	@echo "Compiling $(NAME)..."

test:
	@echo "Compiling test..."
	@$(CC) $(ALLFLAGS) $(SRCS_NOMAIN) -o $@

builtins: $(EXECS)
	@echo "Compiling builtins..."

%: $(BUILTIN_FOLDER)/%.c
	@$(CC) $(ALLFLAGS) -o $(BUILTIN_FOLDER)$@ $<

run:
	@./$(NAME)

%.o: %.c
	@echo compiling file $<...
	@$(CC) $(FLAGS) $< -o $@

clean:
	@$(RM_ALL) $(TO_CLEAN)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all run clean fclean re test libft

###################################################################