/*
 * Created by Aaron Helton on 11/22/19
 */
#include <EmberLib/Util/EmberList.h>
#include <EmberLib/IO/EmberFile.h>
#include <stdio.h>

int main(void)
{
    EmberString *file_path = create_estring_from_cstr("./Test.txt", 1000);
    EmberFile *file = efile_open(file_path, READ_ONLY, FALSE);
    destroy_estring(file_path);
    file_path = NULL;

    if(!file)
    {
        fprintf(stderr, "There was an issue opening the file!\n");
        return -1;
    }

    char *text = malloc(sizeof(char)*1000);
    uint64 read = efile_read(file, text, 1000);
    text[read] = '\0';

    if(!efile_eof_reached(file))
    {
        fprintf(stderr, "There was a lot more text than expected! We got this: \n");
    } else {
        fprintf(stdout, "We got this data: \n");
    }
    fprintf(stdout, "%s", text);
    free(text);
    efile_close(file);

    fprintf(stdout, "Additional Data Gathered: \n");
    fprintf(stdout, "Total Data Read: %d Bytes\n", read);
    return 0;
}
