# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/04 13:34:13 by vtrofyme          #+#    #+#              #
#    Updated: 2025/07/14 13:44:07 by vtrofyme         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= minishell

SRC 		= minishell_main.c prompter.c basics.c initializer.c cleaners.c\
			exceptors.c parse_quotes.c parse_split_command.c parse_stream_names.c\
			parse_arguments.c			execute.c


SRCSDIR		= src
OBJDIR		= obj
INCLUDE		= include

SRCS		= $(addprefix $(SRCSDIR)/, $(SRC))

OBJS		= $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))

CFLAGS		= -Wall -Wextra -Werror -g
MFLAGS		= -lreadline
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
