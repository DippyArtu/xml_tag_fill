#include "xml_tag_fill.h"

char 		*read_file(char *file_name)
{
	int 	fd;
	char 	*line;
	char 	*temp;
	char 	*file_tmp;
	char 	*file;
	int 	c;

	c = 1;
	if (!(fd = open(file_name, O_RDONLY)))
	{
		printf("file open error\n");
		exit (0);
	}
	printf("FILE OPPENED\n\n");
	file = ft_strnew(1);
	while (get_next_line(fd, &line) > 0)
	{
		temp = ft_strjoin(line, "\n");
		ft_strdel(&line);
		file_tmp = ft_strjoin(file, temp);
		ft_strdel(&file);
		ft_strdel(&temp);
		file = file_tmp;
		//ft_strdel(&file_tmp);
		printf("%i reading.....\n", c);
		c++;
	}
	//ft_strdel(&file_tmp);
	ft_strdel(&temp);
	ft_strdel(&line);
	if (get_next_line(fd, &line) == -1)
	{
		printf("FILE READ GNL ERROR\n");
		ft_strdel(&temp);
		ft_strdel(&file_tmp);
		ft_strdel(&line);
		exit (0);
	}
	close(fd);
	return (file);
}

char		*find_barcode(t_file *file)
{
	char 	*code;
	char 	tag_open[] = "<barcode>";
	int 	tag_c;
	char 	*tmp;

	code = ft_strnew(1);
	file->position = ft_strstr(file->position, tag_open);
	if (!file->position)
		return (NULL);
	file->position = ft_skipnchars(file->position, (tag_c = ft_strlen(tag_open)));
	tmp = ft_strjoin_till_char(code, file->position, '<');
	ft_strdel(&code);
	code = tmp;
	ft_strdel(&tmp);
	file->position = ft_skipnchars(file->position, (ft_strlen(code) + tag_c + 1));
	return (code);
}

void		transfer_text(t_file *file)
{
	char *tmp;
	char *file_out_tmp;

	tmp = NULL;
	if (file->file_start && file->position)
	{
		tmp = ft_strsubptr(file->position_tmp, file->position);
		file_out_tmp = ft_strjoin(file->file_out, tmp);
		//ft_strdel(&file->file_out);
		file->file_out = file_out_tmp;
		ft_strdel(&file_out_tmp);
		ft_strdel(&tmp);
	}
	else if (!file->file_start)
	{
		file->file_out = ft_strsubptr(file->file_tmp, file->position);
		ft_strdel(&file->file_tmp);
		file->file_start = true;
	}
	file->file_tmp = file->file_out;
	if (file->position)
		file->position_tmp = file->position;
}