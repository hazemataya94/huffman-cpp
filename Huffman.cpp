//
//  Huffman.cpp
//  Huffman Compression
//
//  Created by Hazem Ataya on 3/14/19.
//  Email hazem.ataya94@gmail.com
//

#include "Huffman.h"
#include <bitset>
#include <iostream>
#include <fstream>

void Huffman::writeUnsignedChar(string &str, unsigned char* chars, int size) {
    for (int i = 0; i < size; i++) {
        str.push_back(chars[i]);
    }
}

unsigned char* Huffman::readUnsignedChar(string str, int index, int size) {
    
    vector<unsigned char> output;
    string subStr = str.substr(index, size);
    
    for (int i = 0; i < size; i++) {
        output.push_back((unsigned char)subStr[i]);
    }
    
    return output.data();
}

//Compress
void Huffman::createFrequencyTable() {
    
    unordered_map<unsigned char, int> frequencyMap;
    
    for (int i = 0; i < (int)this->text.size(); i++) {
        frequencyMap[this->text[i]]++;
    }
    
    for (unordered_map<unsigned char, int>::iterator i = frequencyMap.begin(); i != frequencyMap.end(); i++) {
        this->frequencyTable.push_back(make_pair(i->first, i->second));
    }
}

void Huffman::buildHuffmanTree() {
    
    priority_queue<Tree*, vector<Tree *>, TreeComparator> huffQueue;
    
    for (int i = 0; i < this->frequencyTable.size(); i++) {
        
        Tree *node = new Tree();
        node->frequency = this->frequencyTable[i].second;
        node->character = this->frequencyTable[i].first;
        
        huffQueue.push(node);
    }
    
    while (huffQueue.size() > 1) {
        
        Tree *a, *b;
        a = huffQueue.top();
        huffQueue.pop();
        
        b = huffQueue.top();
        huffQueue.pop();
        Tree *c = new Tree();
        c->frequency = a->frequency + b->frequency;
        c->left = a;
        c->right = b;
        huffQueue.push(c);
    }
    
    this->root = huffQueue.top();
}

void Huffman::traverseHuffmanTree(Tree* newRoot, string prev, string toAppend) {
    
    prev += toAppend;
    
    if (newRoot->right == NULL && newRoot->left == NULL) {
        this->codeMap[newRoot->character] = prev;
    }
    if (newRoot->right != NULL) {
        traverseHuffmanTree(newRoot->right , prev, "1");
    }
    if (newRoot->left != NULL) {
        traverseHuffmanTree(newRoot->left, prev, "0");
    }
}

string Huffman::getHuffmanBitString() {
    
    string outputString = "";
    string compressedText = "";
    vector<unsigned char> outputBuffer;
    int paddedBits;
    
    //ones and zeros
    for (int i = 0; i < (int)this->text.size(); i++) {
        outputString = outputString + this->codeMap[this->text[i]];
    }
    
    int outputStringSize = (int)outputString.size();
    
    if (outputStringSize % 8 != 0) {
        int deficit = 8 * ((outputStringSize / 8) + 1) - outputStringSize;
        paddedBits = deficit;
        for (int i = 0; i < deficit; i++) {
            outputString += "0";
            outputStringSize++;
        }
    }
    
    //string
    int interval = 0;
    unsigned char bit = 0;
    
    for (int i = 0; i < outputStringSize; i++) {
        
        bit = (bit << 1) | (outputString[i] - '0');
        
        interval++;
        if(interval == 8) {
            interval = 0;
            outputBuffer.push_back(bit);
            bit = 0;
        }
    }
    
    int size = (int)this->codeMap.size();
    writeUnsignedChar(compressedText, (unsigned char*)& paddedBits, sizeof(int));
    writeUnsignedChar(compressedText, (unsigned char*)& size, sizeof(int));
    
    for (unordered_map<unsigned char, string>::iterator i = this->codeMap.begin(); i != this->codeMap.end(); i++) {
        
        writeUnsignedChar(compressedText, (unsigned char*)& i->first, 1);
        
        int len = (int)i->second.size();
        writeUnsignedChar(compressedText, (unsigned char*)& len, sizeof(int));
        writeUnsignedChar(compressedText, (unsigned char*)i->second.c_str(), (int)i->second.size());
    }
    
    writeUnsignedChar(compressedText, outputBuffer.data(), (int)outputBuffer.size());
    
    return compressedText;
}


