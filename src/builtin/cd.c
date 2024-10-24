/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/10/24 14:40:36 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void cd_error(char **cmd)
{
	printf("minishell : cd : %s: No such file or directory", cmd[1]);
}


int mini_cd(char **cmd, t_minishell *minishell)
{
    char cwd[10000];
	
    if (chdir(cmd[1]) == 0)
    {
    	if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			printf("%s\n", cwd);
			update_env_var("PWD", cwd, minishell);	
            return(0);
		}
        else 
		{
        	cd_error(cmd);
			return(1);			
		}
    }
	return(0);
}


// int main (int argc, char **argv, char **envp)
// {
// 	t_minishell minishell;
	
	
// 	copy_env(&minishell, envp);
// 	ft_env(&minishell);
// 	if (argc > 1)
// 	{
// 		char cwd[1000];
// 		if (argv[1][0] == '1')
// 		{
// 			char *cmd1[] = {"cd", "/Users/lscarcel/Documents", NULL};
// 			getcwd(cwd, 1000);
// 			printf("répertoire courant avant la commande cd /Users/lscarcel/Documents : %s\n", cwd);
// 			mini_cd(cmd1, &minishell);
// 			getcwd(cwd, 1000);
// 			printf("répertoire courant après la commande cd /Users/lscarcel/Documents : %s\n", cwd);
// 			printf("\n");
// 			ft_env(&minishell);
// 		}
// 		else if (argv[1][0] == '4')
// 		{
// 			char *cmd1[] = {"cd", "..", NULL};
// 			getcwd(cwd, 1000);
// 			printf("répertoire courant avant la commande cd .. : %s\n", cwd);
// 			mini_cd(cmd1, &minishell);
// 			getcwd(cwd, 1000);
// 			printf("répertoire courant après la commande cd .. : %s\n", cwd);
// 		}
// 	return (0);
// 	}
// }