//
//  main.cpp
//  Huffman Compression
//
//  Created by Hazem Ataya on 3/14/19.
//  Email hazem.ataya94@gmail.com
//

#include "Huffman.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

inline string readTextFromFile(string filePath) {
    
    ifstream ifs(filePath);
    
    if (!ifs.is_open()) {
        throw runtime_error("File not found");
    }
    
    std::string fileText((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
    
    return fileText;
}

inline string readBinaryFile(string filePath) {
    
    ifstream ifs(filePath, std::ios::binary);
    
    if (!ifs.is_open()) {
        throw runtime_error("File not found");
    }
    
    std::string fileText((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
    
    return fileText;
}

inline int getFileSize(string filePath) {

    FILE *p_file = NULL;
    p_file = fopen(filePath.c_str(),"rb");
    
    fseek(p_file,0,SEEK_END);
    int size = (int)ftell(p_file);
    fclose(p_file);
    
    return size;
}


int main(int argc, char* argv[]) {
    
    string testFolderPath = "PathToFolder/Test";
    
    string originalTextFile = testFolderPath + "/sampleTextFile.txt";
    string compressedTextFile = testFolderPath + "/compressed.txt";
    string decompressedTextFile = testFolderPath + "/decompressed.txt";
    
    string originalBinaryFile = testFolderPath + "/samplePDFFile.pdf";
    string compressedBinaryFile = testFolderPath + "/compressedPdf.pdf";
    string decompressedBinaryFile = testFolderPath + "/decompressedPdf.pdf";
    
    Huffman huffman;
    
    //Text Compression
    string originalText = readTextFromFile(originalTextFile);
    string compressedText = huffman.compress(originalText);
    string decompressedText = huffman.decompress(compressedText);
    
    assert(originalText == decompressedText);
    
    cout << "Original Text Size: " << (int)originalText.length() << "[B]" << endl;
    cout << "Compressed Text Size: " << (int)compressedText.length() << "[B]" << endl;
    
    //Text File Compression
    huffman.compressTextFile(originalTextFile, compressedTextFile);
    huffman.decompressTextFile(compressedTextFile, decompressedTextFile);
    
    assert(readTextFromFile(originalTextFile) == readTextFromFile(decompressedTextFile));
    
    cout << "Original Text File Size: " << getFileSize(originalTextFile) << "[B]" << endl;
    cout << "Compressed Text File Size: " << getFileSize(compressedTextFile) << "[B]" << endl;
    
    //Binary File Compression
    huffman.compressBinaryFile(originalBinaryFile, compressedBinaryFile);
    huffman.decompressBinaryFile(compressedBinaryFile, decompressedBinaryFile);
    
    assert(readBinaryFile(originalBinaryFile) == readBinaryFile(decompressedBinaryFile));
    
    cout << "Original PDF File Size: " << getFileSize(originalBinaryFile) << "[B]" << endl;
    cout << "Compressed PDF File Size: " << getFileSize(compressedBinaryFile) << "[B]" << endl;
    
    return 0;
}
