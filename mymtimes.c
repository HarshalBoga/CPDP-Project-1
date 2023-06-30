// Printing output as required in the question //

// #include <stdio.h>
// #include <time.h>

// int main(){
  
//   time_t now = time(NULL);

//   struct tm *nowtime;

//   nowtime = localtime(&now);

//   printf("%s\n" , nowtime);
// }


// Getting last modification //




// int main(int argc , char* argv[]){
  
//   if(argc < 2){
//     printf("Enter a directory as a command!");
//   }
  
//    DIR* mydir = opendir(argv[1]);
//   struct dirent* direntPointer;

//   while((direntPointer = readdir(mydir)) != NULL){

//   while(direntPointer!=NULL){

//    char path[1000];
//    snprintf(path , 100 , "%s/%s" , argv[1] , direntPointer->d_name);

//    struct stat buf;
   
//    if(stat(path , &buf) == 0){
//     printf("This was Modified on: %s" , ctime(&buf.st_mtime));
//    }

//   }
//   }
//   closedir(mydir);
// }



// #include <time.h>
// #include <stdio.h>
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <stdio.h>
// #include <dirent.h>
// #include <string.h>
// #include <unistd.h>
// #include <dirent.h>
// #include <sys/stat.h>
// #include <time.h>
// #include <stdio.h>
// #include <stdlib.h>

// int showModificationTime(char* path){

//   DIR *dir;
//   struct dirent *ent;
//   struct stat fileStat;
//   int arrayOfHours[24];
//   time_t now = time(NULL);
//   time_t timeNow;
//   struct tm *tm;
 
//   memset(arrayOfHours , 0 , sizeof(arrayOfHours));

//   dir = opendir(path);
//   if ((dir != NULL)) {
//     while ((ent = readdir(dir)) != NULL) {

//       char filePath[1024];
//       snprintf(filePath, sizeof(filePath), "%s/%s", path, ent->d_name);

//       if (lstat(filePath, &fileStat) == 0) {
       
        
//         int hours = (now - fileStat.st_mtime)/ 3600;
//         if(hours < 24){
//           arrayOfHours[23 - hours]++;  
//         } 
//       } else {
//         perror("stat");
//       }

//       for(int i = 0; i < 24 ; i++){
//         time_t timeNow = now - ((24 - i) * 3600); 
//         struct tm *tm = localtime(&timeNow);
       
//         printf("%s:%d\n" , asctime(tm) , arrayOfHours[23 - i]); 
//     }
//     closedir(dir);
    

//   }
//       }else{
//         perror("Directory Error!");
//       }
     
 
//  return 0; 
// }


// int main(int argc, char *argv[]) {
  

//   if (argc != 2) {
//     showModificationTime(".");
//   }

//   showModificationTime(argv[1]);
//   return 0;
// }




#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>



void searchInDir(char *path, int *arrayOfHourss);
void searchInFiles(char *file, int *arrayOfHours);
void printOutput(int *arrayOfHours);



int main(int argc, char *argv[]){

    char path[1000];
    int arrayOfHours[24];
    memset(arrayOfHours, 0, sizeof(arrayOfHours));

    if (argc == 2){
        strcpy(path, argv[1]);
    }
    else{
        strcpy(path, ".");
    }

    searchInDir(path, arrayOfHours);
    printOutput(arrayOfHours);

    return 0;
}



void searchInDir(char *path, int *arrayOfHours){

    DIR *dir;
    struct dirent *entry;
    struct stat statbuf;
    char nextPath[1000];

    if ((dir = opendir(path)) == NULL){
        return;
    }

    while ((entry = readdir(dir)) != NULL){
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0){
            continue;
        }

        snprintf(nextPath, 1000, "%s/%s", path, entry->d_name);
        lstat(nextPath, &statbuf);

        if (S_ISREG(statbuf.st_mode)){
            searchInFiles(nextPath, arrayOfHours);
        }
        else if (S_ISDIR(statbuf.st_mode)){
            searchInDir(nextPath, arrayOfHours);
        }
    }

    closedir(dir);
}



void searchInFiles(char *file, int *arrayOfHours){

    struct stat statbuf;
    time_t current_time, file_time;
    int arrayValues;

    lstat(file, &statbuf);
    file_time = statbuf.st_mtime;
    time(&current_time);

    arrayValues = (int)(difftime(current_time, file_time) / 3600);

    if (arrayValues < 24){
        arrayOfHours[arrayValues]++;
    }
}



void printOutput(int *arrayOfHours){

    time_t now = time(NULL);
    time_t timeNow;
    int i;

    for(i = 0; i < 24 ; i++){
    timeNow = now - ((24 - i) * 3600); 
    struct tm *tm = localtime(&timeNow);

    char buffer[26];
    strftime(buffer, 26, "%c", tm);
    printf("%s: %d\n", buffer, arrayOfHours[23 - i]);
    }
}
