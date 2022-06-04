#include "../shell.h"

int tablen(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return i;
}

void	unset_exp(t_shell *index, char *str)
{
	char **temp;
	char **save;
	int i;
	int j;

	i = 0;
	j = 0;
	temp = (char **)malloc(sizeof(char *) * (tablen(index->tab_save_exp) + 1));
	while (index->tab_save_exp[i])
	{
		if (len(index->tab_save_exp[i]) == 0)
		{
			save = (char **)malloc(sizeof(char *));
			save[0] = index->tab_save_exp[i];
		}
		else
			save = ft_split(index->tab_save_exp[i], '=');
		if (strcmp(save[0], str) != 0)
		{
			temp[j] = index->tab_save_exp[i];
			j++;
			i++;
		}
		else
			i++;
	}
	temp[j] = NULL;
	index->tab_save_exp = (char **)malloc(sizeof(char *) * (tablen(temp) + 1));
	i = 0;
	while (temp[i])
	{
		index->tab_save_exp[i] = temp[i];
		i++;
	}
	free(temp);
	index->tab_save_exp[i] = NULL;
}

void    ft_unset(t_shell *index, char **str, int fd)
{
	int i;
	int j;
	int k;
	char **save;
	char **temp;

	k = 1;
	while (str[k])
	{
		if (finder(str[k]) == 2)
		{
			ft_putstr_fd("export: not a valid identifier: ", fd);
			ft_putendl_fd(str[k], fd);
			k++;
			status_exec_g = 1;
		}
		else if (invalide_identifier(str[k], fd) == 1)
			k++;
		else
		{
			temp = (char **)malloc(sizeof(char *) * (tablen(index->tab_save_env) + 1));
			j = 0;
			i = 0;
			while (index->tab_save_env[i])
			{
				save = ft_split(index->tab_save_env[i], '=');
				if (strcmp(save[0], str[k]) != 0)
				{
					temp[j] = index->tab_save_env[i];
					j++;
					i++;
				}
				else
					i++;
			}
			temp[j] = NULL;
			index->tab_save_env = (char **)malloc(sizeof(char *) * (tablen(temp) + 1));
			i = 0;
			while (temp[i])
			{
				index->tab_save_env[i] = temp[i];
				i++;
			}
			free(temp);
			index->tab_save_env[i] = NULL;
			if (index->tab_save_exp)
				unset_exp(index, str[k]);
			k++;
			status_exec_g = 0;
		}
	}
}