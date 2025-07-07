/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:00:23 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/04 18:29:19 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_one_cmd
{
	char	*line;
	char	*cmd_path;
	char	**args;
	char	**envp;
	int		access_status;
	int		error;
}			t_cmd;

typedef struct s_shell_metadata
{
	t_cmd	*cmds;
	int		num_cmds;
	char	**envp;
}				t_shell;


int		ft_strcmp(const char *s1, const char *s2);
void	get_cmd_line(void);

#endif
