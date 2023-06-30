#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]){

  struct timeval start_time, end_time;
  float elapsed_time;
  pid_t pid;
  int status;
  struct rusage myUsage;

  gettimeofday(&start_time, NULL);

  if (argc < 2){
    fprintf(stderr, "Usage: %s Enter Arguments!\n", argv[0]);
    return 1;
  }

  pid = fork();
  if (pid == -1){
    perror("fork");
    return 1;
  }

  else if (pid == 0){
    
    execvp(argv[1], argv + 1);
    perror("execvp");
    return 1;   
  }

  if (wait4(pid, &status, 0, &myUsage) == -1){
    perror("wait4");
    return 1;
  }

  
  printf("User CPU time: %ld.%ds\n", myUsage.ru_utime.tv_sec, myUsage.ru_utime.tv_usec);
  printf("System CPU time: %ld.%ds\n", myUsage.ru_stime.tv_sec, myUsage.ru_stime.tv_usec);


  gettimeofday(&end_time, NULL);
  
  elapsed_time = (end_time.tv_sec - start_time.tv_sec) + (double)(end_time.tv_usec - start_time.tv_usec) / 1000000;

  printf("Elapsed wall clock time: %.6fs\n", elapsed_time);

  return 0;
}
