#include "xml_tag_fill.h"

int 		main(int argv, char **argc)
{
	char 	*output;
	int 	output_file_fd;
	char	*output_file_name;
	t_file 	*file;

	if (argv != 3)
	{
		printf("USAGE: ./xml_tag_fill FILE BARCODE_FILE\n");
		exit (0);
	}
	file = (t_file *)malloc(sizeof(t_file));
	file->file_start = false;
	file->position = read_file(argc[1]);
	output = generate_file(argc[2], file);
	output_file_name = ft_strjoin("new_", argc[1]);
	output_file_fd = open(output_file_name, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	free(&file->position);
	ft_putstr_fd(output, output_file_fd);
	ft_strdel(&output);
	return (0);
}