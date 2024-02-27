########################## VARIABLES ###############################

NAME		= minishell

SRC_FOLDER	= ./src/

SRCS_BLANK	= main prompt signal command path utils split split_utils

SRCS		= $(addsuffix .c, $(addprefix $(SRC_FOLDER), $(SRCS_BLANK)))

FLAGS		= -g -Wall -Wextra -Werror -fsanitize=address
LIBFLAGS	= -L./libft -lft -lreadline -ledit

CC			= gcc

RM			= rm -f
RM_ALL		= rm -drf

TO_CLEAN	= *.dSYM *.o *test

########################## TARGETS ###############################

all: $(NAME) run

$(NAME): $(SRCS)
	$(CC) $(FLAGS) $(SRCS) $(LIBFLAGS) -o $@

test:
	@echo "Running test..."
	$(CC) -g -Wextra -Wall $(SRCS) $(LIBFLAGS) -o $@
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