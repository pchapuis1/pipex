/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchapuis <pchapuis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:20:25 by pchapuis          #+#    #+#             */
/*   Updated: 2023/02/14 16:06:00 by pchapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>

typedef struct s_env
{
	char	**argv;
	char	**envp;
}	t_env;

char	**ft_split(char const *s, char c);
int		ft_strlen(const char *str);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*find_path(char *cmd, char **envp);
int		error_launch(void);
void	error_cmd(char *cmd);
void	ft_free(char **tab);
int		close_fd(int *fd);
int		ft_strcmp(const char *s1, const char *s2);
int		direct_path(char **cmd, char **envp);

#endif