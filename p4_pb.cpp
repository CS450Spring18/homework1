/* extract_vdso.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Problem 4 Part B
*/

int main(int argc, char **argv)
{
    char        buf[256];
    void *mem;
    const char *range_name;
    FILE       *rd, *wr;
    long long   start_addr, end_addr;

    /* Open file for writing the vdso data to */
    if (argc != 3)
    {
        fprintf(stderr,
                "Usage: %s <file> <string>\n"
                "\t<file>:   File to write the vdso data to.\n"
                "\t<string>: Name of the mapped in region, e.g. vdso\n",
                argv[0]);

        abort();
    }

    range_name = argv[2];

    if (!(wr = fopen(argv[1], "w")))
    {
        perror("Error: fopen() - output file");
        abort();
    }

    /* Get this process' memory layout */
    if (!(rd = fopen("/proc/self/maps", "r")))
    {
        perror("Error: fopen() - /proc/self/maps");
        abort();
    }

    /* Find the line in /proc/self/maps that contains 
       the substring [vdso] * */
    while (fgets(buf, sizeof(buf), rd))
    {
        if (strstr(buf, range_name))
          break;
    }

    fclose(rd);

    /* Locate the end memory range for [vdso] */
    end_addr = strtoll((strchr(buf, '-') + 1), NULL, 16);

    /* Terminate the string so we can get the start 
       address really easily * */
    *(strchr(buf, '-')) = '\0';
    start_addr = strtoll(buf, NULL, 16);

    /* Open up the memory page and extract the vdso */
    if (!(rd = fopen("/proc/self/mem", "r")))
    {
        perror("Error: fopen() - /proc/self/mem");
        abort();
    }

    /* Hop to the vdso portion */
    fseek(rd, start_addr, SEEK_SET);

    /* Copy the memory locally and then move it to the file */
    mem = malloc(end_addr - start_addr);
    if (!fread(mem, 1, end_addr - start_addr, rd))
    {
        perror("Error: read() - /proc/self/mem");
        abort();
    }

    /* Write the data to the specified output file */
    if (!fwrite(mem, 1, end_addr - start_addr, wr))
    {
        perror("Error: fwrite() - output file");
        abort();
    }

    free(mem);
    fclose(rd);
    fclose(wr);

    printf("Start: %p\nEnd:   %p\nBytes: %d\n",
            (void *)start_addr, (void *)end_addr, (int)(end_addr - start_addr));

    return 0;
}