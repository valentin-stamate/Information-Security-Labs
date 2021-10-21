#include <fcntl.h>
#include <unistd.h>
#include <cstdio>
#include "File.h"

/** The buffer is clear automatically. Don't use the reference.  */
void File::readFile(const char *path, char* buffer, int& bytesRead) {
    FILE* fd = fopen(path, "r");

    char c;

    int len = 0;
    while ((c = getc(fd)) != EOF) {
        buffer[len++] = c;
    }
    buffer[len] = '\n';

    bytesRead = len;
    fclose(fd);
}

void File::writeFile(const char* path, const char* text, int len, bool clear) {
    int fd = open(path, O_WRONLY | O_APPEND | O_CREAT | (O_TRUNC * clear), 0644);

    write(fd, text, len);
    close(fd);
}
