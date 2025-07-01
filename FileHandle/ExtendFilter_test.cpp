#include "FileHandle/ExtendFilter.hpp"
#include <gtest/gtest.h>

namespace filehandle {

TEST(DefaultFilterTest, AlwaysTrue) {
  DefaultFilter filter;
  EXPECT_TRUE(filter("test.txt"));
  EXPECT_TRUE(filter("image.jpg"));
  EXPECT_TRUE(filter(""));
}

TEST(ImageFilterTest, AcceptValidExtensions) {
  ImageFilter filter;
  EXPECT_TRUE(filter("photo.jpg"));
  EXPECT_TRUE(filter("image.png"));
  EXPECT_TRUE(filter("pic.bmp"));
  EXPECT_TRUE(filter("scan.tiff"));
}

TEST(ImageFilterTest, RejectInvalidExtensions) {
  ImageFilter filter;
  EXPECT_FALSE(filter("document.pdf"));
  EXPECT_FALSE(filter("archive.zip"));
  EXPECT_FALSE(filter("music.mp3"));
  EXPECT_FALSE(filter("video.mp4"));
}

TEST(ImageFilterTest, CaseSensitivity) {
  ImageFilter filter;
  EXPECT_FALSE(filter("PHOTO.JPG")); // case-sensitive check fails
}

TEST(ImageFilterTest, CustomExtensions) {
  ImageFilter filter({".jpeg", ".gif"});
  EXPECT_TRUE(filter("picture.jpeg"));
  EXPECT_TRUE(filter("animation.gif"));
  EXPECT_FALSE(filter("image.png"));
}

} // namespace filehandle
