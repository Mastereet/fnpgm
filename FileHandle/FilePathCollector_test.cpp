#include "FileHandle/FilePathCollector.hpp"
#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>

namespace fs = std::filesystem;
namespace filehandle {

class FilePathCollectorTest : public ::testing::Test {
protected:
  std::string testRoot;

  void SetUp() override {
    testRoot = "test_data/fpc_test";
    fs::remove_all(testRoot);
    fs::create_directories(testRoot + "/level1/level2");
    std::ofstream(testRoot + "/a.jpg");
    std::ofstream(testRoot + "/b.png");
    std::ofstream(testRoot + "/c.txt");
    std::ofstream(testRoot + "/level1/x.jpg");
    std::ofstream(testRoot + "/level1/y.png");
    std::ofstream(testRoot + "/level1/level2/z.bmp");
  }

  void TearDown() override { fs::remove_all(testRoot); }
};

TEST_F(FilePathCollectorTest, ConstructorAndCollect) {
  FilePathCollector collector(testRoot, -1, {".jpg", ".png"});
  EXPECT_TRUE(collector.isCollected());
  EXPECT_EQ(collector.getCollectedPaths().size(), 4);
}

TEST_F(FilePathCollectorTest, SettersInvalidateCollect) {
  FilePathCollector collector(testRoot, -1, {".jpg"});
  EXPECT_TRUE(collector.isCollected());
  collector.setSuffixes({".txt"});
  EXPECT_FALSE(collector.isCollected());
  collector.setDepth(1);
  EXPECT_FALSE(collector.isCollected());
  collector.setRootPath(testRoot + "/level1");
  EXPECT_FALSE(collector.isCollected());
}

TEST_F(FilePathCollectorTest, SaveToFile) {
  FilePathCollector collector(testRoot, -1, {".jpg"});
  std::string outputPath = testRoot + "/output.txt";
  EXPECT_TRUE(collector.saveToFile(outputPath));
  std::ifstream ifs(outputPath);
  std::string line;
  int count = 0;
  while (std::getline(ifs, line)) {
    if (!line.empty())
      ++count;
  }
  EXPECT_EQ(count, 2);
}

TEST_F(FilePathCollectorTest, PrintToConsoleDoesNotCrash) {
  FilePathCollector collector(testRoot, -1, {".bmp"});
  testing::internal::CaptureStdout();
  collector.printToConsole();
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_NE(output.find(".bmp"), std::string::npos);
}

TEST_F(FilePathCollectorTest, InvalidRootPathDoesNotThrow) {
  EXPECT_THROW(FilePathCollector("non_existent_path", -1, {".jpg"}), std::runtime_error);
}

TEST_F(FilePathCollectorTest, EmptyDirectoryReturnsEmptyCollection) {
  fs::create_directories(testRoot + "/empty");
  FilePathCollector collector(testRoot + "/empty", -1, {".jpg"});
  EXPECT_TRUE(collector.isCollected());
  EXPECT_TRUE(collector.getCollectedPaths().empty());
}

TEST_F(FilePathCollectorTest, NoMatchingSuffixFilesReturnsEmpty) {
  FilePathCollector collector(testRoot, -1, {".md", ".exe"});
  EXPECT_TRUE(collector.isCollected());
  EXPECT_TRUE(collector.getCollectedPaths().empty());
}

TEST_F(FilePathCollectorTest, SaveToFileWithNoCollectedFiles) {
  FilePathCollector collector(testRoot, -1, {".unknown"});
  collector.collect();
  std::string outputPath = testRoot + "/empty_output.txt";
  EXPECT_TRUE(collector.saveToFile(outputPath));
  std::ifstream ifs(outputPath);
  std::string line;
  std::getline(ifs, line);
  EXPECT_EQ(line, "No Path Collected!");
}

} // namespace filehandle