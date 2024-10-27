#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

void write_file(int fileno)
{
    int fd;
    int num;
    char filename[10];
    char buffer[16];
    ssize_t data_read;

    sprintf(filename, "%d.dat", fileno);
    
    if (access(filename, F_OK) != 0)
    {
        fd = open(filename, O_CREAT); 
        if (fd < 0)
        {
            printf("error creating file.");
            return;
        }
        close(fd);
        return;
    }

    fd = open(filename, O_RDWR);
    if (fd < 0)
    {
        printf("error opening file on file %d.", fileno);
        return;
    }

    data_read = read(fd, buffer, sizeof(buffer) - 1);
    if (data_read < 0) {
        perror("error reading file");
        close(fd);
        return;
    }
    buffer[data_read] = '\0';

    if (data_read == 0)
    {
        lseek(fd, 0, SEEK_SET);
        write(fd, "1", 1);
        close(fd);
    }
    else
    {
        num = atoi(buffer);
        if (num < 10)
        {
            num++;
            sprintf(buffer, "%d", num);
            lseek(fd, 0, SEEK_SET);
            write(fd, buffer, strlen(buffer));
            close(fd);
        }
        else
        {
            close(fd);
            if (remove(filename) != 0)
            {
                printf("error deleting files.");
            }
            return;
        }
    }
}

int main()
{
    int i = 1;

    for (i = 1; i <= 1024; i++)
    {
        write_file(i);
    }
    return 0;
}
