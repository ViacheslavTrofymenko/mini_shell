/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:00:23 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/11 20:05:32 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# define Q_M_CHECK 0
# define Q_M_WRITE 1
# define Q_NORMAL ' '
# define Q_SINGLE '\''
# define Q_DOUBLE '\"'
# define PIPE '|'
# define ER_MALLOC 2

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct s_one_cmd
{
	char	*line;
	char	*q_type;
	char	*cmd_path;
	char	**args;
	char	**splits;
	char	*split_type;
	char	**envp;
	int		access_status;
	int		num_args;
	int		ind_arg;
	int		ind_start;
	int		len;
	int		num_splits;
	int		error;
}			t_cmd;

typedef struct s_quote_parser
{
	int		q_flag;
	int		ind_strt;
	int		ind_line;
	char	*str;
	char	*q_marker_str;
}			t_qoutes;

typedef struct s_shell_metadata
{
	t_cmd		*cmds;
	t_qoutes	qts;
	int			num_cmds;
	char		**envp;
}				t_shell;

int		ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
void	*ft_memset(void *s, char c, size_t n);
size_t	ft_strlen(const char *s);
int		ft_is_space(char c);
void	ft_intset(int	*arr, int c, int n);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void *));
t_list	*ft_lstnew(void *content);
void	get_cmd_line(t_shell *shell);
void	mark_quotes(t_shell *shell, char *str);
void	crit_except(t_shell *data, int error_code);
void	initialize_shell(t_shell *shell, char **envp);
void	initialize_cmds(t_shell *shell);
void	nullify_array(char	**arr, int size);
void	create_cmd_vars(t_shell *shell, char *str);
void	count_splits(t_shell *shell, t_cmd *cmd);
void	cmd_split(t_shell *shell, t_cmd *cmd);

#endif
