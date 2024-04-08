########################## VARIABLES ###############################

NAME			= minishell

SRC_FOLDER		= ./src/
MAIN			= main
SRCS_BLANK		= prompt signal commands_1 path utils  parsing_1 echo \
				parsing_2 parsing_3 parsing_main syntax broken_pipe string env_variables \
				bags_1 bags_2 bags_main terminal commands_2 cd pwd exit commands_builtins \
				shell export export_utils env unset commands_3 clean clean_2 here_doc \
				syntax_2 here_doc_2 bags_3 bloodyquotes cd_2
				

SRCS_NOMAIN		= $(addsuffix .c, $(addprefix $(SRC_FOLDER), $(SRCS_BLANK)))
SRCS			= $(SRCS_NOMAIN) $(addsuffix .c, $(addprefix $(SRC_FOLDER), $(MAIN)))

LIBFLAGS		= -L./libft -lft -L$(HOME)/.brew/opt/readline/lib -lreadline -ledit -fsanitize=address
BREWFLAGS		= -I$(HOME)/.brew/opt/readline/include
FLAGS			= -g -Wall -Wextra -Werror 
ALLFLAGS		= $(FLAGS) $(LIBFLAGS) $(BREWFLAGS)

CC				= gcc

RM				= rm -f
RM_ALL			= rm -rf

TO_CLEAN		= *.dSYM *.o *test .vscode

########################## TARGETS ###############################

all: $(NAME) run

$(NAME): $(SRCS)
	make -C libft
	@$(CC) $(ALLFLAGS) $(SRCS) -o $@
	@echo "Compiling $(NAME)..."

test:
	@echo "Compiling test..."
	@$(CC) $(ALLFLAGS) $(SRCS_NOMAIN) -o $@

%: $(BUILTIN_FOLDER)/%.c
	@$(CC) $(ALLFLAGS) -o $(BUILTIN_FOLDER)$@ $<

run:
	@./$(NAME)

%.o: %.c
	@echo compiling file $<...
	@$(CC) $(FLAGS) $< -o $@

clean:
	make clean -C libft
	@$(RM_ALL) $(TO_CLEAN)

fclean: clean
	make fclean -C libft
	@$(RM) $(NAME)

re: fclean all

.PHONY: all run clean fclean re test libft

###################################################################