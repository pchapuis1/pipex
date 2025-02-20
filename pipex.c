/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchapuis <pchapuis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:36:44 by pchapuis          #+#    #+#             */
/*   Updated: 2023/03/02 11:57:19 by pchapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	swap_fd(int *fd, int *pipefd, int fd_value, int pipefd_value)
{
	if (close(pipefd[fd_value]) != 0)
		return (perror("Close"), 1);
	if (dup2(fd[fd_value], fd_value) == -1)
		return (perror("Dup2"), 1);
	if (dup2(pipefd[pipefd_value], pipefd_value) == -1)
		return (perror("Dup2"), 1);
	if (close(fd[fd_value]) != 0)
		return (perror("Close"), 1);
	if (close(pipefd[pipefd_value]) != 0)
		return (perror("Close"), 1);
	return (0);
}

static int	exec_cmd(char *argv, char **envp)
{
	char	**cmd;
	char	*path;

	if (!argv[0])
		return (error_cmd(argv), 1);
	cmd = ft_split(argv, ' ');
	if (!cmd)
		return (1);
	if (!cmd[0])
		return (ft_free(cmd), 1);
	if (ft_strnstr(cmd[0], "/", ft_strlen(cmd[0])))
		return (direct_path(cmd, envp));
	path = find_path(cmd[0], envp);
	if (path)
	{
		if (execve(find_path(cmd[0], envp), cmd, envp) == -1)
			return (perror("execve"), free(path), ft_free(cmd), 1);
	}
	else
		return (error_cmd(cmd[0]), ft_free(cmd), 1);
	free(path);
	ft_free(cmd);
	return (0);
}

static int	read_branch(int *fd, int *pipefd, t_env env)
{
	pid_t	read_process;

	read_process = fork();
	if (read_process == -1)
		return (perror("Fork"), 1);
	if (read_process == 0)
	{
		fd[0] = open(env.argv[1], O_RDONLY);
		if (fd[0] == -1)
			return (perror(env.argv[1]), close_fd(pipefd), 1);
		if (swap_fd(fd, pipefd, 0, 1) == 1)
			return (1);
		if (exec_cmd(env.argv[2], env.envp) == 1)
			return (1);
	}
	return (0);
}

static int	write_branch(int *fd, int *pipefd, t_env env)
{
	pid_t	write_process;

	write_process = fork();
	if (write_process == -1)
		return (perror("Fork"), 1);
	if (write_process == 0)
	{
		fd[1] = open(env.argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd[1] == -1)
			return (perror(env.argv[4]), close_fd(pipefd), 1);
		if (swap_fd(fd, pipefd, 1, 0) == 1)
			return (1);
		if (exec_cmd(env.argv[3], env.envp) == 1)
			return (1);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int		pipefd[2];
	int		fd[2];
	t_env	env;

	env.argv = argv;
	env.envp = envp;
	if (argc != 5)
		return (error_launch());
	if (pipe(pipefd) == -1)
		return (perror("Pipe"), 1);
	if (read_branch(fd, pipefd, env) == 1)
		return (1);
	if (write_branch(fd, pipefd, env) == 1)
		return (1);
	if (close_fd(pipefd) == 1)
		return (1);
	waitpid(-1, NULL, 0);
	waitpid(-1, NULL, 0);
	return (0);
}
