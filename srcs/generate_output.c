#include "xml_tag_fill.h"

char 		*generate_link(char *code, char *barcode_file)
{
	int 	fd;
	char 	link_start[] = "<picture>https://storage.googleapis.com/fotobank1/";
	char	link_end[] = "</picture>";
	char 	*link_output;
	int		code_c;
	char 	*line;
	int 	test;

	if (!(fd = open(barcode_file, O_RDONLY)))
	{
		printf("barcode file open error\n");
		exit (0);
	}
	link_output = NULL;
	code_c = ft_strlen(code);
	while (get_next_line(fd, &line) > 0)
	{
		test = ft_strncmp(line, code, code_c);
		if (!test)
		{
			link_output = ft_strnew(200);
			link_output = ft_strcat(link_output, link_start);
			link_output = ft_strcat(link_output, line);
			link_output = ft_strcat(link_output, link_end);
			printf("match found\n\n");
		}
		ft_strdel(&line);
	}
	if (line)
		ft_strdel(&line);
	if (code)
		ft_strdel(&code);
	close(fd);
	return(link_output);
}

char 	*generate_file(char *barcode_file, t_file *file)
{
	char 	*output;
	char 	*link;
	char 	*code;
	char	*tmp;

	printf("GENERATION START\n\n");
	file->file_tmp = file->position;
	while (file->position)
	{
		code = find_barcode(file);
		transfer_text(file);
		if (code)
		{
			printf("CODE FOUND\n");
			if ((link = generate_link(code, barcode_file)))
			{
				tmp = file->file_out;
				file->file_out = ft_strjoin(file->file_out, link);
				ft_strdel(&tmp);
				ft_strdel(&link);
				printf("LINK INSERTED\n\n");
			}
		}
	}
	output = ft_strjoin(file->file_out, file->position_tmp);
	printf("DONE GENERATING\n\n");
	return (output);
}