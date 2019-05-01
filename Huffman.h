//
//  Huffman.h
//  Huffman Compression
//
//  Created by Hazem Ataya on 3/14/19.
//  Email hazem.ataya94@gmail.com
//

#ifndef Huffman_h
#define Huffman_h

#include <string>
#include <unordered_map>
#include <queue>

using namespace std;

struct Tree {
    int frequency;
    unsigned char character;
    Tree *left = NULL;
    Tree *right = NULL;
};

class TreeComparator {
public:
    bool operator()(Tree *a, Tree *b) {
        return a->frequency > b->frequency;
    }
};

class Huffman {
    
    string text;
    int paddedBits;
    Tree* root;
    unordered_map<unsigned char, string> codeMap;
    vector<pair<unsigned char, int>> frequencyTable;
    
    //Helpers
    void writeUnsignedChar(string &str, unsigned char* chars, int size);
    unsigned char* readUnsignedChar(string str, int index, int size);
    
    //Compress
    void createFrequencyTable();
    void buildHuffmanTree();
    void traverseHuffmanTree(Tree *newRoot, string prev, string toAppend);
    string getHuffmanBitString();
    
    //Decompress
    void readHeader();
    string getStringFromBuffer();
    
    //FileHelpers
    string readTextFromFile(string filePath);
    void writeTextToFile(string filePath, string text);
    string readBinaryFile(string filePath);
    void writeBinaryFile(string filePath, string content);
    
public:
    
    string compress(string text);
    string decompress(string text);
    bool compressTextFile(string inputPath, string outputPath);
    bool decompressTextFile(string inputPath, string outputPath);
    bool compressBinaryFile(string inputPath, string outputPath);
    bool decompressBinaryFile(string inputPath, string outputPath);
};

#endif /* Huffman_h */
