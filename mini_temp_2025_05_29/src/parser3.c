/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 22:19:40 by djang             #+#    #+#             */
/*   Updated: 2025/05/25 22:19:41 by djang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_cmd_list(t_cmd *cmd)
{
	t_cmd	*tmp;
	t_redir	*rtmp;
	int		i;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->argv)
		{
			i = 0;
			while (cmd->argv[i])
				free(cmd->argv[i++]);
			free(cmd->argv);
		}
		while (cmd->redir)
		{
			rtmp = cmd->redir->next;
			free(cmd->redir->file);
			free(cmd->redir);
			cmd->redir = rtmp;
		}
		free(cmd);
		cmd = tmp;
	}
}

//void free_cmd_list(t_cmd *cmd)
//{
//    t_cmd *tmp;
//    t_redir *rtmp;
//    int i;
    
//    while (cmd)
//    {
//        tmp = cmd->next;
//        if (cmd->argv)
//        {
//            i = 0;
//            while (cmd->argv[i])
//                free(cmd->argv[i++]);
//            free(cmd->argv);
//        }
        
//        while (cmd->redir)
//        {
//            rtmp = cmd->redir->next;
//            if (cmd->redir->file)
//            {
//                // 히어독 임시 파일이면 삭제
//                if (ft_strncmp(cmd->redir->file, "/tmp/heredoc_tmp", 16) == 0)
//                    unlink(cmd->redir->file);
//                free(cmd->redir->file);
//            }
//            free(cmd->redir);
//            cmd->redir = rtmp;
//        }
        
//        free(cmd);
//        cmd = tmp;
//    }
//}

void	print_cmd_list(t_cmd *cmd)
{
	int		i;
	t_redir	*r;

	while (cmd)
	{
		printf("cmd: ");
		i = 0;
		if (cmd->argv)
		{
			while (cmd->argv[i])
			{
				printf("[%s] ", cmd->argv[i]);
				i++;
			}
		}
		printf("\n");
		r = cmd->redir;
		while (r)
		{
			printf(" redir type: %d, file: %s\n", r->type, r->file);
			r = r->next;
		}
		cmd = cmd->next;
	}
}
