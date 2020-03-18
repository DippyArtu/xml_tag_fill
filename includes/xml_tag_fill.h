#ifndef XML_TAG_FILL_H
# define XML_TAG_FILL_H

# include "libft.h"
# include <stdio.h>
# include <stdbool.h>
# include <string.h>

typedef struct 		s_file
{
	char	*position;
	char	*position_tmp;
	char 	*file_out;
	char 	*file_tmp;
	bool	file_start;
}					t_file;

char 		*generate_link(char *code, char *barcode_file);
char 		*read_file(char *file_name);
char 		*generate_file(char *barcode_file, t_file *pos);
char		*find_barcode(t_file *pos);
void		transfer_text(t_file *pos);
char 		*gen_name(char *old_name);

#endif
