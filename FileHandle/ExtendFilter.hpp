#ifndef FNPGM_FILEHANDLE_EXTENDFILTER_HPP
#define FNPGM_FILEHANDLE_EXTENDFILTER_HPP

#include <string>
#include <vector>
namespace filehandle {

// default filter, accept all
struct DefaultFilter {
  bool operator()(const std::string &filename) const;
};

// image extension filter
struct ImageFilter {
  explicit ImageFilter(const std::vector<std::string> &exts = {".jpg", ".png", ".bmp", ".tiff"});

  bool operator()(const std::string &filename) const;

private:
  std::vector<std::string> suffixes;
};

} // namespace filehandle

#endif // FNPGM_FILEHANDLE_EXTENDFILTER_HPP
