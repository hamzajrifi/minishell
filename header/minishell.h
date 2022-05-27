/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjrifi <hjrifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:13:56 by hjrifi            #+#    #+#             */
/*   Updated: 2022/05/27 11:13:37 by hjrifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct t_contents
{
	char	*str;
	int		i;
	int		end;
	int		narg;
}t_contents;

typedef struct s_pipes
{
	char			*prt;
	char			**val;
	int				*v_type;
	struct s_pipes	*next;
} s_pipes;


typedef struct  t_type 
{
	enum {
		command = 1,
		argument,
		variable,
		quote ,
		equale ,
		parenthese,
		dollar,
	}type;
}n_type;

typedef struct t_list
{
	char			**value;
	int				*type;
}s_list;

# include <stdio.h> 
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
#endif
