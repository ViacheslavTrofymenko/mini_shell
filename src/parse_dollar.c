/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 22:17:37 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/13 22:17:37 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
void	expand_dollars(t_shell *shell, t_cmd_p *cmd)
{
	char	*temp;
	int		index;

	index = 0;
	temp = cmd->line;
	while (cmd->line[index])
	{
		if (cmd->line[index] == Q_DOLLAR && cmd->q_type[index] != Q_SINGLE)
			replace_variable(shell, cmd, cmd->line, index);

		index++;
	}
}

void	replace_variable(t_shell *shell, t_cmd_p *cmd, char *str, int start)
{
	int		index;
	int		len;
	char	*find;

	index = start + 1;
	len = 1;
	find = NULL;
	if (ft_isdigit(str[index]) == 0)
	{
		while (ft_isalnum_(cmd->line[index]))
		{
			index++;
			len++;
		}
		find = find_var_in_env(shell->envp, &(str[index]), len);
	}
	if (len > 0)
}

char	*find_var_in_env(char **env, char *find, int len)
{
	int	index;

	index = 0;
	if (env == NULL)
		return (NULL);
	while (env[index])
	{
		if (ft_strncmp(env[index], find, len) == 0)
		{
			if (env[len] == '=')
				return (env[len + 1]);
		}
		index++;
	}
}*/