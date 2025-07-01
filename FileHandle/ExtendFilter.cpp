#include "FileHandle/ExtendFilter.hpp"
#include <algorithm>
namespace filehandle {

bool DefaultFilter::operator()(const std::string &filename) const { return true; }

ImageFilter::ImageFilter(const std::vector<std::string> &exts) : suffixes(exts) {}

bool ImageFilter::operator()(const std::string &filename) const {
  // check if filename ends with any of the suffixes
  return std::any_of(suffixes.begin(), suffixes.end(), [&filename](const std::string &ext) {
    return filename.size() >= ext.size() && filename.compare(filename.size() - ext.size(), ext.size(), ext) == 0;
  });
}

} // namespace filehandle
