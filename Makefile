# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/04 13:34:13 by vtrofyme          #+#    #+#              #
#    Updated: 2025/07/18 10:40:37 by vtrofyme         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= minishell

SRC 		= minishell_main.c prompter.c basics_simple.c initializer.c cleaners.c\
			exceptors.c parse_quotes.c parse_cmd.c parse_stream_names.c\
			parse_pipes.c parse_split_cmd.c parse_dollar.c basics_variables.c\
			execute/execute.c execute/execute_utils.c execute/handle_heredocs.c\
			execute/apply_redirections.c execute/exec_pipe_cmds.c\

SRCSDIR		= src
OBJDIR		= obj
INCLUDE		= include

SRCS		= $(addprefix $(SRCSDIR)/, $(SRC))

OBJS		= $(SRCS:src/%.c=obj/%.o)

CFLAGS		= -Wall -Wextra -Werror -g
MFLAGS		= -lreadline
INCLUDES	= -I$(INCLUDE)

RM = rm -rf

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJS)
	$(MAKE) -C libft
	cc $(OBJS) $(LIBRARY) $(INCLUDES) -lreadline -L libft -lft -o $(NAME)

$(OBJDIR)/%.o: $(SRCSDIR)/%.c
	@mkdir -p $(dir $@)
	cc $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	$(MAKE) -C libft clean
	$(RM) $(OBJDIR)

fclean: clean
	$(MAKE) -C libft fclean
	$(RM) $(NAME)

re: fclean all
