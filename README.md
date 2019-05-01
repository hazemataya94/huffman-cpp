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

### And coding style tests

Explain what these tests test and why

```
Give an example
```

## Deployment

Add additional notes about how to deploy this on a live system

## Built With

* [Dropwizard](http://www.dropwizard.io/1.0.2/docs/) - The web framework used
* [Maven](https://maven.apache.org/) - Dependency Management
* [ROME](https://rometools.github.io/rome/) - Used to generate RSS Feeds

## Authors

* [**Hazem Ataya**](https://github.com/hazemataya94)

