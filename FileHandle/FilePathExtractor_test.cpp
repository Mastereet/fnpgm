#include "FileHandle/FilePathExtractor.hpp"
#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>

namespace fs = std::filesystem;
namespace filehandle {

class FilePathExtractorTest : public ::testing::Test {
protected:
  std::string testDir;
  std::vector<std::string> collectedPaths;
  /*
  test_data_dir/
  ├── a.jpg          <-- be collected (depth = 0)
  ├── b.txt          <-- not match default image suffix, ignored
  ├── c.png          <-- be collected (depth = 0)
  └── sub/
      ├── d.bmp      <-- be collected (depth = 1)
      └── e.docx     <-- invalid extension, always ignored
  */
  void SetUp() override {
    testDir = "test_data_dir";
    fs::create_directory(testDir);
    std::ofstream(testDir + "/a.jpg");
    std::ofstream(testDir + "/b.txt");
    std::ofstream(testDir + "/c.png");
    fs::create_directory(testDir + "/sub");
    std::ofstream(testDir + "/sub/d.bmp");
    std::ofstream(testDir + "/sub/e.docx");
  }

  void TearDown() override {
    fs::remove_all(testDir);
    collectedPaths.clear();
  }

  void collectCallback(const std::string &path) { collectedPaths.push_back(path); }
};

TEST_F(FilePathExtractorTest, DefaultImageFilterCollectsImagesOnly) {
  FilePathExtractor<std::function<void(const std::string &)>> extractor(
      [this](const std::string &path) { collectCallback(path); });

  extractor.scan(testDir);
  EXPECT_EQ(collectedPaths.size(), 3); // a.jpg, c.png, sub/d.bmp

  for (const std::string &path : collectedPaths) {
    EXPECT_TRUE(path.find(".jpg") != std::string::npos || path.find(".png") != std::string::npos ||
                path.find(".bmp") != std::string::npos);
  }
}

TEST_F(FilePathExtractorTest, CustomFilterCollectsTxtOnly) {
  FilePathExtractor<std::function<void(const std::string &)>, ImageFilter> extractor(
      [this](const std::string &path) { collectCallback(path); });

  extractor.scan(testDir, -1, {".txt"});
  ASSERT_EQ(collectedPaths.size(), 1);
  EXPECT_TRUE(collectedPaths[0].find("b.txt") != std::string::npos);
}

TEST_F(FilePathExtractorTest, DepthLimitingWorks) {
  FilePathExtractor<std::function<void(const std::string &)>> extractor(
      [this](const std::string &path) { collectCallback(path); });

  extractor.setDepth(0);
  extractor.scan(testDir);
  ASSERT_EQ(collectedPaths.size(), 2); // only a.jpg and c.png at root
}

} // namespace filehandle
