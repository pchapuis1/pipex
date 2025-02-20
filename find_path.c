/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchapuis <pchapuis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 13:45:42 by pchapuis          #+#    #+#             */
/*   Updated: 2023/03/02 11:55:42 by pchapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	free_path(char **all_paths)
{
	int	i;

	i = 0;
	while (all_paths[i] != NULL)
	{
		free(all_paths[i]);
		i ++;
	}
	free(all_paths);
}

static char	*create_path(char *cmd, char *path_test)
{
	char	*path;
	char	*temp;

	temp = ft_strjoin(path_test, "/");
	if (!temp)
		return (NULL);
	path = ft_strjoin(temp, cmd);
	free(temp);
	if (!path)
		return (NULL);
	return (path);
}

char	*find_path(char *cmd, char **envp)
{
	char	**all_paths;
	char	*path;
	int		i;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == NULL)
		i ++;
	all_paths = ft_split(ft_strnstr(envp[i], "PATH", 4), ':');
	if (!all_paths)
		return (NULL);
	i = 0;
	while (all_paths[i])
	{
		path = create_path(cmd, all_paths[i]);
		if (!path)
			return (NULL);
		if (access(path, X_OK) == 0)
		{
			free_path(all_paths);
			return (path);
		}
		free(path);
		i ++;
	}
	return (free_path(all_paths), NULL);
}

int	direct_path(char **cmd, char **envp)
{
	int	i;
	int	fd;

	i = 0;
	while (!cmd[0][i] || cmd[0][i] != '/')
		i ++;
	if (!cmd[0][i + 1] || (cmd[0][i + 1] == '.' && !cmd[0][i + 2]))
		return (write(2, cmd[0], ft_strlen(cmd[0])),
			write(2, ": is a directory\n", 17), 1);
	fd = open(cmd[0], O_RDONLY);
	if (fd != -1 || access(cmd[0], X_OK) == 0)
	{
		if (execve(cmd[0], cmd, envp) == -1)
			return (write(2, cmd[0], ft_strlen(cmd[0])),
				write(2, ": is a directory\n", 17), ft_free(cmd), 1);
		return (0);
	}
	else
	{
		if (fd != -1)
			close(fd);
		return (perror(cmd[0]), ft_free(cmd), 1);
	}
}
