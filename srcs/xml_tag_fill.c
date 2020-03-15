#include "xml_tag_fill.h"

int 		main(int argv, char **argc)
{
	char 	*output;
	t_file 	*file;

	if (argv != 3)
	{
		printf("USAGE: ./xml_tag_fill FILE BARCODE_FILE\n");
		exit (0);
	}
	file = (t_file *)malloc(sizeof(t_file));
	file->file_start = false;
	file->file_end = false;
	file->position = read_file(argc[1]);
	output = generate_file(argc[2], file);
	return (0);
}