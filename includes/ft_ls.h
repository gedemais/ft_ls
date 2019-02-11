/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 00:59:52 by gedemais          #+#    #+#             */
/*   Updated: 2019/02/11 08:54:45 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# define TF ((t_file*)add[i])
# define TF1 ((t_file*)add[i - 1])

# define O_L 1
# define O_RMAJ 2
# define O_A 4
# define O_R 8
# define O_T 16

# include "../libft/libft.h"
# include <stdbool.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <time.h>
# include <errno.h>

typedef struct	s_file t_file;

struct		s_file
{
	char	*name;
	int		name_len;
	char	*perms;
	int		dir;
	t_file	*next;
};

// main.c
int		ft_ls(char **params, int mask, char *path);
void	ft_usage(int type, char wrong, char *wrong_name, int usage);

// ft_run.c
void	ft_run(char *path, int mask, int nbf, void **add);

// ft_list.c
int		ft_lstlen(t_file *lst);
void	ft_display_ls_lst(t_file *top);
t_file	*ft_ls_lstnew(char *path, char *name, int mask);
int		ft_ls_pushfront(t_file **file, t_file *new);
t_file	*ft_make_list(char **params, char *path, int mask);

// ft_parsing.c
int		ft_is_flag(char c);
int		ft_count(int argc, char **argv);
int		ft_get_options(int ac, char **av, int *i, int mask);
char	**ft_get_params(int ac, char **av, char **data, int i);
char	**ft_parse_input(int ac, char **av, int *mask);

// ft_quicksort.c
void	ft_swap_nodes(t_file *n1, t_file *n2);
void	**ft_addresses (t_file *lst, int len);
int		ft_ls_quicksort(void **add, int start, int end);

// fts.c
int		ft_tablen(char **tab);
char	**ft_tabdel(char **tab);
int		ft_add_mask(int mask, char c);
int		ft_get_screen_length(void);
int		ft_find_biggest(void **add);

#endif