//Decompress
void Huffman::readHeader() {
    
    int index = 0;
    
    unsigned char* paddedBitsUC = readUnsignedChar(this->text, index, sizeof(int));
    index += sizeof(int);
    this->paddedBits = *((int*)paddedBitsUC);
    
    unsigned char* sizeUC = readUnsignedChar(this->text, index, sizeof(int));
    index += sizeof(int);
    int size = *((int*)sizeUC);
    
    for (int i = 0; i < size; i++) {
        
        unsigned char* keyUC = readUnsignedChar(this->text, index, 1);
        index += 1;
        unsigned char key = *keyUC;
        
        unsigned char* lenUC = readUnsignedChar(this->text, index, sizeof(int));
        index += sizeof(int);
        int len = *((int*)lenUC);
        
        unsigned char* valueUC = readUnsignedChar(this->text, index, len);
        index += len;
        string value;
        for (int j = 0; j < len; j++) {
            value.push_back(valueUC[j]);
        }
        
        this->codeMap[key] = value;
    }
    
    this->text = this->text.substr(index);
    
}

string Huffman::getStringFromBuffer() {
    
    string compressedText = "";
    string decompressedText = "";
    
    for (int i = 0; i < (int)this->text.size(); i++) {
        compressedText += std::bitset<8>(this->text[i]).to_string();
    }
    
    string bit = "";
    unordered_map<string, unsigned char> reverseCodes;
    
    for(unordered_map<unsigned char, string>::iterator i = this->codeMap.begin(); i != this->codeMap.end(); i++) {
        reverseCodes[i->second] = i->first;
    }
    
    for (int i = 0; i < compressedText.size() - paddedBits; i++) {
        
        bit += string(1, compressedText[i]);
        
        if (reverseCodes.find(bit) != reverseCodes.end()) {
            decompressedText += reverseCodes[bit];
            bit = "";
        }
    }
    
    return decompressedText;
}


//FileHelpers
string Huffman::readTextFromFile(string filePath) {
    
    ifstream ifs(filePath);
    
    if (!ifs.is_open()) {
        throw runtime_error("File not found");
    }
    
    std::string fileText((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
    
    return fileText;
}

void Huffman::writeTextToFile(string filePath, string text) {
    
    ofstream ofs(filePath);
    
    if (!ofs.is_open()) {
        throw runtime_error("File not found");
    }
    
    ofs << text;
    ofs.close();
    
    return;
}

string Huffman::readBinaryFile(string filePath) {
    
    ifstream ifs(filePath, std::ios::binary);
    
    if (!ifs.is_open()) {
        throw runtime_error("File not found");
    }
    
    std::string fileText((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
    
    return fileText;
}

void Huffman::writeBinaryFile(string filePath, string content) {
    
    ofstream ofs(filePath, std::ios::binary);
    
    if (!ofs.is_open()) {
        throw runtime_error("File not found");
    }
    
    ofs << content;
    ofs.close();
    
    return;
}


//public
string Huffman::compress(string text) {
    
    this->text = text;
    
    createFrequencyTable();
    buildHuffmanTree();
    traverseHuffmanTree(this->root, "", "");
    
    return getHuffmanBitString();
}

string Huffman::decompress(string text) {
    
    this->text = text;
    
    Huffman::readHeader();
    
    return Huffman::getStringFromBuffer();
}

bool Huffman::compressTextFile(string inputPath, string outputPath) {
    
    try {
        
        string text = this->readTextFromFile(inputPath);
        string compressedText = this->compress(text);
        this->writeTextToFile(outputPath, compressedText);
        
    } catch (const runtime_error& error) {
        
        return false;
    }
    
    return true;
}

bool Huffman::decompressTextFile(string inputPath, string outputPath) {
    
    try {
        
        string text = this->readTextFromFile(inputPath);
        string decompressedText = this->decompress(text);
        this->writeTextToFile(outputPath, decompressedText);
        
    } catch (const runtime_error& error) {
        
        return false;
    }
    
    return true;
}

bool Huffman::compressBinaryFile(string inputPath, string outputPath) {
    
    try {
        
        string text = this->readBinaryFile(inputPath);
        string compressedText = this->compress(text);
        this->writeBinaryFile(outputPath, compressedText);
        
    } catch (const runtime_error& error) {
        
        return false;
    }
    
    return true;
}

bool Huffman::decompressBinaryFile(string inputPath, string outputPath) {
    
    try {
        
        string text = this->readBinaryFile(inputPath);
        string decompressedText = this->decompress(text);
        this->writeBinaryFile(outputPath, decompressedText);
        
    } catch (const runtime_error& error) {
        
        return false;
    }
    
    return true;
}
