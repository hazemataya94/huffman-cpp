# Huffman Compression

This code was created to implement Huffman compression alogrithm on text, text files, and binary files.

## Getting Started

Download the files, include Huffman.h header in your program.

## Running The Tests

Use the main.cpp file to do tests, you just have to change "testFolderPath" to be the full path of the provided Test folder on your local device.

### How To Use

After the header is included, an object of Huffman class should be created:

```
Huffman huffman;
```

#### Text Compression:
```
string compressedText = huffman.compress(originalText);
string decompressedText = huffman.decompress(compressedText);
```

#### Text File Compression:
```
huffman.compressTextFile(originalTextFile, compressedTextFile);
huffman.decompressTextFile(compressedTextFile, decompressedTextFile);    
```

#### Binary File Compression:
```
huffman.compressBinaryFile(originalBinaryFile, compressedBinaryFile);
huffman.decompressBinaryFile(compressedBinaryFile, decompressedBinaryFile);
```

## Authors

* [**Hazem Ataya**](https://github.com/hazemataya94)

