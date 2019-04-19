#include "ft_ssl.h"

void	commands_init(t_com **com_list)
{
	add_new_command(com_list, "Message Digest", "sha512", &sha512_start);
	add_new_command(com_list, "Message Digest", "sha256", &sha256_start);
	add_new_command(com_list, "Message Digest", "md5", &md5_start);
}

void	add_new_command(t_com **com_list, char *group, char *name, t_func f)
{
	t_com	*new;

	if ((new = ft_memalloc(sizeof(t_com))))
	{
		new->group = group;
		new->name = name;
		new->func = f;
		new->next = *com_list;
		*com_list = new;
	}
	else
	{
		ft_printf("Command %s ", name);
		perror("wasn't created");
	}
}

t_com	*check_command(char *command, t_com *list)
{
	t_com	*temp;

	if (!list)
	{
		ft_printf("Commands list is empty!\n");
		exit(0);
	}
	temp = list;
	while (temp)
	{
		if (ft_strequ(temp->name, command))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

void	final_check(t_com *com)
{
	char	*temp;

	if ((com->reverse == '+' || com->quiet == '+') && !com->wasout && !com->p)
		stdin_operate(com);
	if ((com->reverse == '+' || com->quiet == '+') && !com->wasout && com->p)
	{
		temp = ft_strdup("");
		com->digest = com->func(temp, ft_strlen(temp));
		ft_printf("%s\n", com->digest);
		ft_memdel((void **)&(com->digest));
	}
}

void	clean_list(t_com **list)
{
	t_com	*temp;

	temp = *list;
	if (temp && temp->next)
		clean_list(&(temp->next));
	if (temp)
		ft_memdel((void **)&temp);
}
