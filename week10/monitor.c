#include <stdio.h>
#include <stdlib.h>
#include <sys/inotify.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>
#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define EVENT_BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )
#define PATH_LENGTH 1024


void print_all_stats(const char* source) {
    printf("Detecting files in directory: \n");
    DIR *dir;
    struct dirent *entry;
    char path[PATH_LENGTH];
    struct stat info;
    if((dir = opendir(source)) == NULL) perror("opendir error: ");
    else {
        while((entry = readdir(dir)) != NULL) {
            if(entry->d_name[0] != '.') {
                strcpy(path, source);
                strcat(path,"/");
                strcat(path, entry->d_name);
                if(stat(path, &info) == 0){
                    printf("File: %s, Inode number: %lu, hardlinks: %lu\n", path, info.st_ino, info.st_nlink);
                }
            }
        }
        closedir(dir);
    }
}
char signal_handler_path[PATH_LENGTH];
void signal_handler(int signum) {
    if(signum == SIGINT) {
        print_all_stats(signal_handler_path);
        exit(0);
    }
}
int main(int argc, char const *argv[]){
    char* path = argv[1];
    strcpy(signal_handler_path,argv[1]);
    signal(SIGINT, signal_handler);

    int notifier = inotify_init();
    if(notifier == -1) {
        printf("Could not monitor file!\n");
        return 0;
    }
    int watcher = inotify_add_watch(notifier, path,
        IN_ACCESS | 
        IN_CREATE |
        IN_DELETE |
        IN_MODIFY |
        IN_OPEN |
        IN_ATTRIB
        );
    if(watcher == -1) {
        printf("Could not watch the file/n");
        return 0;
    }
    print_all_stats(path);
    printf("Monitoring directory...\n");
    int length;
    char buffer[EVENT_BUF_LEN];
    while(1) {
        length = read(notifier, buffer, EVENT_BUF_LEN);
        int i = 0;
        while ( i < length ) {
            struct inotify_event *event = ( struct inotify_event * ) &buffer[i];
            if ( event->len ) {
                if ( event->mask & IN_CREATE ) {
                    // creation of file
                    if ( event->mask & IN_ISDIR )
                        printf( "New directory %s created.\n", event->name );
                    else
                        printf( "New file %s created.\n", event->name );
                } else if ( event->mask & IN_DELETE ) {
                    // deletion of file
                    if ( event->mask & IN_ISDIR )
                        printf( "Directory %s deleted.\n", event->name );
                    else
                      printf( "File %s deleted.\n", event->name );
                } else if ( event->mask & IN_ACCESS ) {
                    // access to file
                    if ( event->mask & IN_ISDIR )
                        printf( "Directory %s Accessed.\n", event->name );
                    else
                      printf( "File %s Accessed.\n", event->name );
                } else if ( event->mask & IN_MODIFY ) {
                    // modification to file
                    if ( event->mask & IN_ISDIR )
                        printf( "Directory %s modified.\n", event->name );
                    else
                      printf( "File %s modified.\n", event->name );
                } else if ( event->mask & IN_OPEN ) {
                    // in opening of a file
                    if ( event->mask & IN_ISDIR )
                        printf( "Directory %s opened.\n", event->name );
                    else
                      printf( "File %s opened.\n", event->name );
                } else if ( event->mask & IN_ATTRIB ) {
                    // change of metadata
                    if ( event->mask & IN_ISDIR )
                        printf( "Changed metdata of directory %s.\n", event->name );
                    else
                      printf( "Changed metdata of file %s.\n", event->name );
                }
            }
            i += EVENT_SIZE + event->len;
        }
    }

    inotify_rm_watch(notifier, watcher);
    close(notifier);
    printf("Monitoring stopped!\n");
    print_all_stats(argv[1]);
    return 0;
}