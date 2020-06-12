#include <stdio.h>
#include <unistd.h> 
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char*argv[]){

    char filename[20];
    char filename2[20];
    int file1, file2, r;
    char buffer[100];

/*
    This will be our user input, the screen will prompt for the user to enter a file 
    to be copied and a file to be the destination, and we will accept this value and 
    move on to opening up the files.
 */
    printf("Please enter a file to copy: \n");
    scanf("%s", filename);

    printf("Please enter the destination file name: \n");
    scanf("%s", filename2);
    
/*
    We will open the source file and destination file, source file will be open for 
    readonly, the destination file will be created and write only with permissions. 
    0700 gives all rights to the owner of the file and no permisson to any other user.
    If the files are not found/created then an error message will pop up and the program
    will exit. 
 */

    if(((file1 = open(filename, O_RDONLY))== -1 || ((file2 = open(filename2, O_CREAT|O_WRONLY, 0700))== -1))){
        perror("There was an error opening/creating file: ");
        exit(1);
    }

/*
    In these statements, we will read and write, basically copy the source to the destination file.
    We have our loop here, we will read file1, copy contents to buffer, returns number of bytes read.
    If greater than zero than we continue, if less than 0 than we will exit loop. Then we will write
    to file2 from what we read in file1. Now if it doesnt equal to r than we will have a writing error,
    meaning we didnt copy the file properly. 
 */
    while((r = read(file1, buffer, sizeof(buffer))) > 0){
        if(write(file2, buffer, r) != r){
            perror("Error copying: ");
            exit(1);
        }
    }

/*
    These will close the source file and destination files. 
 */
    close(file2);
    close(file1);

    printf("Source file %s is copied to destination file: %s \n", filename, filename2);

    return(0);
}   

