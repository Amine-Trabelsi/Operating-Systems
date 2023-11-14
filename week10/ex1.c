#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h> 
#include <signal.h>
#define PATH_LENGTH 1024

void find_all_hlinks(const char* source) {
	// print them to stdout
	struct stat file_stat;
	int fd = open("myfile1.txt", O_RDONLY);
	int ret = fstat(fd, &file_stat);
	close(fd);
	long unsigned inode = file_stat.st_ino;
	printf("Inode of myfile1.txt: %lu\n", inode);

	printf("Files with the same inode: \n");
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
					if(info.st_ino == inode){
						printf("%s\n", path);
					}
				}
			}
		}
		closedir(dir);
	}
}

void unlink_all(const char* source){
	printf("inlinking\n");
	// keep only one hard link 
	// and print location to stdout
	// print stats of the last link
	// print them to stdout
	struct stat file_stat;
	char path_to_first[PATH_LENGTH];
	strcpy(path_to_first, source);
	strcat(path_to_first, "/myfile11.txt");
	int fd = open(path_to_first, O_RDONLY);
	int ret = fstat(fd, &file_stat);
	close(fd);
	long unsigned inode = file_stat.st_ino;
	printf("Inode of myfile11.txt: %lu\n", inode);

	printf("Deleting Files with the same inode: \n");
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
					if(info.st_ino == inode){
						printf("%s\n",path);
						unlink(path);
					}
				}
			}
		}
		closedir(dir);
	}
}

void create_sym_link(const char* source, const char* link) {
	// create symbolic link to source in that path
	// use symlink()
	symlink(source, link);
}

int main(int argc, char const *argv[]){
	// create myfile1.txt
	FILE* fp = fopen("myfile1.txt", "w");
	if(fp == NULL) {
		printf("Failed to create myfile1.txt\n");
		return 0;
	}
	fprintf(fp, "Hello World!\n");
	fclose(fp);
	
	char path_to_first[PATH_LENGTH];//= argv[1];
	char path_to_second[PATH_LENGTH];
	strcpy(path_to_first, argv[1]);
	strcpy(path_to_second, argv[1]);
	strcat(path_to_first, "/myfile11.txt");
	strcat(path_to_second, "/myfile12.txt");

	// create two hard links
	link("myfile1.txt", path_to_first);
	link("myfile1.txt", path_to_second);
	
	find_all_hlinks(argv[1]);

	// move file myfile1.txt to tmp/
	rename("myfile1.txt", "/tmp/myfile1.txt");
	// modify the file myfile11.txt
	FILE* tmp = fopen(path_to_first, "a");
	fprintf(tmp, "Hello again!\n");
	fclose(tmp);
	// did the monitor detect the change ?


	char path_to_third[PATH_LENGTH];
	strcpy(path_to_third, argv[1]);
	strcat(path_to_third, "/myfile13.txt");
	create_sym_link("/tmp/myfile1.txt", path_to_third);

	// modify tmp/myfile1.txt 
	tmp = fopen("/tmp/myfile1.txt", "a");
	fprintf(tmp, "Hello for the third time!\n");
	fclose(tmp);
	// did the monitor detect smth?

	unlink_all(argv[1]);
	// explain the number of hard links
	
	return 0;
}