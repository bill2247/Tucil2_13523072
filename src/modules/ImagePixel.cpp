#include "../header/ImagePixel.hpp"

ImagePixel::ImagePixel() : width(0), height(0) {}
ImagePixel::~ImagePixel() = default;

bool ImagePixel::loadImage(const std::string& filepath) {
    int channels;
    unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &channels, 3);
    if (!data) {
        return false;
    }

    pixelMatrix.resize(height, std::vector<Pixel>(width));

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int index = (y * width + x) * 3;
            pixelMatrix[y][x] = Pixel(data[index], data[index+1], data[index+2]);
        }
    }

    stbi_image_free(data);
    return true;
}

bool ImagePixel::saveImage(const std::string& filepath) const {
    std::vector<unsigned char> data(width * height * 3);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int index = (y * width + x) * 3;
            data[index] = pixelMatrix[y][x].r;
            data[index+1] = pixelMatrix[y][x].g;
            data[index+2] = pixelMatrix[y][x].b;
        }
    }

    std::string ext = filepath.substr(filepath.find_last_of(".") + 1);
    if (ext == "png") {
        return stbi_write_png(filepath.c_str(), width, height, 3, data.data(), width * 3);
    } else if (ext == "jpg" || ext == "jpeg") {
        return stbi_write_jpg(filepath.c_str(), width, height, 3, data.data(), 90);
    }

    return false;
}

int ImagePixel::getWidth() const { return width; }
int ImagePixel::getHeight() const { return height; }

const std::vector<std::vector<Pixel>>& ImagePixel::getPixelMatrix() const { return pixelMatrix; }
std::vector<std::vector<Pixel>>& ImagePixel::getPixelMatrix() { return pixelMatrix; }

Pixel ImagePixel::getPixel(int x, int y) const {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw std::out_of_range("Pixel coordinates out of range");
    }
    return pixelMatrix[y][x];
}

void ImagePixel::setPixel(int x, int y, const Pixel& pixel) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw std::out_of_range("Pixel coordinates out of range");
    }
    pixelMatrix[y][x] = pixel;
}

void ImagePixel::createFromMatrix(const std::vector<std::vector<Pixel>>& matrix) {
    if (matrix.empty() || matrix[0].empty()) {
        width = height = 0;
        pixelMatrix.clear();
        return;
    }

    height = matrix.size();
    width = matrix[0].size();
    pixelMatrix = matrix;
}