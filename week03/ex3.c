#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PATH 2048
#define FILE_NAME_SIZE 64
#define FILE_DATA_SIZE 1024

typedef struct File File;
typedef struct Directory Directory;

struct File {
	short id;
	char name[FILE_NAME_SIZE];
	int size;
	char data[FILE_DATA_SIZE];
	Directory *directory; 
};

struct Directory{
	char name[FILE_NAME_SIZE];
	File **files; // files in directory
	Directory **directories; //subdirectories
	unsigned char nf; // number of files in the directory
	unsigned char nd; // number of sub-directories
	char path[MAX_PATH]; // absolute path to this directory
};


// Prints the name of the File file
void show_file(File *file){
	printf("%s", file->name);
}

// Displays the content of the Directory dir
void show_dir(Directory *dir) {
	printf("\nDIRECTORY\n");
	printf(" path: %s\n", dir->path);
	printf(" files:\n");
	printf(" [ ");
	for(int i=0;i < (dir->nf); i++){
		show_file((dir->files[i]));
	}
	printf("]\n");
	printf(" directories: \n");
	printf(" { ");
	for (int i=0; i< (dir->nd);i++) {
		show_dir(dir->directories[i]);
	}
	printf("}\n");
}

// adds the subdirectory dir 1 to the directory dir2
void add_dir(Directory *dir1, Directory *dir2) {
	if(dir1 && dir2) {
		dir2->directories[dir2->nd] = dir1;
		dir2->nd++;
		char temp_path[MAX_PATH];
		if(strcmp(dir2->path, "/")) {
			strcpy(temp_path, dir2->path);
			strcat(temp_path, "/");
			strcat(temp_path, dir1->name);
			strcpy(dir1->path, temp_path);
		} else {
			strcpy(temp_path, "/");
			strcat(temp_path, dir1->name);
			strcpy(dir1->path, temp_path);
		}
	}
}
void add_file(struct File* file, struct Directory* dir) {
	// adds new file to current dir
	dir->files[dir->nf] = file;
	(dir->nf)++;
	file->directory = dir;
}

void overwrite_to_file(struct File* file, const char* str) {
	// overwrite the file content with str 
	strcpy(file->data, str);

}

void append_to_file(struct File* file, const char* str){
	// append str to end of file
	strcat(file->data, str);
}
void printp_file(struct File* file){
	// print path of file to stdout
	printf("%s/%s\n", (file->directory)->path,file->name);
}

int main(){
	unsigned int FILE_ID = 0; 
	Directory root;
	strcpy(root.name,"/");
	root.nf = 0;
	root.nd = 0;
	root.files = malloc(32*sizeof(File));
	root.directories = malloc(32*sizeof(Directory)); 
	strcpy(root.path,"");

	Directory home;
	strcpy(home.name,"home");
	home.nf = 0;
	home.nd = 0;
	home.files = malloc(32*sizeof(File));
	home.directories = malloc(32*sizeof(Directory));

	Directory bin;
	strcpy(bin.name,"bin");
	bin.nf = 0;
	bin.nd = 0;
	bin.files = malloc(32*sizeof(File));
	bin.directories = malloc(32*sizeof(Directory));
	
	//
	add_dir(&home, &root);
	add_dir(&bin, &root);
	
	// *
	File bash; strcpy(bash.name,"bash");
	bash.id = FILE_ID++;
	add_file(&bash, &bin);
	
	// *
	File ex3_1c; ex3_1c.id = FILE_ID++;
	strcpy(ex3_1c.name,"ex3_1.c");
	overwrite_to_file(&ex3_1c, "int printf(const char * format, ...);");
	add_file(&ex3_1c, &home);

	File ex3_2c; ex3_2c.id = FILE_ID++;
	strcpy(ex3_2c.name,"ex3_2.c");
	overwrite_to_file(&ex3_2c, "//This is a comment in C language");
	add_file(&ex3_2c, &home);
	// *
	append_to_file(&bash, "Bourne Again Shell!!");
	// *
	append_to_file(&ex3_1c, "int main(){printf(\"Hello World!\")");
	
	// *
	printp_file(&bash);
	printp_file(&ex3_1c);
	printp_file(&ex3_2c);
	
	return EXIT_SUCCESS;
}