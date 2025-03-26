#include "../header/QuadTree.hpp"

QuadTree::QuadTree(int x, int y, int width, int height){
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    for (int i=0; i< 4; i++){
        this->child[i] = nullptr;
    }
}

QuadTree::~QuadTree(){}

void QuadTree::addChild(int index, QuadTree* newchild){
    this->child[index] = newchild;
}

bool QuadTree::isLeaf(){
    for (int i=0; i<4; i++)
    if (this->child[i] != nullptr){
        return false;
    }
    return true;
}

int QuadTree::depth(){
    if (this->isLeaf()){
        return 1;
    }
    int max = 0;
    for (int i=0; i<4;i++){
        if (this->child[i] != nullptr){
            int temp = this->child[i]->depth();
            if (temp > max){
                max = temp;
            }
        }
    }
    return max + 1;
}

int QuadTree::countNode(){
    if (this->isLeaf()){
        return 1;
    }
    int count = 0;
    for (int i=0; i<4; i++){
        if (this->child[i] != nullptr){
            count += this->child[i]->countNode();
        }
    }
    return count + 1;
}