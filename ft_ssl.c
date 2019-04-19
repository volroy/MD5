#include "ft_ssl.h"

int		main(int argc, char *argv[])
{
	t_com	*com;
	t_com	*com_list;

	com_list = NULL;
	commands_init(&com_list);
	if (argc != 1)
	{
		if ((com = check_command(argv[1], com_list)))
		{
			if (argc == 2)
				stdin_operate(com);
			else
				ssl_process(com, argc - 2, &(argv[2]));
		}
		else
			print_invalid_command(argv[1], com_list);
	}
	else
		read_command_from_stdin(com_list);
	clean_list(&com_list);
	return (0);
}

void	read_command_from_stdin(t_com *com_list)
{
	int		ret;
	char	*line;
	t_com	*com;

	ret = 0;
	ft_printf("FT_SSL> ");
	while ((ret = get_next_line(0, &line)) && ret != -1)
	{
		if (!(com = check_command(line, com_list)))
		{
			print_invalid_command(line, com_list);
			ft_memdel((void **)&line);
			ft_printf("FT_SSS> ");
			continue ;
		}
		else
		{
			stdin_operate(com);
			break ;
		}
	}
	if (ret == -1)
		perror("Bad STDIN reading");
}

void	format_output(t_com *com, char *name)
{
	char	*upper;

	if (com->quiet == '+')
		ft_printf("%s\n", com->digest);
	else if (com->reverse == '+')
	{
		if (com->isfile == '+')
			ft_printf("%s %s\n", com->digest, name);
		else
			ft_printf("%s \"%s\"\n", com->digest, name);
	}
	else
	{
		if (!(upper = ft_strupper(com->name)))
			exit(0);
		if (com->isfile == '+')
			ft_printf("%s (%s) = %s\n", upper, name, com->digest);
		else
			ft_printf("%s (\"%s\") = %s\n", upper, name, com->digest);
		ft_memdel((void **)&upper);
	}
}

void	print_command_usage(t_com *com, char op)
{
	if (op == 's')
		ft_printf("ft_ssl: %s: option requires an argument -- %c\n", com->name, op);
	else
		ft_printf("ft_ssl: %s: illegal option -- %c\n", com->name, op);
	ft_printf("usage: %s [-pqr] [-s string] [files ...]\n", com->name);
}

void	print_invalid_command(char *command, t_com *list)
{
	ft_printf("ft_ssl: Error: \'%s\' is an invalid command.\n", command);
	ft_printf("\nStandard commands:\n");
	while (list && ft_strequ(list->group, "Standard"))
	{
		ft_printf("%s\n", list->name);
		list = list->next;
	}
	ft_printf("\nMessage Digest commands:\n");
	while (list && ft_strequ(list->group, "Message Digest"))
	{
		ft_printf("%s\n", list->name);
		list = list->next;
	}
	ft_printf("\nCipher commands:\n");
	while (list && ft_strequ(list->group, "Cipher"))
	{
		ft_printf("%s\n", list->name);
		list = list->next;
	}
	ft_printf("\n");
}
