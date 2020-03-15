//TODO populate file with links


#include "xml_tag_fill.h"

char 	*generate_file(char *barcode_file, t_file *file)
{
	char 	*link;
	char 	*code;

	file->file_tmp = file->position;
	while (file->position)
	{
		code = find_barcode(file);
		transfer_text(file);
		//printf("%s\n\n", file->position_tmp);
		if (code)
		{
			link = generate_link(code, barcode_file);
			link = NULL;
			code = NULL;
		}
	}
	file->file_out = ft_strjoin(file->file_out, file->position_tmp);
	printf("%s\n\n", file->file_out);
	exit(0);
	return (file->file_out);
}