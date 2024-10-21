/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melyssa <melyssa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/10/12 12:23:20 by melyssa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int mini_cd(char **cmd)
{
    char cwd[10000];

    if(count_args(cmd) > 2)
        return(cd_error(1, cmd));
    else if (count_args(cmd) == 1)
        return(cd_home());
    else
    {
        if(ft_strcmp(cmd[1], "~") == 0)
            return(cd_home());
        else if (ft_strcmp(cmd[1], "-") == 0)
            return(cd_oldpwd());
        if (chdir(cmd[1]) == 0)
        {
            if (getcwd(cwd, sizeof(cwd)) != NULL)
                return(0);
            else 
                return(cd_error(3, cmd));
        }
    }
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

int cd_oldpwd(void)
{

}

int ft_cd_error(int i, char **cmd)
{
    if (i == 1)
        printf("minishell: cd: too many arguments\n");
    else if (i == 2)
        printf("minishell: cd: HOME not set\n");
    else if (i == 3)
        {
            printf("minishell : cd : %s: No such file or directory", cmd[1]);
            return(1);
        }
    return (1);
}
