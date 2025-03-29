#ifndef IMAGE_PIXEL_H
#define IMAGE_PIXEL_H

#include <vector>
#include <string>
#include <cstdint>
#include <stdexcept>

// Forward declarations from stb
extern "C" {
    unsigned char* stbi_load(char const* filename, int* x, int* y, int* comp, int req_comp);
    void stbi_image_free(void* retval_from_stbi_load);
    int stbi_write_png(char const* filename, int w, int h, int comp, const void* data, int stride_in_bytes);
    int stbi_write_jpg(char const* filename, int w, int h, int comp, const void* data, int quality);
}

// Represents a single pixel with RGB channels
struct Pixel {
    uint8_t r, g, b;
    Pixel() : r(0), g(0), b(0) {}
    Pixel(uint8_t red, uint8_t green, uint8_t blue) : r(red), g(green), b(blue) {}
};

class ImagePixel {
public:
    ImagePixel();
    ~ImagePixel();
    bool loadImage(const std::string& filepath);
    bool saveImage(const std::string& filepath) const;
    int getWidth() const;
    int getHeight() const;
    const std::vector<std::vector<Pixel>>& getPixelMatrix() const;
    std::vector<std::vector<Pixel>>& getPixelMatrix();
    Pixel getPixel(int x, int y) const;
    void setPixel(int x, int y, const Pixel& pixel);
    void createFromMatrix(const std::vector<std::vector<Pixel>>& matrix);
    
private:
    std::vector<std::vector<Pixel>> pixelMatrix;
    int width;
    int height;
};

#endif