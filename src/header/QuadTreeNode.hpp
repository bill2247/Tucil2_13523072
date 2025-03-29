#ifndef QUADTREE_COMPRESSOR_H
#define QUADTREE_COMPRESSOR_H

#include "ImagePixel.hpp"
#include "ErrorCalculator.hpp"
#include <memory>
#include <queue>

struct QuadTreeNode {
    int x, y;
    int width, height;
    Pixel averageColor;
    bool isLeaf;
    std::unique_ptr<QuadTreeNode> children[4];
    
    QuadTreeNode(int x, int y, int w, int h) 
        : x(x), y(y), width(w), height(h), isLeaf(false) {
        for (int i = 0; i < 4; i++) children[i] = nullptr;
    }
};

class QuadTreeCompressor {
public:
    QuadTreeCompressor(ImagePixel& image, ErrorCalculator::ErrorMethod method, double threshold, int minBlockSize);
    void compress();
    void reconstruct(ImagePixel& outputImage);
    int getTreeDepth() const;
    int getNodeCount() const;
    
private:
    ImagePixel& image;
    ErrorCalculator::ErrorMethod method;
    double threshold;
    int minBlockSize;
    std::unique_ptr<QuadTreeNode> root;
    int treeDepth;
    int nodeCount;
    
    std::unique_ptr<QuadTreeNode> buildQuadTree(int x, int y, int width, int height, int currentDepth);
    void reconstructImage(QuadTreeNode* node, std::vector<std::vector<Pixel>>& matrix);
    void getBlock(const ImagePixel& img, int x, int y, int width, int height, std::vector<std::vector<Pixel>>& block);
};

#endif