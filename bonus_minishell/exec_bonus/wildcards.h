/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:26:50 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/23 16:31:52 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARDS_H
# define WILDCARDS_H

#include "../shell.h"
#include "../sec_parsing/header/utiles_functions.h"

typedef struct s_wild
{
	char	*get_next;
	char	*str1;
	char	*str2;
	char	**tab_wild;
	int		size;
	int		out_file;
	int		in_file;
	int		size_j;
}	t_wild;

void	change(t_list **list, t_wild *wild);
int		sec_utils_wild(t_wild *wild, int i, int count, char **tab);
void	utils_milt_wild(t_list **list, t_wild *wild, char **tab, int fd);
void	utils_mult_wild(t_list **list, t_wild *wild, char *tab, int fd);
void	mult_wild(t_list **list, t_wild *wild, char **tab, int fd);
void	one_wild(t_list **list, t_wild *wild, int fd);
void	import_all_arg(t_shell *mini, t_list **list, t_wild *wild, int fd);
void	exec_wild(t_shell *mini, t_list **list);
void	utils_exec_wild(t_wild *wild, t_shell *mini, t_list **list);
void	ft_wildcards(t_list **list, t_shell *mini);

#endif