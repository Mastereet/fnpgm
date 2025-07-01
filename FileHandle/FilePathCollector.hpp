#ifndef FNPGM_FILEHANDLE_FILEPATHCOLLECTOR_HPP
#define FNPGM_FILEHANDLE_FILEPATHCOLLECTOR_HPP

#include "FileHandle/FilePathExtractor.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace filehandle {

class FilePathCollector {
public:
  FilePathCollector() = default;
  FilePathCollector(std::string rootPath, int maxDepth, const std::vector<std::string> &suffixes);

  void setSuffixes(const std::vector<std::string> &suffixes);
  void setDepth(int depth);
  const std::vector<std::string> &getCollectedPaths() const;
  void clear();

  void setRootPath(const std::string &path);
  const std::string &getRootPath() const { return rootPath_; }

  // need inline
  bool collect() {
    if (rootPath_.empty())
      return false;
    collectedPaths_.clear();
    filehandle::CollectHandler handler(collectedPaths_);
    filehandle::FilePathExtractor<filehandle::CollectHandler> extractor(handler);
    extractor.scan(rootPath_, maxDepth_, suffixList_);
    collected_ = true;
    return true;
  }
  bool isCollected() const;

  bool saveToFile(const std::string &outPath);
  bool printToConsole();

private:
  bool isValidDirectory() const;

  int maxDepth_ = -1;
  std::vector<std::string> suffixList_;
  std::string rootPath_;
  std::vector<std::string> collectedPaths_;
  bool collected_ = false;
};

} // namespace filehandle

#endif // FNPGM_FILEHANDLE_FILEPATHCOLLECTOR_HPP