/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melyssa <melyssa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/10/28 21:42:36 by melyssa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define ERROR -1

# define PIPE "|"
# define REDIR_INPUT "<"
# define REDIR_OUTPUT ">"
# define HEREDOC "<<"
# define APPEND_OUTPUT ">>"

# define SQUOTE '\''
# define DQUOTE '\"'
# define SPACE ' '
# define TAB '\t'
# define NEWLINE '\n'

# define HASH_TABLE_SIZE 10

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_builtin
{
	char					*key;
	struct s_builtin		*next;
}							t_builtin;

typedef struct s_command_line
{
	char					**command;
	int						is_builtin;
	char					*input_file;
	char					*output_file;
	int						append_output;
	char					*heredoc_delimiter;
	struct s_command_line	*next;
}							t_command_line;

// tokenization
char						**split_into_tokens(char *s);
char						*skip_space(char *s);
char						*iterate_word(char *s);
char						*skip_quotes(char *s, char quote);
char						*iterate_inside_quotes(char *s, char quote);
char						*handle_quote(char *s, char quote);
void						handle_arr(char *s, char **arr, int *count,
								char *start_string);
void						free_arr_tokenization(char **arr);

// Parsing
t_command_line				*parsing(char **tokens);
t_command_line				*create_node(char **command, int *index,
								t_builtin **hash_table);
int							calculate_width(char **tokens, int *index);
int							is_builtin_command(char *cmd, t_builtin **hash_table);

// tokenization - quote verifications
int							find_last_quote(char *s, char quote);
int							is_space_before_quote(char *s);

// hash table
unsigned int				hash(char *str);
void						insert(t_builtin **table, char *key);
int							search(t_builtin **table, char *key);
void						initialize_builtins(t_builtin **hash_table);
#endif