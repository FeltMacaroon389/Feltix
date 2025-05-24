#ifndef FFS_H
#define FFS_H

#include <stddef.h>
#include <stdint.h>

#define FFS_MAX_FILES 128
#define FFS_MAX_FILENAME_LENGTH 64
#define FFS_MAX_FILE_SIZE 4096 // 4KB

// Error Codes
#define FFS_SUCCESS 0
#define FFS_FILE_EXISTS -1
#define FFS_NO_SPACE -2
#define FFS_FILE_NOT_FOUND -3
#define FFS_INVALID_NAME -4
#define FFS_SIZE_EXCEEDS_LIMIT -5
#define FFS_BUFFER_TOO_SMALL -6
#define FFS_INVALID_OPERATION -8

// File structure
typedef struct {
    char name[FFS_MAX_FILENAME_LENGTH];
    char data[FFS_MAX_FILE_SIZE];
    size_t size;
    int is_used;
} File;

// Filesystem structure
typedef struct {
    File files[FFS_MAX_FILES];
} FeltFileSystem;

extern FeltFileSystem fs;

int ffs_create_file(const char *name);
int ffs_delete_file(const char *name);
int ffs_write_file(const char *name, const char *data);
int ffs_read_file(const char *name, char *buffer, size_t buffer_size);
int ffs_are_files_present(void);
void ffs_list_files(void);

#endif // FFS_H

