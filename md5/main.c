#include "md5.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <error.h>

void print_md5sum(const char *path, FILE * fp);

int main(int argc, char *argv[])
{
    if (argc == 1)
        print_md5sum("-", stdin);

	for (int i = 1; i < argc; i++) {
		FILE   *fp = fopen(argv[i], "r");

		if (fp == NULL)
			error(EXIT_FAILURE, errno,
			      "error: open %s for reading", argv[i]);
        print_md5sum(argv[i], fp);
        fclose(fp);
	}

	return EXIT_SUCCESS;
}

void print_md5sum(const char *path, FILE * fp)
{

	MD5_CTX context;
	unsigned char digest[16];
	unsigned char buf[8096];
	int     nread;

	MD5Init(&context);
	while ((nread = fread(buf, 1, sizeof(buf), fp)) == sizeof(buf)) {
		MD5Update(&context, buf, nread);
    }
	if (ferror(fp))
		error(EXIT_FAILURE, errno, "error: reading %s", path);
	MD5Update(&context, buf, nread);
	MD5Final(digest, &context);

	for (int j = 0; (size_t) j < sizeof(digest); j++)
		printf("%02x", digest[j]);
	printf("  %s\n", path);
}
