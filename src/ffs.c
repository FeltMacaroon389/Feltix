// FFS (Felt File-System)

#include <ffs.h>

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <vga.h>

FeltFileSystem fs;

// Create a file
int ffs_create_file(const char *name) {
    if (strlen(name) >= FFS_MAX_FILENAME_LENGTH) {
        return FFS_INVALID_NAME;
    }

    for (int i = 0; i < FFS_MAX_FILES; i++) {
        if (fs.files[i].is_used && strcmp(fs.files[i].name, name) == 0) {
            return FFS_FILE_EXISTS;
        }
    }

    for (int i = 0; i < FFS_MAX_FILES; i++) {
        if (!fs.files[i].is_used) {
            fs.files[i].is_used = 1;
            memcpy(fs.files[i].name, name, strlen(name));
            fs.files[i].name[strlen(name)] = '\0';
            fs.files[i].size = 0;

            // Clear any residual data
            for (size_t j = 0; j < FFS_MAX_FILE_SIZE; j++) {
                fs.files[i].data[j] = '\0';
            }

            return FFS_SUCCESS;
        }
    }

    return FFS_NO_SPACE;
}


// Delete a file
int ffs_delete_file(const char *name) {
    for (int i = 0; i < FFS_MAX_FILES; i++) {
        if (fs.files[i].is_used && strcmp(fs.files[i].name, name) == 0) {
            fs.files[i].is_used = 0;
            fs.files[i].size = 0;

            for (int j = 0; j < FFS_MAX_FILENAME_LENGTH; j++) {
                fs.files[i].name[j] = '\0';
            }
            for (int j = 0; j < FFS_MAX_FILE_SIZE; j++) {
                fs.files[i].data[j] = '\0';
            }

            return FFS_SUCCESS;
        }
    }

    return FFS_FILE_NOT_FOUND;
}

// Write data to a file
int ffs_write_file(const char *name, const char *data) {
    size_t data_length = strlen(data);

    if (data_length > FFS_MAX_FILE_SIZE) {
        return FFS_SIZE_EXCEEDS_LIMIT;
    }

    for (int i = 0; i < FFS_MAX_FILES; i++) {
        if (fs.files[i].is_used && strcmp(fs.files[i].name, name) == 0) {
            // Clear the buffer before writing to avoid leftover data
            memset(fs.files[i].data, 0, FFS_MAX_FILE_SIZE);

            memcpy(fs.files[i].data, data, data_length);
            fs.files[i].size = data_length;
            return FFS_SUCCESS;
        }
    }

    return FFS_FILE_NOT_FOUND;
}


// Read data from a file
int ffs_read_file(const char *name, char *buffer, size_t buffer_size) {
    for (int i = 0; i < FFS_MAX_FILES; i++) {
        if (fs.files[i].is_used && strcmp(fs.files[i].name, name) == 0) {
            size_t file_size = fs.files[i].size;

            if (buffer_size < file_size + 1) {
                return FFS_BUFFER_TOO_SMALL;
            }

            memcpy(buffer, fs.files[i].data, file_size);
            buffer[file_size] = '\0';
            return (int)file_size;
        }
    }
    return FFS_FILE_NOT_FOUND;
}

// Check if there are any files present in the filesystem
int ffs_are_files_present(void) {
    for (int i = 0; i < FFS_MAX_FILES; i++) {
        if (fs.files[i].is_used) {
            return 1; // There is at least one file
        }
    }

    return 0; // No files present
}

// List all files (print to VGA)
void ffs_list_files(void) {
    if (ffs_are_files_present() == 1) {

        for (int i = 0; i < FFS_MAX_FILES; i++) {
            if (fs.files[i].is_used) {
                print_string(fs.files[i].name, VGA_COLOR_LIGHT_GREY);
                print_string(" ", VGA_COLOR_BLACK);
            }
        }

        print_string("\n", VGA_COLOR_BLACK);
    }
}

