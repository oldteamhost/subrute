#include <stdio.h>
#include <curl/curl.h>
#include <sys/stat.h> 
#include "output.h"

int init_data_folder(){
    int temp_data;
    temp_data = mkdir("bases", S_IRUSR | S_IWUSR | S_IXUSR);

    if (temp_data == 0){
        return 0;
    }
    
    return EOF;
}

void init_main_folders(){
    init_data_folder();
}

int write_line_to_file(const char *path, const char *line){
    FILE *file = fopen(path, "a");
    if (file == NULL) {
        printf("Subrute: error open file\n");
        return EOF;
    }
    fprintf(file, "%s\n", line);
    fclose(file);
    return 0;
}

int write_main_info_to_file(const char* path, const char* line){
    FILE *fp;
    time_t currentTime;
    struct tm *localTime;

    currentTime = time(NULL);
    localTime = localtime(&currentTime);

    fp = fopen(path, "a");

    if (fp == NULL) {
        printf("Subrute: error open file\n");
        return EOF;
    }

    fprintf(fp, "%s %d-%02d-%02d %02d:%02d:%02d\n", line,
        localTime->tm_year + 1900, localTime->tm_mon + 1, localTime->tm_mday,
        localTime->tm_hour, localTime->tm_min, localTime->tm_sec);

    fclose(fp);
    return 0;
}
