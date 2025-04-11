#include <iostream>
#include <string>
#include <chrono>
#include "../header/ImagePixel.hpp"
#include "../header/ErrorCalculator.hpp"
#include "../header/QuadTreeNode.hpp"

int main(int argc, char* argv[]) {
    if (argc < 7) {
        std::cerr << "Usage: " << argv[0] << " <input_image> <error_method> <threshold> "
                  << "<min_block_size> <compression_percentage> <output_image> [output_gif]\n";
        return 1;
    }
    
    try {
        std::string inputPath;
        std::cout << "input path: ";
        std::cin >> inputPath;

        int methodNum;
        std::cout << "error method" << std::endl;
        std::cout << "1. Variance " << std::endl;
        std::cout << "2. Mean Absolute Deviation " << std::endl;
        std::cout << "3. Max Pixel Difference " << std::endl;
        std::cout << "4. Entropy " << std::endl;
        std::cout << "Enter method number (1-4): ";
        std::cin >> methodNum;

        double threshold;
        std::cout << "input treshold (0.0-1.0): ";
        std::cin >> threshold;

        int minBlockSize;
        std::cout << "input minimum block size: ";
        std::cin >> minBlockSize;

        std::string outputPath;
        std::cout << "output path: ";
        std::cin >> outputPath;
        
        // Convert method number to enum
        ErrorCalculator::ErrorMethod method;
        switch (methodNum) {
            case 1: method = ErrorCalculator::VARIANCE; break;
            case 2: method = ErrorCalculator::MEAN_ABSOLUTE_DEVIATION; break;
            case 3: method = ErrorCalculator::MAX_PIXEL_DIFFERENCE; break;
            case 4: method = ErrorCalculator::ENTROPY; break;
            default: throw std::invalid_argument("Invalid error method");
        }
        
        // Load the image
        ImagePixel image;
        if (!image.loadImage(inputPath)) {
            std::cerr << "Failed to load image: " << inputPath << std::endl;
            return 1;
        }
        
        // Start timer
        auto start = std::chrono::high_resolution_clock::now();
        
        // Compress the image
        QuadTreeCompressor compressor(image, method, threshold, minBlockSize);
        compressor.compress();
        
        // Reconstruct the compressed image
        ImagePixel compressedImage;
        compressedImage.createFromMatrix(image.getPixelMatrix()); // Initialize with same dimensions
        compressor.reconstruct(compressedImage);
        
        // Save the compressed image
        if (!compressedImage.saveImage(outputPath)) {
            std::cerr << "Failed to save compressed image: " << outputPath << std::endl;
            return 1;
        }
        
        // Stop timer
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        
        // Output results
        std::cout << "Execution time: " << duration.count() << " ms\n";
        std::cout << "Tree depth: " << compressor.getTreeDepth() << "\n";
        std::cout << "Node count: " << compressor.getNodeCount() << "\n";
        
        // TODO: Calculate and output compression percentage, original and compressed sizes
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}