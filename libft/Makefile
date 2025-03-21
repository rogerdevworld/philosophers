# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmarrero <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/16 12:58:52 by rmarrero          #+#    #+#              #
#    Updated: 2025/02/19 16:29:30 by rmarrero         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- mandatory functions --- #
SRC = ft_isascii.c ft_memcpy.c ft_putstr_fd.c ft_strlcat.c ft_strrchr.c ft_atoi.c ft_isdigit.c\
ft_memmove.c ft_strlcpy.c ft_strtrim.c ft_bzero.c ft_isprint.c ft_memset.c ft_strchr.c \
ft_strlen.c ft_calloc.c ft_putchar_fd.c ft_strdup.c ft_strmapi.c ft_tolower.c ft_substr.c\
ft_isalnum.c ft_memchr.c ft_putendl_fd.c ft_striteri.c ft_strncmp.c ft_toupper.c ft_isalpha.c \
ft_memcmp.c ft_putnbr_fd.c   ft_strjoin.c ft_strnstr.c ft_split.c ft_itoa.c
OBJS = $(SRC:.c=.o)

# --- bonus functions --- #
BSRC = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c \
ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c get_next_line_utils.c\
get_next_line.c ft_printf.c ft_flags.c ft_printf_utils.c
BOBJS = $(BSRC:.c=.o)

# --- ft_printf functions --- #
# --- get_next_line functions --- #
# --- additional functions --- #
ADDSRC = ft_sqrt.c ft_atol.c ft_fabs.c ft_atof.c ft_strcmp.c ft_getenv.c
ADDOBJS = $(ADDSRC:.c=.o)

NAME = libft.a
HEADER = libft.h
CC = cc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f
AR = ar rsc

#color
RED     = \033[31m
GREEN   = \033[32m
YELLOW  = \033[33m
BLUE    = \033[34m
RESET   = \033[0m

#ifdef BONUS
OBJECTS = $(OBJS) $(BOBJS) $(ADDOBJS)

all: $(NAME)

$(NAME): $(OBJECTS)
	@echo "$(GREEN)Compilando...$(RESET)"
	$(AR) $(NAME) $?
	@echo "$(BLUE)"
	@echo "$(YELLOW)           ($(RESET)__$(YELLOW))\           $(RESET)"
	@echo "$(YELLOW)           ($(RESET)oo$(YELLOW))\\________  $(RESET)"
	@echo "$(RESET)           /|| \\        \\ $(RESET)"
	@echo "$(RESET)              ||------w | $(RESET)"
	@echo "$(RESET)              ||       || $(RESET)"
	@echo "$(YELLOW)THE COW MAKES MUUUUUUUUUU!$(RESET)"
	@echo "$(RESET)"

%.o: %.c $(HEADER) Makefile
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(BOBJS) $(ADDOBJS)

fclean: clean
	$(RM) -f $(NAME)
	
re: fclean all

.PHONY : all clean fclean re
