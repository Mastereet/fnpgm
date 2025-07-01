// FilePathExtractor.hpp
#ifndef FNPGM_FILEHANDLE_FILEPATHEXTRACTOR_HPP
#define FNPGM_FILEHANDLE_FILEPATHEXTRACTOR_HPP

#include <functional>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#ifdef _WIN32
#include <windows.h>
#else
#include <dirent.h>
#include <sys/stat.h>
#endif

#include "FileHandle/ExtendFilter.hpp"

namespace filehandle {

/**
 * @brief FilePathExtractor
 * @tparam Handler: callable object, signature void(const std::string&)
 * @tparam Filter: callable object, signature bool(const std::string&)
 * @note maxDepth = -1 means no limit
 */
template <typename Handler, typename Filter = ImageFilter>
class FilePathExtractor {
public:
  FilePathExtractor(Handler h, Filter f = Filter()) : callback(h), filter(f), maxDepth(-1) {}
  /*
  @brief scan the directory and collect the files
  @param path: the path of the directory
  @param maxDepth_: the max depth of the directory, -2,-1.. means no limit
  @param suffixList: the suffix list of the files
  */
  void scan(const std::string &path, int maxDepth_ = -2, const std::vector<std::string> &suffixList = {}) {
    if (!suffixList.empty()) {
      filter = Filter(suffixList);
    }
    if (maxDepth_ != -2) {
      maxDepth = maxDepth_;
    }
    traverse(path, maxDepth);
  }

  void setDepth(int depth) { maxDepth = depth; }

  void setSuffixFilter(const std::vector<std::string> &suffixList) { filter = Filter(suffixList); }

private:
  Handler callback;
  Filter filter;
  int maxDepth;

  void traverse(const std::string &currentPath, int depth) {
    if (isDirectory(currentPath)) {
      traverseDirectory(currentPath, depth);
    } else {
      processFile(currentPath);
    }
  }

  void traverseDirectory(const std::string &dirPath, int depth) {
#ifdef _WIN32
    std::string searchPath = dirPath + "\\*";
    WIN32_FIND_DATAA ffd;
    HANDLE hFind = FindFirstFileA(searchPath.c_str(), &ffd);
    if (hFind == INVALID_HANDLE_VALUE)
      return;
    do {
      std::string name = ffd.cFileName;
      if (name == "." || name == "..")
        continue;
      std::string full = dirPath + "\\" + name;
      bool isDir = (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
#else
    DIR *dir = opendir(dirPath.c_str());
    if (!dir)
      return;
    struct dirent *ent;
    while ((ent = readdir(dir)) != nullptr) {
      std::string name = ent->d_name;
      if (name == "." || name == "..")
        continue;
      std::string full = dirPath + "/" + name;
      bool isDir = (ent->d_type == DT_DIR);
#endif
      if (isDir) {
        if (depth != 0) {
          traverse(full, depth > 0 ? depth - 1 : depth);
        }
      } else {
        processFile(full);
      }
#ifdef _WIN32
    } while (FindNextFileA(hFind, &ffd) != 0);
    FindClose(hFind);
#else
    }
    closedir(dir);
#endif
  }

  void processFile(const std::string &filePath) {
    std::string name = filePath.substr(filePath.find_last_of("/\\") + 1);
    if (filter(name)) {
      callback(filePath);
    }
  }

  bool isDirectory(const std::string &path) {
#ifdef _WIN32
    DWORD attr = GetFileAttributesA(path.c_str());
    return (attr != INVALID_FILE_ATTRIBUTES) && (attr & FILE_ATTRIBUTE_DIRECTORY);
#else
    struct stat st;
    return stat(path.c_str(), &st) == 0 && S_ISDIR(st.st_mode);
#endif
  }
};

/*
    @brief Handler one: print the file path to standard output
    @param path: the file path
    how to use:
    filehandle::FilePathExtractor<decltype(printHandler)> extractor(printHandler);
    extractor.scan("path", 2);
*/
// auto printHandler = [](const std::string &path) { std::cout << "Fond: " << path << std::endl; };

/*
@brief Handler two: write the file path to a file
    @param path: the file path
    how to use:
    std::ofstream ofs("path.txt");
    filehandle::FilePathExtractor<decltype(fileWriterHandler)> extractor(fileWriterHandler);
    extractor.setSuffixFilter({".txt"});
    extractor.setDepth(2);
    extractor.scan("path");
*/
// auto fileWriterHandler = [&ofs](const std::string &path) { ofs << path << "\n"; };

/*
    @brief Handler three: collect the file path
    @param path: the file path
    how to use:
    std::vector<std::string> collectedPaths;
    filehandle::FilePathExtractor<decltype(collectHandler)> extractor(collectHandler);
    extractor.scan("path", 2, {".cpp", ".hpp"});
*/
// auto collectHandler = [](const std::string &path) { collectedPaths.push_back(path); };

struct PrintHandler {
  void operator()(const std::string &path) const { std::cout << "Found: " << path << std::endl; }
};

struct FileWriterHandler {
  std::ofstream &ofs;
  explicit FileWriterHandler(std::ofstream &stream) : ofs(stream) {}
  void operator()(const std::string &path) const { ofs << path << "\n"; }
};

struct CollectHandler {
  std::vector<std::string> &collected;
  explicit CollectHandler(std::vector<std::string> &vec) : collected(vec) {}
  void operator()(const std::string &path) const { collected.push_back(path); }
};

} // namespace filehandle

#endif // FNPGM_FILEHANDLE_FILEPATHEXTRACTOR_HPP
