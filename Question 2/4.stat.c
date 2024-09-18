#include <sys/stat.h>
#include <stdio.h>
#include <time.h>

int main() {
    struct stat fileStat;

    // Get file status
    if (stat("file.txt", &fileStat) < 0) {
        perror("stat failed");
        return 1;
    }

    // Print file information
    printf("File size: %ld bytes\n", fileStat.st_size);
    printf("File last modified: %s", ctime(&fileStat.st_mtime));

    return 0;
}
