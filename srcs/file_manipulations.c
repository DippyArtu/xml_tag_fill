#include "xml_tag_fill.h"

char 		*read_file(char *file_name)
{
	int 	fd;
	char 	*line;
	char 	*temp;
	char 	*file;
	int 	c;

	c = 1;
	if (!(fd = open(file_name, O_RDONLY)))
	{
		printf("file error\n");
		exit (0);
	}
	printf("FILE OPPENED\n\n");
	file = ft_strnew(1);
	while (get_next_line(fd, &line) > 0)
	{
		if (!(temp = ft_strdup(line)))
		{
			printf("READ ERROR temp strdup\n");
			exit(0);
		}
		if (!(file = ft_strjoin(file, temp)))
		{
			printf("READ ERROR file strjoin\n");
			exit(0);
		}
		printf("%i reading.....\n", c);
		c++;
		ft_strdel(&temp);
		ft_strdel(&line);
	}
	ft_strdel(&temp);
	ft_strdel(&line);
	if (get_next_line(fd, &line) == -1)
	{
		printf("file gnl error\n");
		exit (0);
	}
	ft_strdel(&line);
	close(fd);
	return (file);
}

char		*find_barcode(t_file *file)
{
	char 	*code;
	char 	tag_open[] = "<barcode>";
	int 	tag_c;

	tag_c = ft_strlen(tag_open);
	code = ft_strnew(1);
	file->position = ft_strstr(file->position, tag_open);
	if (!file->position)
		return (NULL);
	file->position = ft_skipnchars(file->position, tag_c);
	code = ft_strcpy_till_char(code, file->position, '<');
	file->position = ft_skipnchars(file->position, (ft_strlen(code) + tag_c + 1));
	return (code);
}

void		transfer_text(t_file *file)
{
	char *tmp;

	tmp = NULL;
	if (file->file_start && file->position)
	{
		tmp = ft_strsubptr(file->position_tmp, file->position);
		file->file_out = ft_strjoin(file->file_out, tmp);
		ft_strdel(&tmp);
	}
	else if (!file->file_start)
	{
		file->file_out = ft_strsubptr(file->file_tmp, file->position);
		file->file_start = true;
	}
	file->file_tmp = file->file_out;
	if (file->position)
		file->position_tmp = file->position;
}