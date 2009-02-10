#include "file_handler.h"

// TODO: Use fseek... We want to go chunk by chunk
char * read_file(char * file_name) {
	FILE *fp;
	char * file_data;
	struct stat file_status;

	if ((fp = fopen(file_name, "rb")) == NULL) {
		fclose(fp);
		return NULL;
	}

	stat(file_name, &file_status);

	free(file_data);
	file_data = (char *)malloc(file_status.st_size);
	
	fread(file_data, 1, file_status.st_size, fp);

	fclose(fp);

	return file_data;
}
