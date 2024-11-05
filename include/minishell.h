/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melyssa <melyssa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/11/04 22:33:59 by melyssa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H
# define ERROR -1
# define SQUOTE '\''
# define DQUOTE '\"'
# define SPACE ' '
# define TAB '\t'
# define NEWLINE '\n'
# define TRUE 1
# define FALSE 0

# define TABLE_BUILTINS_SIZE 11
# define TABLE_OPERATORS_SIZE 7

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "libft.h"
// #include <readline/readline.h>

typedef struct s_env_var
{
	char *key;
    char *value;
    struct s_env_var *next;
} t_env_var;

typedef struct s_minishell {
	char **envp;
	t_env_var *env;
}	t_minishell;

typedef enum
{
	REDIR_OUTPUT,
	APPEND_OUTPUT,
	REDIR_INPUT,
	HEREDOC,
	PIPE
}		
					e_operators;
typedef enum
{
	CD,
	ECHO,
	ENV,
	EXIT,
	EXPORT,
	PWD,
	UNSET
}							e_builtins;

// hash table for builtins
typedef struct s_hash_builtin
{
	char					*key;
	int						type;
	struct s_hash_builtin	*next;
}							t_hash_builtins;

// hash table for operators
typedef struct s_hash_operators
{
	char					*key;
	int						type;
	struct s_hash_operators	*next;
}							t_hash_operators;

typedef struct s_command_line
{
	char					**command;
	int						is_builtin;
	int						builtin_type;
	char					*input_file;
	char					*output_file;
	int						append_output;
	char					*heredoc_delimiter;
	struct s_command_line	*next;
}							t_command_line;
typedef struct s_data
{
	int						pipe_count;
}							t_data;

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

// -- BUILTINS -- //
int     mini_cd(char **cmd, t_minishell *minishell);
void 	cd_error(char **cmd);
int 	ft_count_args(char **cmd);
char 	*ft_getenv(char *key, t_minishell *minishell);
int 	update_env_value(char *key, char *value, t_minishell *minishell);
void 	copy_env(t_minishell *minishell);
int 	add_node(char *str, t_minishell *minishell);
void	print_env(t_minishell *minishell);
void	declare(t_minishell *minishell);
void	ft_pwd(t_minishell *minishell);

// Parsing
t_command_line				*parsing(char *tokens[], t_data *data);
t_command_line				*create_node(t_hash_operators *table_operators[],
								char *tokens[], int *index,
								t_hash_builtins *table_builtins[]);
int							calculate_width(t_hash_operators *table_operators[],
								char *tokens[], int *index);
int							is_builtin_command(char *cmd,
								t_hash_builtins *table_builtins[]);

// tokenization - quote verifications
int							find_last_quote(char *s, char quote);
int							is_space_before_quote(char *s);

// hash table builtins
void						initialize_builtins(t_hash_builtins *table_builtins[]);
int							search(t_hash_builtins *table[], char *key);

// hash table operators
void						initialize_operators(t_hash_operators *table_operators[]);
int							get_operator_type(t_hash_operators *table_operators[],
								char *str);

#endif