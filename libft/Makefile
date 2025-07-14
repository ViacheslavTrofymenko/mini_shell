# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/08 17:46:53 by vtrofyme          #+#    #+#              #
#    Updated: 2025/04/08 17:46:55 by vtrofyme         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Define variables
CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = libft.a

SRCS = \
	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
	ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
	ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c \
	ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c \
	ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c \
	ft_tolower.c ft_toupper.c

BONUS_SRCS = \
	ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c \
	ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

# List of object files
OBJS = $(SRCS:.c=.o)

# List of bonus object files
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

# The default rule is all, which compiles the library
all: $(NAME)

# Rule to create the library
$(NAME): $(OBJS)
	@echo "Creating library $(NAME)"
	@ar rcs $(NAME) $(OBJS)

# Bonus rule to add the bonus functions to library
bonus: $(OBJS) $(BONUS_OBJS)
	@echo "Adding bonus files to library $(NAME)"
	@ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)

# Compile the object files
%.o: %.c
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	@echo "Cleaning object files..."
	@rm -rf $(OBJS) $(BONUS_OBJS)

# Remove all generated files
fclean: clean
	@echo "Cleaning all generated files..."
	@rm -f $(NAME)
	@echo "Cleaned succesfully"

# Rebuild everything
re: fclean all

# Prevent unnecessary commands
.PHONY: all clean fclean re
# cc test_libft.c libft.h libft.a -lbsd
