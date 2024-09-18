#include <dirent.h>
#include <stdio.h>

int main() {
    struct dirent *de;  // Pointer for directory entry
    
    // Open directory
    DIR *dr = opendir(".");
    if (dr == NULL) {
        perror("Could not open current directory");
        return 1;
    }
    
    // Read and print directory entries
    printf("Directory contents:\n");
    while ((de = readdir(dr)) != NULL) {
        printf("%s\n", de->d_name);
    }

    // Close directory
    closedir(dr);
    
    return 0;
}
