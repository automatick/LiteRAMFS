#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <stdexcept>

using str = std::string;
template <typename T>
using vec = std::vector<T>;

struct File {
    str filename;
    str content;
};

struct Folder {
    str name;
    vec<File*> files;
    vec<Folder> subfolders;
};

struct Root {
    vec<Folder> folders;
};

vec<str> split_path(const str &path) {
    vec<str> parts;
    std::stringstream ss(path);
    str part;
    while (std::getline(ss, part, '/')) {
        if (!part.empty()) {
            parts.push_back(part);
        }
    }
    return parts;
}

Folder* create_folder_by_path(Root *root, const str &path) {
    auto parts = split_path(path);
    if (parts.empty()) {
        return nullptr;
    }

    Folder *current_folder = nullptr;

    for (auto &folder : root->folders) {
        if (folder.name == parts[0]) {
            current_folder = &folder;
            break;
        }
    }

    if (!current_folder) {
        root->folders.push_back({parts[0], {}, {}});
        current_folder = &root->folders.back();
    }

    for (size_t i = 1; i < parts.size(); ++i) {
        auto it = std::find_if(
            current_folder->subfolders.begin(),
            current_folder->subfolders.end(),
            [&parts, i](const Folder &f) { return f.name == parts[i]; }
            );

        if (it == current_folder->subfolders.end()) {
            current_folder->subfolders.push_back({parts[i], {}, {}});
            current_folder = &current_folder->subfolders.back();
        } else {
            current_folder = &(*it);
        }
    }

    return current_folder;
}

File* create_file_by_path(Root *root, const str &path, const str &filename, const str &content) {
    Folder *folder = create_folder_by_path(root, path);
    if (!folder) {
        return nullptr;
    }
    File *file = new File{filename, content};
    folder->files.push_back(file);
    return file;
}

File* find_file_by_path(const Root *root, const str &path) {
    auto parts = split_path(path);
    if (parts.empty()) {
        return nullptr;
    }

    const Folder *current_folder = nullptr;

    for (const auto &folder : root->folders) {
        if (folder.name == parts[0]) {
            current_folder = &folder;
            break;
        }
    }

    if (!current_folder) {
        return nullptr;
    }

    for (size_t i = 1; i < parts.size() - 1; ++i) {
        auto it = std::find_if(
            current_folder->subfolders.begin(),
            current_folder->subfolders.end(),
            [&parts, i](const Folder &f) { return f.name == parts[i]; }
            );

        if (it == current_folder->subfolders.end()) {
            return nullptr;
        }

        current_folder = &(*it);
    }
    auto it = std::find_if(
        current_folder->files.begin(),
        current_folder->files.end(),
        [&parts](const File *f) { return f->filename == parts.back(); }
        );

    if (it != current_folder->files.end()) {
        return *it;
    }

    return nullptr;
}

str read_file_by_path(const Root *root, const str &path) {
    File *file = find_file_by_path(root, path);
    if (!file) {
        throw std::runtime_error("File not found: " + path);
    }
    return file->content;
}

int rm(File *file, Folder *folder) {
    auto it = std::find_if(
        folder->files.begin(),
        folder->files.end(),
        [file](File* f) { return f == file; }
        );

    if (it != folder->files.end()) {
        delete *it;
        folder->files.erase(it);
        return 0;
    }

    return -1;
}

int rmdir(Folder *parent, const str &foldername) {
    auto it = std::find_if(
        parent->subfolders.begin(),
        parent->subfolders.end(),
        [&foldername](const Folder &f) { return f.name == foldername; }
        );

    if (it != parent->subfolders.end()) {
        for (File* file : it->files) {
            delete file;
        }
        parent->subfolders.erase(it);
        return 0;
    }

    return -1;
}

void cleanup_folder(Folder &folder) {
    for (File* file : folder.files) {
        delete file;
    }
    for (Folder &subfolder : folder.subfolders) {
        cleanup_folder(subfolder);
    }
}

void cleanup_root(Root &root) {
    for (Folder &folder : root.folders) {
        cleanup_folder(folder);
    }
}

int main() {
    Root root;
    create_folder_by_path(&root, "/root/files");
    create_file_by_path(&root, "/root/files", "main.txt", "hello world");

    try {
        str content = read_file_by_path(&root, "/root/files/main.txt");
        std::cout << "File content: " << content << std::endl;
    } catch (const std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
    }

    cleanup_root(root);

    return 0;
}
