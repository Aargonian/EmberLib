/*
 * Created by Aaron Gorodetzky on 12/8/2019.
 */

#include <EmberLib/IO/EmberFile.h>
#include <EmberLib/Util/EmberString.h>
#include <stdio.h>

struct EmberGenericFile
{
    FILE *file;
    uint64 current_loc;
    uint64 file_size;
    bool eof_reached;
};

/* TODO: Add proper error handling and checking */
EmberFile *efile_open(EmberString *path, EmberFileMode mode, bool create)
{
    EmberFile *efile = malloc(sizeof(EmberFile));
    if(!efile)
    {
        return NULL;
    }

    char *file_mode;
    switch(mode)
    {
        case READ_ONLY:
            file_mode = "rb";
            break;
        case WRITE_ONLY:
            file_mode = "wb";
            break;
        case READ_AND_WRITE:
            file_mode = "ab";
            break;
        default:
            return NULL;
    }

    efile->file = fopen(path->c_str, file_mode);
    if(!efile->file)
    {
        return NULL;
    }

    fseek(efile->file, 0, SEEK_END);
    efile->file_size = ftell(efile->file);
    fseek(efile->file, 0, SEEK_SET);
    efile->current_loc = ftell(efile->file);
    efile->eof_reached = FALSE;
    return efile;
}

uint64 efile_read(EmberFile *efile, void *buffer, uint64 buffer_size)
{
    if(!efile || !efile->file || efile->eof_reached)
    {
        return 0;
    }
    uint64 amount_read = fread(buffer, sizeof(char), buffer_size, efile->file);

    if(amount_read < buffer_size)
    {
        if(feof(efile->file))
        {
            efile->eof_reached = TRUE;
        } else {
            /* TODO: ERROR HERE */
        }
    }
    return amount_read;
}

bool efile_eof_reached(EmberFile *file)
{
    return file->eof_reached;
}

void efile_close(EmberFile *efile)
{
    if(!efile)
        return;
    if(efile->file)
    {
        fclose(efile->file);
        efile->file = NULL;
    }
    free(efile);
}
