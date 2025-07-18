/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredocs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:31:53 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/07/18 11:54:43 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_single_heredoc(t_shell *shell, int i, int j);

void	handle_heredocs(t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	while (i < shell->num_cmds)
	{
		j = 0;
		while (j < shell->cmds[i].num_files)
		{
			if (shell->cmds[i].rw_type[j] == IO_INPUT && shell->cmds[i].f_mode[j] == IO_DOUBLE)
				process_single_heredoc(shell, i, j);
			j++;
		}
		i++;
	}
}

static void	process_single_heredoc(t_shell *shell, int i, int j)
{
	int		fd;
	char	*tmp_filename;
	char	*line;
	char	*delimiter;

	delimiter = shell->cmds[i].f_names[j];
	tmp_filename = ft_strjoin("/tmp/.heredoc_", delimiter);
	fd = open(tmp_filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		crit_except(shell, ft_error(1, tmp_filename));
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
	close(fd);
	free(shell->cmds[i].f_names[j]);
	shell->cmds[i].f_names[j] = tmp_filename;
}
