//TODO mb remove \0 at the end of file?

#include "xml_tag_fill.h"

//void		ft_putstr_no_terminator_fd(char const *s, int fd)
//{
//	int i;
//
//	if (!s || !fd)
//		return ;
//	i = 0;
//	while (s[i])
//	{
//		write(fd, &s[i], 1);
//		i++;
//	}
//}

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
	printf("FILE READ\n\n");

	output = generate_file(argc[2], file);
	printf("FILE GENERATED\n\n");

	output_file_name = ft_strjoin("new_", argc[1]);
	output_file_fd = open(output_file_name, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	printf("NEW FILE CREATED\n\n");
	free(&file->position);

	ft_putstr_fd(output, output_file_fd);
	printf("NEW FILE POPULATED\n\n");
	ft_strdel(&output);

	printf("DONE\n\n");
	return (0);
}