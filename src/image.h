#pragma once

#include <cstdint>
#include <string>
#include <vector>

// RGBA8 image, straight alpha.
struct Image {
    int w = 0, h = 0;
    std::vector<uint8_t> px;

    bool empty() const { return w == 0 || h == 0; }
};

bool loadImage(const std::string& path, Image& out);
bool loadImageMemory(const std::string& bytes, Image& out);
bool loadQoi(const std::string& path, Image& out);
bool saveQoi(const std::string& path, const Image& img);

// Animated GIF: every frame composited and covered to w x h. Frames are dropped evenly (their delays
// merged) so that the decoded sequence stays under maxBytes. Delays are in milliseconds, at least 20.
struct ImageSeq {
    std::vector<Image> frames;
    std::vector<int> delaysMs;
};
bool loadGifSeq(const std::string& path, int w, int h, size_t maxBytes, ImageSeq& out);

Image resize(const Image& src, int w, int h);
Image cover(const Image& src, int w, int h);
Image contain(const Image& src, int maxW, int maxH, float maxScale);
void roundCorners(Image& img, float radius);
void blur(Image& img, int radius, int passes);
void darken(Image& img, float factor);
void composite(Image& dst, const Image& src, int x, int y);  // src over dst, straight alpha
