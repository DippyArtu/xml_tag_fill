#include "xml_tag_fill.h"

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

char 	*generate_file(char *barcode_file, t_file *file)
{
	char 	*output;
	char 	*link;
	char 	*code;

	file->file_tmp = file->position;
	while (file->position)
	{
		code = find_barcode(file);
		transfer_text(file);
		if (code)
		{
			link = generate_link(code, barcode_file);
			file->file_out = ft_strjoin(file->file_out, link);
			ft_strdel(&code);
			ft_strdel(&link);
		}
	}
	output = ft_strjoin(file->file_out, file->position_tmp);
	ft_strdel(&file->position);
	ft_strdel(&file->file_out);
	ft_strdel(&code);
	ft_strdel(&link);
	return (output);
}