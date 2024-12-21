### LiteRAMFS: Lightweight RAM-based File System

LiteRAMFS is a lightweight in-memory file system designed for managing files and folders directly in RAM. It provides basic operations like creating, reading, and deleting files and folders, making it ideal for temporary data storage, testing, and educational purposes.

---

## Features

- **RAM-based storage**: Data is stored in memory for high-speed access.
- **Hierarchical structure**: Supports nested folders and files.
- **Basic file operations**: Create, read, and delete files and folders.
- **Dynamic memory management**: Automatically handles memory allocation for files and folders.
- **Simple API**: Easy to integrate and use in custom projects.

---

## Installation

Clone the repository and include the `LiteRAMFS` files in your project:
```bash
git clone https://github.com/automatick/LiteRAMFS.git
cd LiteRAMFS
```

Include the header files in your project:
```cpp
#include "literamfs.hpp"
```

---

## API Overview

Here is an overview of the main functions provided by LiteRAMFS:

### Folder and File Operations

1. **Create a folder by path**:
   ```cpp
   Folder* create_folder_by_path(Root *root, const str &path);
   ```
   - **Parameters**: 
     - `root`: The root of the file system.
     - `path`: Absolute path to the folder (e.g., `/root/docs`).
   - **Returns**: A pointer to the created or existing folder.

2. **Create a file by path**:
   ```cpp
   File* create_file_by_path(Root *root, const str &path, const str &filename, const str &content);
   ```
   - **Parameters**: 
     - `root`: The root of the file system.
     - `path`: Path to the folder where the file will be created.
     - `filename`: Name of the file.
     - `content`: Initial content of the file.
   - **Returns**: A pointer to the created file.

3. **Find a file by path**:
   ```cpp
   File* find_file_by_path(const Root *root, const str &path);
   ```
   - **Parameters**:
     - `root`: The root of the file system.
     - `path`: Full path to the file (e.g., `/root/docs/file.txt`).
   - **Returns**: A pointer to the file if found, or `nullptr` if not found.

4. **Read a file by path**:
   ```cpp
   str read_file_by_path(const Root *root, const str &path);
   ```
   - **Parameters**: 
     - `root`: The root of the file system.
     - `path`: Path to the file.
   - **Returns**: The content of the file.

5. **Delete a file**:
   ```cpp
   int rm(File *file, Folder *folder);
   ```
   - **Parameters**:
     - `file`: Pointer to the file to be deleted.
     - `folder`: Folder containing the file.
   - **Returns**: `0` on success, `-1` if the file was not found.

6. **Delete a folder**:
   ```cpp
   int rmdir(Folder *parent, const str &foldername);
   ```
   - **Parameters**:
     - `parent`: Parent folder containing the folder to be deleted.
     - `foldername`: Name of the folder to be deleted.
   - **Returns**: `0` on success, `-1` if the folder was not found.

7. **Cleanup memory**:
   ```cpp
   void cleanup_root(Root &root);
   ```
   - **Parameters**: 
     - `root`: The root of the file system.
   - Cleans up all dynamically allocated memory for files and folders.

---

## Usage Example

Here’s a simple example of using LiteRAMFS:

```cpp
#include "literamfs.hpp"
#include <iostream>

int main() {
    Root root;

    // Create folders and files
    create_folder_by_path(&root, "/root/files");
    create_file_by_path(&root, "/root/files", "example.txt", "This is an example file.");

    // Read file content
    try {
        str content = read_file_by_path(&root, "/root/files/example.txt");
        std::cout << "File content: " << content << std::endl;
    } catch (const std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
    }

    // Cleanup memory
    cleanup_root(root);

    return 0;
}
```

---

## Use Cases

1. **Temporary data storage**:
   - Use LiteRAMFS for storing temporary data that doesn't need to persist between program runs.

2. **Testing file-based logic**:
   - Simulate file systems in unit tests without writing to the actual disk.

3. **Educational purposes**:
   - Learn about file systems and hierarchical data structures.

4. **Prototyping**:
   - Quickly prototype applications that require file system-like behavior without needing disk I/O.

---

## Limitations

- Data is stored in memory and will be lost when the program exits.
- Does not support advanced features like permissions, symlinks, or concurrent access.

---

## Contributions

Contributions are welcome! Feel free to fork the repository, make changes, and submit pull requests. For major changes, please open an issue first to discuss what you would like to change.

---

## License

This project is licensed under the MIT License. See the `LICENSE` file for more details.

---
