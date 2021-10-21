#include <fcntl.h>
#include <unistd.h>
#include <cstdio>
#include "File.h"

/** The buffer is clear automatically. Don't use the reference.  */
void File::readFile(const char *path, void (*block)(const char* block, long len, int blockSize)) {
    int fd = open(path, O_RDONLY);

    char buffer[BUFFER_SIZE + 1];

    long bytesRead;
    while ((bytesRead = read(fd, buffer, BUFFER_SIZE))) {
        buffer[bytesRead] = '\0';
        block(buffer, bytesRead, BUFFER_SIZE);
    }

    close(fd);
}

void File::writeFile(const char* path, const char* text, int len, bool clear) {
    int fd = open(path, O_WRONLY | O_APPEND | O_CREAT | (O_TRUNC * clear), 0644);

    write(fd, text, len);
    close(fd);
}
