/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 22:17:05 by djang             #+#    #+#             */
/*   Updated: 2025/05/25 22:17:06 by djang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	write_heredoc_content(int write_fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, delimiter))
		{
			free(line);
			break ;
		}
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
}

void	create_temp_file(int read_fd, char **file_path)
{
	int		fd;
	char	buffer[4096];
	int		bytes_read;

	free(*file_path);
	*file_path = ft_strdup("/tmp/heredoc_tmp");
	fd = open(*file_path, O_RDWR | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
	{
		perror("open");
		close(read_fd);
		return ;
	}
	bytes_read = read(read_fd, buffer, sizeof(buffer));
	while (bytes_read > 0)
	{
		write(fd, buffer, bytes_read);
		bytes_read = read(read_fd, buffer, sizeof(buffer));
	}
	close(read_fd);
	close(fd);
	unlink(*file_path);
}

void	process_heredoc_redir(t_redir *r)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) < 0)
	{
		perror("pipe");
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
		write_heredoc_content(pipefd[1], r->file);
		close(pipefd[1]);
		exit(0);
	}
	else
	{
		close(pipefd[1]);
		waitpid(pid, NULL, 0);
		create_temp_file(pipefd[0], &r->file);
		r->type = TK_REDIR_IN;
	}
}

void	handle_heredoc(t_cmd *cmd)
{
	t_redir	*r;

	r = cmd->redir;
	while (r)
	{
		if (r->type == TK_HEREDOC)
			process_heredoc_redir(r);
		r = r->next;
	}
}
