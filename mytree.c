#include<stdio.h>
#include<string.h>
#include<dirent.h>
#include <string.h>
#include <unistd.h>

void printTreeStructure(const char* dir, int layer) {

    DIR* myDir = opendir(dir);

    if (myDir == NULL) {
        perror("opendir");
        return;
    } else {
         struct dirent* dirEntry;
         while ((dirEntry = readdir(myDir)) != NULL) {
            if (dirEntry->d_type == DT_DIR) {
                if (strcmp(dirEntry->d_name, ".") == 0 || strcmp(dirEntry->d_name, "..") == 0) {
                continue;
            }

            for (int i = 0; i < layer; i++) {
                printf("|   ");
            }

            printf("|--- %s\n", dirEntry->d_name);
            
            char path[1000];
            snprintf(path, sizeof(path), "%s/%s", dir, dirEntry->d_name);

            printTreeStructure(path, layer ++);
        } 
        
        if(dirEntry->d_type != DT_DIR){
            for (int i = 0; i < layer; i++) {
                printf("|   ");
            }
            printf("|---%s\n", dirEntry->d_name);
        }
    }

    closedir(myDir);
    
    }

   
}

int main(int argc, char* argv[]) {
    char* dir = ".";
    if (argc > 1) {
        dir = argv[1];
    }
    printTreeStructure(dir, 0);
    return 0;
}
