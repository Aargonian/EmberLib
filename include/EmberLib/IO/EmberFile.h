/*
 * Created by Aaron Gorodetzky on 12/8/2019.
 */

#ifndef EMBERLIB_EMBERFILE_H
#define EMBERLIB_EMBERFILE_H

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

/*
 * All files are considered to be opened in binary mode, so there is no need to
 * distinguish between binary/text. However, it must still be specified if the
 * file is for reading, writing, or both.
 *
 * This function will set the following errors under the following conditions:
 *     0. If there is insufficient memory to create the file object and handles,
 *        it will set EMBER_OUT_OF_MEMORY_ERR.
 *     1. If a File is opened as READ_ONLY, and the File DOES NOT EXIST, it will
 *        set the ember_io_err to EMBER_FILE_NOT_FOUND_ERR.
 *     2. If a File is opened as READ_ONLY, and the program does not have
 *        sufficient privileges, it will set EMBER_PERMISSION_ERR.
 */
ember_file *open_file(FILE_MODE mode);


#endif //EMBERLIB_EMBERFILE_H
