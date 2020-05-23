/*
 * Created by Aaron Gorodetzky on 12/8/2019.
 */

#ifndef EMBERLIB_EMBERFILE_H
#define EMBERLIB_EMBERFILE_H

#include <EmberLib/Util/EmberDefines.h>
#include <EmberLib/Util/EmberString.h>

/*
 * TODO: Eventually, we'll need some preprocessor magic to change the type of
 *       EmberFile to match the platform we are on. For now, using stdio as
 *       implemented in EmberGenericFile will have to do.
 */
typedef struct EmberGenericFile EmberFile;

typedef enum EmberIOErr {
    EMBER_NO_ERR             = 0x00000000,
    EMBER_FILE_NOT_FOUND_ERR = 0x00000001,
    EMBER_PERMISSION_ERR     = 0x00000002,
    EMBER_OUT_OF_MEMORY_ERR  = 0x00000004
} EmberIOErr;

typedef enum EmberFileMode {
    READ_ONLY,
    WRITE_ONLY,
    READ_AND_WRITE
} EmberFileMode;

EmberFile *efile_open(EmberString *path, EmberFileMode mode, bool create);
uint64 efile_read(EmberFile *file, void *buffer, uint64 buffer_len);
//uint64 efile_write(EmberFile *file, void *buffer, uint64 buffer_size);
//void efile_flush(EmberFile *file);
void efile_close(EmberFile *file);
bool efile_eof_reached(EmberFile *file);


#endif //EMBERLIB_EMBERFILE_H
