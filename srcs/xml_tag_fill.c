//TODO Figure out all the memory problem crap

#include "xml_tag_fill.h"

char 		*gen_name(char *old_name)
{
	char 	prefix[] = "new_";
	char 	*name;

	if (!(name = ft_strjoin(prefix, old_name)))
	{
		printf("\n\nNAME GEN ERROR\n\n");
		exit (0);
	}
	return (name);
}

int 		main(int argv, char **argc)
{
	char 	*output;
	int 	output_file_fd;
	char 	*name;
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

	name = gen_name(argc[1]);
	output_file_fd = open(name, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	ft_strdel(&name);
	free(&file->position);
	printf("NEW FILE CREATED\n\n");

	ft_putstr_fd(output, output_file_fd);
	ft_strdel(&output);
	printf("NEW FILE POPULATED\n\n");

	printf("DONE\n\n");
	return (0);
}