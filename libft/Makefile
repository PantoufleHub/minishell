# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aperron <aperron@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/11 21:19:28 by ncolomer          #+#    #+#              #
#    Updated: 2024/02/14 14:14:38 by aperron          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

###################### VARIABLES #########################

### PRINTF
PRINTF_FOLDER	= libft/ft_printf/
PRINTF_SRCS		= $(addprefix $(PRINTF_FOLDER), ft_printf.c utils.c write_functions.c)
PRINTF_OBJS		= $(PRINTF_SRCS:.c=.o)
###

### GET_NEXT_LINE
GNL_FOLDER		= libft/get_next_line/
GNL_SRCS		= $(addprefix $(GNL_FOLDER), get_next_line.c get_next_line_utils.c)
GNL_OBJS		= $(GNL_SRCS:.c=.o)
###

ADDONS			= $(PRINTF_SRCS) $(GNL_SRCS)
### BASE_FUNCTIONS
LFT_FOLDER		= libft/src/
SRCS_NPF		=	ft_isalnum.c ft_isprint.c ft_memcmp.c ft_putchar_fd.c ft_split.c \
					ft_strlcat.c ft_strncmp.c ft_substr.c ft_atoi.c ft_isalpha.c \
					ft_itoa.c ft_memcpy.c ft_putendl_fd.c ft_strchr.c ft_strlcpy.c \
					ft_strnstr.c ft_tolower.c ft_bzero.c ft_isascii.c ft_memmove.c \
					ft_putnbr_fd.c ft_strdup.c ft_strlen.c ft_strrchr.c ft_toupper.c \
					ft_calloc.c ft_isdigit.c ft_memchr.c  ft_memset.c ft_putstr_fd.c  \
					ft_strjoin.c ft_strmapi.c ft_strtrim.c ft_striteri.c ft_strrev.c \
					ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c \
					ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c
LFT_SRCS		= $(addprefix $(LFT_FOLDER), $(SRCS_NPF)) $(ADDONS)
LFT_OBJS		= $(LFT_SRCS:.c=.o)
###

CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -I.

LFT_NAME		= libft/libft.a

###################### TARGETS ###########################

all:			$(LFT_NAME)

$(LFT_NAME):	 $(LFT_OBJS)
				ar rcs -w $(LFT_NAME) $(LFT_OBJS)

%.o: 			%.c
				$(CC) -w $(CFLAGS) -c -o $@ $<

# clean:
# 				$(RM) $(LFT_OBJS) 

# fclean:		clean
# 				$(RM) $(LFT_NAME)

re:			fclean $(LFT_NAME)

.PHONY:			all clean fclean re bonus libft

###########################################################