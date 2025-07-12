# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ikulik <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/04 13:34:13 by vtrofyme          #+#    #+#              #
#    Updated: 2025/07/12 17:33:15 by ikulik           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= minishell

SRC 		= minishell_main.c prompter.c basics.c parse_quotes.c cleaners.c\
			initializer.c parse_commands.c parse_arguments_1.c parse_arguments_2.c\


SRCSDIR		= src
OBJDIR		= obj
INCLUDE		= include

SRCS		= $(addprefix $(SRCSDIR)/, $(SRC))

OBJS		= $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))

CFLAGS = -Wall -Wextra -Werror -g
MFLAGS = -lreadline
INCLUDES	= -I$(INCLUDE)

RM = rm -f

all: $(NAME)

$(NAME): $(LIBRARY) $(OBJDIR) $(OBJS)
	cc $(OBJS) $(LIBRARY) $(INCLUDES) -lreadline -o $(NAME)

$(BONUSNAME): $(BONUSOBJS) $(LIBRARY)
	cc $(BONUSOBJS) $(LIBRARY) -o $(BONUSNAME)

$(OBJDIR)/%.o: $(SRCSDIR)/%.c
	cc $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	$(RM) $(OBJS) $(BONUSOBJS)

fclean: clean
	$(RM) $(NAME) $(BONUSNAME)

re: fclean all
