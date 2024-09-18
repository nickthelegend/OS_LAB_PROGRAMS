#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    char buffer[1024];
    ssize_t bytesRead;
    
    // Open source file for reading
    int source = open("source.txt", O_RDONLY);
    if (source < 0) {
        perror("Failed to open source file");
        return 1;
    }

    // Open destination file for writing (or create it)
    int destination = open("destination.txt", O_WRONLY | O_CREAT, 0644);
    if (destination < 0) {
        perror("Failed to open destination file");
        close(source);
        return 1;
    }

    // Read from source and write to destination
    while ((bytesRead = read(source, buffer, sizeof(buffer))) > 0) {
        if (write(destination, buffer, bytesRead) != bytesRead) {
            perror("Write error");
            close(source);
            close(destination);
            return 1;
        }
    }

    // Close both files
    close(source);
    close(destination);
    
    return 0;
}
