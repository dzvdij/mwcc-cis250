#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
 
#define BUFFER_SIZE 4096
 
int main(int argc, char *argv[])
{
    int source_fd;
    int destination_fd;
 
    ssize_t bytes_read;
    ssize_t bytes_written;
 
    char buffer[BUFFER_SIZE];
 
    /*
     * The program should be executed as:
     *
     *     ./copy2 source destination
     *
     * Check that the user supplied the correct number
     * of command-line arguments.
     */
     
     if (argc != 3)
     {
     	printf("User did not supply correct command-line argument. -> ./copy2 source destination\n");
     	return 1;
     }
 
    /*
     * Open the source file for reading.
     *
     * Hint:
     *     Which flag opens a file for reading only?
     *
     * Remember to check whether open() was successful.
     */
     
     source_fd = open(argv[1], O_RDONLY);
     
     if (source_fd == -1)
     {
     	perror("Error with opening source file.\n");
     	return 1;
     }
 
    /*
     * Open the destination file for writing.
     *
     * Hint:
     *     You need to:
     *       - open the file for writing
     *       - create it if it does not exist
     *       - replace its existing contents
     *
     * What flags do you need?
     *
     * If open() fails, make sure you close the source
     * file before exiting.
     */
     
     destination_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
     
     if (destination_fd == -1) 
     {
     	perror("Error with opening destination file.\n");
     	close(source_fd);
     	return 1;
     }
 
    /*
     * Read the source file a chunk at a time.
     *
     * Hint:
     *
     *     read(source_fd, buffer, BUFFER_SIZE)
     *
     * What does read() return?
     *
     * Think about the three possible situations:
     *
     *     > 0    bytes were read
     *      0     end of file
     *     -1     an error occurred
     *
     * Write the data that was read to the destination file.
     *
     * Hint:
     *
     *     write(destination_fd, buffer, bytes_read)
     *
     * Check the return value of write().
     */
    
     while ((bytes_read = read(source_fd, buffer, BUFFER_SIZE)) > 0)
     {
     	bytes_written = write(destination_fd, buffer, bytes_read);
     	
    	if (bytes_written == -1)
 	{
 	       perror("Error with writing to the destination file.\n");
 	       return 1;
    }
}
 
    /*
     * What happens if write() writes fewer bytes than
     * bytes_read?
     *
     * For this lab, make sure you understand why this
     * can be a problem.
     *
     * Check whether the final call to read() failed.
     *
     * Remember:
     *
     *     read() returns -1 when an error occurs.
     */
     
     if (bytes_read == -1)
     {
     	perror("Error with reading the source file.\n");
     	return 1;
}
 
    /*
     * Close both files.
     *
     * Hint:
     *
     *     close(file_descriptor)
     *
     * A file descriptor is a resource. Your program should
     * release resources when it is finished using them.
     */
     
     close(source_fd);
     close(destination_fd);
 
    /*
     * Display a message showing that the copy completed.
     */
 
    printf("Copy has been completed.\n");
    return 0;
}
