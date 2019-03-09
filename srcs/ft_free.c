#include "../includes/ft_ls.h"

char	**ft_tabdel(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		ft_strdel(&tab[i]);
		i++;
	}
	ft_strdel(&tab[i]);
	free(tab);
	tab = NULL;
	return (tab);
}

int	ft_free_add(void **add, int nbf)
{
	int		i;

	i = 0;
	while (i < nbf)
	{
		free(TF->name);
		i++;
	}
	free(add);
	return (0);
}

int		ft_ls_lstdel(t_file *lst)
{
	if (lst->next)
	{
		ft_ls_lstdel(lst->next);
		free(lst->next);
	}
	free(lst);
	return (0);
}
