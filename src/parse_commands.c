/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:40:47 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/08 19:52:55 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_cmd_to_lst(t_shell *shell, char *str, int index, int *ind_start);

/* char	***parse_commands(t_shell *shell, char *str)
{
	parse_quotes(shell, str);

} */

int	ft_is_space(char c)
{
	if (c == ' ' || (9 <= c && c <= 13))
		return (1);
	return (0);
}

void	find_pipes(t_shell *shell, char *str)
{
	int	index;
	int	ind_start;

	index = 0;
	ind_start = 0;
	while (str[index])
	{
		if ((str[index] == PIPE && shell->qts.q_marker_str[index] == Q_NORMAL)
			|| (str[index + 1] == '\0' && ind_start < index))
			add_cmd_to_lst(shell, str, index, &ind_start);
		index++;
	}
}

void	add_cmd_to_lst(t_shell *shell, char *str, int index, int *ind_start)
{
	t_cmd	*cmd;
	t_list	*lst;

	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
		crit_except(shell, EXIT_FAILURE);
	cmd->line = malloc ((index - *ind_start + 1) * sizeof(char));
	cmd->q_type = malloc ((index - *ind_start + 1) * sizeof(char));
	if (cmd->line == NULL || cmd->q_type == NULL)
		crit_except(shell, EXIT_FAILURE);
	ft_strlcpy(cmd->line, &(str[*ind_start]), index - *ind_start + 1);
	ft_strlcpy(cmd->q_type, &(shell->qts.q_marker_str[*ind_start]),
		index - *ind_start + 1);
	lst = ft_lstnew((void *)cmd);
	if (lst == NULL)
		crit_except(shell, EXIT_FAILURE);
	ft_lstadd_back(&(shell->cmds), lst);
	*ind_start = index + 1;
}


