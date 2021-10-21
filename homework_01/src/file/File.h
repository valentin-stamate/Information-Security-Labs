#ifndef HOMEWORK_01_FILE_H
#define HOMEWORK_01_FILE_H


class File {
public:
    static const long BUFFER_SIZE = 4096;

    static void readFile(const char* path, char* buffer, int& bytesRead);
    static void writeFile(const char* path, const char* text, int len, bool clear = false);
};


#endif //HOMEWORK_01_FILE_H
