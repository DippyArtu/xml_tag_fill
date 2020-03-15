#include "xml_tag_fill.h"

char 		*read_file(char *file_name)
{
	int 	fd;
	char 	*line;
	char 	*temp;
	char 	*file;

	if (!(fd = open(file_name, O_RDONLY)))
	{
		printf("file error\n");
		exit (0);
	}
	file = ft_strnew(1);
	while (get_next_line(fd, &line) > 0)
	{
		temp = ft_strdup(line);
		file = ft_strjoin(file, temp);
		ft_strdel(&temp);
		ft_strdel(&line);
	}
	if (get_next_line(fd, &line) == -1)
	{
		printf("file gnl error\n");
		exit (0);
	}
	ft_strdel(&temp);
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

char 		*generate_link(char *code, char *barcode_file)
{
	int 	fd;
	char 	link_start[] = "<picture>https://storage.cloud.google.com/fotobank1/";
	char	link_end[] = "?hl=ru</picture>";
	char 	*link_output;
	int		code_c;
	char 	*line;

	if (!(fd = open(barcode_file, O_RDONLY)))
	{
		printf("barcode file error\n");
		exit (0);
	}
	code_c = ft_strlen(code);
	link_output = ft_strnew(100);
	link_output = ft_strcat(link_output, link_start);
	while (get_next_line(fd, &line))
	{
		if (!ft_strncmp(line, code, code_c))
		{
			link_output = ft_strcat(link_output, line);
			link_output = ft_strcat(link_output, link_end);
		}
		free(line);
	}
	close(fd);
	ft_strdel(&line);
	return(link_output);
}