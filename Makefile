# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/04 13:34:13 by vtrofyme          #+#    #+#              #
#    Updated: 2025/07/14 12:35:07 by vtrofyme         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= minishell

SRC 		= minishell_main.c prompter.c basics.c parse_quotes.c cleaners.c\
			initializer.c parse_commands.c parse_arguments_1.c parse_arguments_2.c\
			execute.c


SRCSDIR		= src
OBJDIR		= obj
INCLUDE		= include

SRCS		= $(addprefix $(SRCSDIR)/, $(SRC))

OBJS		= $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))

CFLAGS = -Wall -Werror -Wextra -g3
MFLAGS = -lreadline
INCLUDES	= -I$(INCLUDE)

RM = rm -f

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJS)
	$(MAKE) -C libft
	cc $(OBJS) $(LIBRARY) $(INCLUDES) -lreadline -L libft -lft -o $(NAME)

$(OBJDIR)/%.o: $(SRCSDIR)/%.c
	cc $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	$(MAKE) -C libft clean
	$(RM) $(OBJS) $(BONUSOBJS)

fclean: clean
	$(MAKE) -C libft fclean
	$(RM) $(NAME) $(BONUSNAME)

re: fclean all
