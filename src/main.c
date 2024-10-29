/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melyssa <melyssa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/10/28 21:14:36 by melyssa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "libft.h"
#include <readline/readline.h>
// les redirections :
//  < 	(commande < fichier.txt) doit rediriger l’entrée. Si le fichier existe, il est simplement utilisé comme source d'entrée. Pas de troncature ni d'ajout, juste une lecture du fichier.
//  > 	(echo "Nouveau contenu" > fichier.txt) doit rediriger la sortie. Si le fichier existe, son contenu est truncaté (écrasé) et remplacé par la nouvelle sortie de la commande.
//  << 	(commande << DELIMITEUR) doit recevoir un délimiteur et lire l’input donné jusqu’à rencontrer une ligne
// 		contenant le délimiteur. Cependant, l’historique n’a pas à être mis à jour !
//	>> 	(echo "Ajouté à la fin" >> fichier.txt) doit rediriger la sortie en mode append (ajout à la fin du fichier).
//  | 	doit rediriger la sortie de la commande à gauche du pipe vers l’entrée de la commande à droite du pipe.

//  Your shell must implement the following builtins:
// ◦ echo with option -n
// ◦ cd with only a relative or absolute path
// ◦ pwd with no options
// ◦ export with no options
// ◦ unset with no options
// ◦ env with no options or arguments
// ◦ exit with no options
int	main(void)
{
	t_command_line *ptr;
	char	*input;
	char **tokens;

	while (1)
	{
		input = readline("minishell % ");
		if (input == NULL)
			break ;
		// add_history(input);
		tokens = split_into_tokens(input);
		if (tokens == NULL)
		{
			printf("Missing last quote");
		}
		ptr = parsing(tokens);
		if (ptr == NULL)
			{
   			 printf("Error: ptr is NULL, linked list is empty.\n");
   			 return (1);  // Arrêter le programme si la liste est vide
		}
		t_command_line *tmp = ptr;
		// Affichage de la liste avant la libération
		while (tmp)
		{
			printf("NODE : \n");
			printf("--------------\n");
			for (int i = 0; tmp->command[i]; i++)
				printf("  CMD[%d] : %s", i, tmp->command[i]);
			printf("\nis_builtin : %d\n, input : %s\n, output : %s\n, is_append : %d\n NEXT : --->\n", tmp->is_builtin, tmp->input_file, tmp->output_file, tmp->append_output);
			printf("--------------\n");
			tmp = tmp->next;
		}

		// Libération de la liste après l'affichage
		t_command_line *current;
		while (ptr != NULL)
		{
			current = ptr;
			ptr = ptr->next;
			free(current); // Libère le nœud
		}


		if (ft_strcmp(tokens[0], "exit") == 0)
			break ;
	}
	return (0);
}
