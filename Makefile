# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bkuksa <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/02 12:38:05 by bkuksa            #+#    #+#              #
#    Updated: 2019/10/02 12:38:07 by bkuksa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SRC_NAME = main.c help.c mod.c imag.c grad.c
OBJ_NAME = $(SRC_NAME:.c=.o)

SRCDIR = srcs
OBJDIR = objs

CC = gcc
CFLAGS = -Wall -Werror -Wextra

INC = -I includes -I libft

LIBS = -L libft -lft -lm -lmlx -framework OpenGL -framework AppKit

SRC = $(addprefix $(SRCDIR)/, $(SRC_NAME))
OBJ = $(addprefix $(OBJDIR)/, $(OBJ_NAME))

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft
	@$(CC) $(LIBS) $^ -o $@
	@echo "\033[1;33m--FDF Built And Ready--\033[m"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c $(INC) $< -o $@

clean:
	@make -C libft clean
	@rm -f $(OBJ)
ifneq ($(OBJDIR), ./)
	@rm -rf $(OBJDIR)
endif
	@echo "\033[1;33mClean Objs:    OK!\033[m"

fclean: clean
	@make -C libft fclean
	@rm -f $(NAME)
	@echo "\033[1;33mFclean FDF:    OK!\033[m"

re: fclean all

.PHONY: all, clean, fclean, re
