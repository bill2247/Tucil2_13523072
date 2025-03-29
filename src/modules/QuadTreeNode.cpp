#include "../header/QuadTreeNode.hpp"

QuadTreeCompressor::QuadTreeCompressor(ImagePixel& image, ErrorCalculator::ErrorMethod method, double threshold, int minBlockSize)
    : image(image), method(method), 
      threshold(threshold), minBlockSize(minBlockSize),
      treeDepth(0), nodeCount(0) {}

void QuadTreeCompressor::compress() {
    if (root) {
        root.reset();
        treeDepth = 0;
        nodeCount = 0;
    }
    
    root = buildQuadTree(0, 0, image.getWidth(), image.getHeight(), 1);
}

void QuadTreeCompressor::reconstruct(ImagePixel& outputImage) {
    if (!root) return;
    
    std::vector<std::vector<Pixel>> matrix(image.getHeight(), 
                                         std::vector<Pixel>(image.getWidth()));
    reconstructImage(root.get(), matrix);
    outputImage.createFromMatrix(matrix);
}

int QuadTreeCompressor::getTreeDepth() const { return treeDepth; }
int QuadTreeCompressor::getNodeCount() const { return nodeCount; }

std::unique_ptr<QuadTreeNode> QuadTreeCompressor::buildQuadTree(int x, int y, int width, int height, int currentDepth) {
    auto node = std::make_unique<QuadTreeNode>(x, y, width, height);
    nodeCount++;
    treeDepth = std::max(treeDepth, currentDepth);
    
    // Get the current block
    std::vector<std::vector<Pixel>> block;
    getBlock(image, x, y, width, height, block);
    
    // Calculate error and mean values
    double rMean, gMean, bMean;
    double error = ErrorCalculator::calculateError(method, block, rMean, gMean, bMean);
    
    // Check if we should split
    bool shouldSplit = (error > threshold) && 
                      (width > minBlockSize && height > minBlockSize) &&
                      (width/2 >= minBlockSize && height/2 >= minBlockSize);
    
    if (shouldSplit) {
        // Split into 4 quadrants
        int halfWidth = width / 2;
        int halfHeight = height / 2;
        
        // Top-left
        node->children[0] = buildQuadTree(x, y, halfWidth, halfHeight, currentDepth + 1);
        // Top-right
        node->children[1] = buildQuadTree(x + halfWidth, y, width - halfWidth, halfHeight, currentDepth + 1);
        // Bottom-left
        node->children[2] = buildQuadTree(x, y + halfHeight, halfWidth, height - halfHeight, currentDepth + 1);
        // Bottom-right
        node->children[3] = buildQuadTree(x + halfWidth, y + halfHeight, 
                                         width - halfWidth, height - halfHeight, currentDepth + 1);
    } else {
        // Leaf node - store average color
        node->isLeaf = true;
        node->averageColor = Pixel(static_cast<uint8_t>(rMean),
                                 static_cast<uint8_t>(gMean),
                                 static_cast<uint8_t>(bMean));
    }
    
    return node;
}

void QuadTreeCompressor::reconstructImage(QuadTreeNode* node, std::vector<std::vector<Pixel>>& matrix) {
    if (!node) return;
    
    if (node->isLeaf) {
        // Fill the block with average color
        for (int y = node->y; y < node->y + node->height; y++) {
            for (int x = node->x; x < node->x + node->width; x++) {
                if (static_cast<size_t>(y) < matrix.size() && static_cast<size_t>(x) < matrix[y].size()){
                    matrix[y][x] = node->averageColor;
                }
            }
        }
    } else {
        // Reconstruct children
        for (int i = 0; i < 4; i++) {
            reconstructImage(node->children[i].get(), matrix);
        }
    }
}

void QuadTreeCompressor::getBlock(const ImagePixel& img, int x, int y, int width, int height,
             std::vector<std::vector<Pixel>>& block) {
    block.clear();
    block.reserve(height);
    
    for (int row = y; row < y + height; row++) {
        if (row >= img.getHeight()) break;
        
        std::vector<Pixel> rowPixels;
        rowPixels.reserve(width);
        
        for (int col = x; col < x + width; col++) {
            if (col >= img.getWidth()) break;
            rowPixels.push_back(img.getPixel(col, row));
        }
        
        block.push_back(rowPixels);
    }
}
