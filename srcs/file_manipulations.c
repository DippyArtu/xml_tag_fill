#include "xml_tag_fill.h"

char 		*read_file(char *file_name)
{
	int 	fd;
	char 	*line;
	char 	*temp;
	char 	*file;
	int 	c;

	c = 1;
	temp = NULL;
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
		file = ft_strjoin(file, temp);
		//ft_strdel(&temp);
		printf("%i reading.....\n", c);
		c++;
	}
	if (get_next_line(fd, &line) == -1)
	{
		printf("FILE READ GNL ERROR\n");
		if (line)
			ft_strdel(&line);
		if (temp)
			ft_strdel(&temp);
		ft_strdel(&file);
		exit (0);
	}
	if (line)
		ft_strdel(&line);
//	if (temp)
//		ft_strdel(&temp);
	close(fd);
	return (file);
}

char		*find_barcode(t_file *file)
{
	char 	*code;
	char 	tag_open[] = "<barcode>";
	int 	tag_c;

	code = ft_strnew(1);
	file->position = ft_strstr(file->position, tag_open);
	if (!file->position)
		return (NULL);
	file->position = ft_skipnchars(file->position, (tag_c = ft_strlen(tag_open)));
	code = ft_strjoin_till_char(code, file->position, '<');
	file->position = ft_skipnchars(file->position, (ft_strlen(code) + tag_c + 1));
	return (code);
}

void		transfer_text(t_file *file)
{
	char *tmp;

	tmp = NULL;
	if (file->file_start && file->position) // this is for every consecutive pass
	{
		tmp = ft_strsubptr(file->position_tmp, file->position);
		file->file_out = ft_strjoin(file->file_out, tmp);
		ft_strdel(&tmp);
	}
	else if (!file->file_start) // on a first pass we go here to transfer everything before the first code
	{
		file->file_out = ft_strsubptr(file->file_tmp, file->position);
		file->file_start = true;
	}
	file->file_tmp = file->file_out;
	if (file->position)
		file->position_tmp = file->position;
}