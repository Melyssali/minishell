/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/10/21 15:44:31 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int cd_error(int i, char **cmd)
{
    if (i == 1)
        printf("minishell: cd: too many arguments\n");
    else if (i == 2)
        printf("minishell: cd: HOME not set\n");
    else if (i == 3)
		printf("minishell : cd : %s: No such file or directory", cmd[1]);
	else if (i == 4)
		printf("minishell : cd : OLDPWD not set");
    return (1);
}

int cd_oldpwd(t_minishell *minishell)
{
	minishell->oldpwd = getenv("OLDPWD");
	if (minishell->oldpwd == NULL)
		return(cd_error(2, NULL));
	if (chdir(minishell->oldpwd) == 0)
		return(0);
	else
		return(cd_error(3, NULL));
}
int ft_count_args(char **cmd)
{
    int i;

    i = 0;
    while (cmd[i])
        i++;
    return (i);
}

int cd_home(void)
{
    char *home;

    home = getenv("HOME");
    if (home == NULL)
        return(cd_error(2, NULL));
    if (chdir(home) == 0)
        return(0);
    else
        return(cd_error(3, NULL));
}

int mini_cd(char **cmd, t_minishell *minishell)
{
    char cwd[10000];

    if(ft_count_args(cmd) > 2)
        return(cd_error(1, cmd));
    else if (ft_count_args(cmd) == 1)
        return(cd_home());
    else
    {
        if(strcmp(cmd[1], "~") == 0)
            return(cd_home());
        else if (strcmp(cmd[1], "-") == 0)
            return(cd_oldpwd(minishell));
        if (chdir(cmd[1]) == 0)
        {
            if (getcwd(cwd, sizeof(cwd)) != NULL)
                return(0);
            else 
                return(cd_error(3, cmd));
        }
    }
	return(0);
}


int main (int argc, char **argv)
{
	t_minishell minishell;
	
	if (argc > 1)
	{
		char cwd[1000];
		if (argv[1][0] == '1')
		{
			char *cmd1[] = {"cd", NULL};
			getcwd(cwd, 1000);
			printf("répertoire courant avant la commande cd : %s\n", cwd);
			mini_cd(cmd1, &minishell);
			getcwd(cwd, 1000);
			printf("répertoire courant après la commande cd : %s\n", cwd);
		}
		else if (argv[1][0] == '2')
		{
			char *cmd1[] = {"cd", "~", NULL};
			getcwd(cwd, 1000);
			printf("répertoire courant avant la commande cd ~ : %s\n", cwd);
			mini_cd(cmd1, &minishell);
			getcwd(cwd, 1000);
			printf("répertoire courant après la commande cd ~ : %s\n", cwd);
		}
		else if (argv[1][0] == '3')
		{
			char *cmd1[] = {"cd", "/Users/lscarcel/Documents", NULL};
			getcwd(cwd, 1000);
			printf("répertoire courant avant la commande cd /Users/lscarcel/Documents : %s\n", cwd);
			mini_cd(cmd1, &minishell);
			getcwd(cwd, 1000);
			printf("répertoire courant après la commande cd /Users/lscarcel/Documents : %s\n", cwd);
		}
		else if (argv[1][0] == '4')
		{
			char *cmd1[] = {"cd", "..", NULL};
			getcwd(cwd, 1000);
			printf("répertoire courant avant la commande cd .. : %s\n", cwd);
			mini_cd(cmd1, &minishell);
			getcwd(cwd, 1000);
			printf("répertoire courant après la commande cd .. : %s\n", cwd);
		}
		else if (argv[1][0] == '5')
		{
			char *cmd1[] = {"cd", "/Users/lscarcel/Documents", NULL};
			char *cmd2[] = {"cd", "-", NULL};
			getcwd(cwd, 1000);
			printf("\n");
			printf("répertoire de départ : %s\n", cwd);
			printf("\n");
			printf("on se déplace dans   : /Users/lscarcel/Documents\n");
			printf("\n");
			mini_cd(cmd1, &minishell);
			getcwd(cwd, 1000);
			printf("répertoire courant après la commande cd /Users/lscarcel/Documents : %s\n", cwd);
			printf("\n");
			printf("Puis on revient en arrière\n");
			printf("\n");
			mini_cd(cmd2, &minishell);
			getcwd(cwd, 1000);
			printf("répertoire courant après la commande cd - : %s\n", cwd);
		}
	}
	return (0);
}
