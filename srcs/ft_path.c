#include "../includes/ft_ls.h"

char	*ft_new_path(char *path, char *param)
{
	char	*dest;
	char	*tmp;
	int		len;

	if (param[0] == '/' && ft_strcmp(path, "./") == 0)
	{
		if (param[ft_strlen(param) - 1] == '/')
			return (ft_strdup(param));
		return (ft_strjoin(param, "/"));
	}
	if (path[ft_strlen(path) - 1] == '/')
	{
		if (!(tmp = ft_strjoin(path, param)))
			return (NULL);
		if (!(dest = ft_strjoin(tmp, "/")))
			return (NULL);
	}
	else
		if (!(tmp = ft_strjoin(path, "/\0")))
			return (NULL);
		else if (!(dest = ft_strjoin(tmp, param)))
			return (NULL);
	len = ft_strlen(dest);
	if (dest[len - 1] == '/' && dest[len - 2] == '/')
		dest[len - 1] = '\0';
	ft_strdel(&tmp);
	return (dest);
}
