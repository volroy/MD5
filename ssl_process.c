#include "ft_ssl.h"

void	ssl_process(t_com *com, int ac, char **av)
{
	int		i;
	int		r;

	i = 0;
	while (i < ac)
	{
		if (av[i][0] == '-')
		{
			if ((r = check_flags(com, av[i++])) == 1)
				continue ;
			else if (!r && i != ac)
				string_operate(com, ft_strdup(av[i++]));
			else
				break ;
		}
		else
		{
			com->isfile = '+';
			files_operate(com, ac - i, &(av[i]));
			break ;
		}
	}
	final_check(com);
}

int		check_flags(t_com *com, char *str)
{
	int		i;
	int		len;

	i = 1;
	len = ft_strlen(str);
	while (i < len)
	{
		if (str[i] == 'p' && (com->p = '+'))
			stdin_operate(com);
		else if (str[i] == 'q')
			com->quiet = '+';
		else if (str[i] == 'r')
			com->reverse = '+';
		else if (str[i] == 's' && i == len - 1)
			return (0);
		else if (str[i] == 's' && i++)
			i = string_operate(com, ft_strsub(str, i, len - i)) - 1;
		else
		{
			print_command_usage(com, str[i]);
			return (-1);
		}
		i++;
	}
	return (1);
}

void	stdin_operate(t_com *com)
{
	int		ret;
	char	*result;
	char	buff[513];

	result = NULL;
	ft_bzero(buff, 512);
	while ((ret = read(0, buff, 512)))
	{
		if (ret == -1)
		{
			perror("Bad STDIN reading");
			if (result)
				ft_memdel((void **)&result);
			return ;
		}
		collect_strings(&result, buff);
		ft_bzero(buff, 512);
	}
	if (com->p == '+' && result)
		ft_printf("%s", result);
	com->digest = com->func(result, ft_strlen(result));
	ft_printf("%s\n", com->digest);
	ft_memdel((void **)&(com->digest));
}

int		string_operate(t_com *com, char	*message)
{
	int		i;
	char	*copy;

	i = 0;
	if (message && (copy = ft_strdup(message)))
	{
		com->wasout = '+';
		com->digest = com->func(message, ft_strlen(message));
		format_output(com, copy);
		ft_memdel((void **)&copy);
		ft_memdel((void **)&(com->digest));
		return (OK);
	}
	else
		print_command_usage(com, 's');
	return (ERROR);

}

void	files_operate(t_com *com, int ac, char **av)
{
	int		i;
	char	*message;

	i = 0;
	while (i < ac)
	{
		if (ssl_readfile(av[i], &message) != -1)
		{
			com->wasout = '+';
			com->digest = com->func(message, ft_strlen(message));
			format_output(com, av[i]);
			ft_memdel((void **)&(com->digest));
		}
		else
			ft_printf("ft_ssl: %s: %s: No such file or directory\n", com->name, av[i]);
		i++;
	}
}
