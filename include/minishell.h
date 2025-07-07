/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:00:23 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/07 17:01:03 by ikulik           ###   ########.fr       */
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
# define Q_SINGLE '3'
# define Q_DOUBLE '4'

typedef struct s_one_cmd
{
	char	*line;
	char	*cmd_path;
	char	**args;
	char	**envp;
	int		access_status;
	int		error;
}			t_cmd;

typedef struct s_quote_parser
{
	int		q_flag;
	int		ind_strt;
	int		num_splits;
	int		ind_line;
	char	*str;
	char	**result;
	char	*types;
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
void	get_cmd_line(void);
char	**parse_quotes(t_shell *shell, char *str);
void	crit_except(t_shell *data, int error_code);

#endif
