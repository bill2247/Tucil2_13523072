#ifndef _QUADTREE_HPP_
#define _QUADTREE_HPP_

#include <iostream>

class QuadTree{

private:

    // sudut paling kiri atas matriks
    int x;
    int y;
    // panjang dan lebar matriks
    int width;
    int height;

    // matriks imagepixel

    // partisi dari gambar
    QuadTree* child[4];
    

public:

    // Constructor
    QuadTree(int x, int y, int width, int height);

    // Destructor
    ~QuadTree();

    // tambah anak dari QuadTree
    void addChild(int index, QuadTree* child);

    // cek apakah sebuah daun
    bool isLeaf();
    
    // cek kedalaman pohon (include parent)
    int depth();

    // cari banyak simpul pada pohon
    int countNode();
};


#endif