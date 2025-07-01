#include "FileHandle/FilePathCollector.hpp"
#include "FilePathCollector.hpp"

namespace filehandle {

FilePathCollector::FilePathCollector(std::string rootPath, int maxDepth, const std::vector<std::string> &suffixes)
    : rootPath_(rootPath), maxDepth_(maxDepth), suffixList_(suffixes) {
  if (!collect() || !isValidDirectory()) { // check
    collected_ = false;                    // reset collected state
    throw std::runtime_error("Initial collection failed");
  }
  collected_ = true; // mark as collected after initialization
}

void FilePathCollector::setSuffixes(const std::vector<std::string> &suffixes) {
  suffixList_ = suffixes;
  clear(); // reset collected state when suffixes change
}

void FilePathCollector::setDepth(int depth) {
  maxDepth_ = depth;
  clear(); // reset collected state when depth changes
}

const std::vector<std::string> &FilePathCollector::getCollectedPaths() const { return collectedPaths_; }

void FilePathCollector::clear() {
  collectedPaths_.clear();
  collected_ = false;
}

void FilePathCollector::setRootPath(const std::string &path) {
  rootPath_ = path;
  collectedPaths_.clear(); // reset collected state when root path changes
}

bool FilePathCollector::isCollected() const { return collected_; }

bool FilePathCollector::saveToFile(const std::string &outPath) {
  std::ofstream ofs(outPath);
  if (!ofs)
    return false; // immediate failure if file cannot be opened
  if (collectedPaths_.empty()) {
    ofs << "No Path Collected!\n";
    return true;
  }
  filehandle::FileWriterHandler handler(ofs);
  for (const auto &path : collectedPaths_) {
    handler(path);
  }
  return true;
}

bool FilePathCollector::printToConsole() {
  if (!collected_)
    collect();
  if (collectedPaths_.empty())
    std::cout << "No Path Collected!\n";
  filehandle::PrintHandler handler;
  for (const auto &path : collectedPaths_) {
    handler(path);
  }
  return true;
}

bool FilePathCollector::isValidDirectory() const {
#ifdef _WIN32
  DWORD attr = GetFileAttributesA(rootPath_.c_str());
  return (attr != INVALID_FILE_ATTRIBUTES) && (attr & FILE_ATTRIBUTE_DIRECTORY);
#else
  struct stat st;
  return stat(rootPath_.c_str(), &st) == 0 && S_ISDIR(st.st_mode);
#endif
}
} // namespace filehandle