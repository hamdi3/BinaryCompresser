# BinaryCompresser
![Language: C++](https://img.shields.io/badge/language-C%2B%2B-blue.svg)
![zlib](https://img.shields.io/badge/zlib-1.2.11-brightgreen.svg)
![Build: Make](https://img.shields.io/badge/build-Make-brightgreen.svg)
![License: Unlicense](https://img.shields.io/badge/license-Unlicense-blue.svg)
![Built with Love](https://img.shields.io/badge/built%20with-%E2%9D%A4-red.svg)

## Overview

BinaryCompresser is a C++ project that provides file compression and decompression functionality. It uses the zlib library for compression and decompression, and offers optional encryption based on the Vernam cipher.

## Features

- **File Compression**: The `file_to_binary_string` function compresses files into a binary format using zlib. It takes a path to the input file and a path to the output compressed binary file as input. It also takes an optional encryption key.

- **File Decompression**: The `binary_string_to_file` function decompresses files from a binary format using zlib. It takes the binary path and the output path as input, as well as an optional decryption key.

- **Optional Encryption**: The optional encryption is based on the Vernam cipher. If a key is provided, the `file_to_binary_string` function will encrypt the file before compression, and the `binary_string_to_file` function will decrypt the file after decompression.

## Usage

You can use BinaryCompresser from the terminal as follows:

To compress a file into a binary:
```bash
./BinaryCompresser --file-to-binary <input_file_path> <output_binary_path> [key]
```

To retrive a file from a binary:
```bash
./BinaryCompresser --binary-to-file <input_binary_path> <output_file_path> [key]
```

## Performance
I’ve done some performance testing on files up to 200 MBs. Here are the results:

Compression Time Plot: 
![time](https://github.com/hamdi3/BinaryCompresser/assets/38282254/6b218cba-1b9e-4fde-9da5-a252b7ea9feb)

Compressed File Size Plot:
![bin_size](https://github.com/hamdi3/BinaryCompresser/assets/38282254/f361dfa6-33f0-4f7a-8f5e-ae681f70a92a)

These plots show the time taken to compress files and the size of the compressed files. As you can see, BinaryCompresser is capable of efficiently compressing large files.

## Building
This project uses CMake for building. You can build the project as follows:
```bash
mkdir build
cd build
cmake ..
make
```
This will create a `build` directory, change into that directory, generate the Makefile with CMake, and then build the project with Make.

## Contributing

Contributions are welcome and greatly appreciated! To contribute to this project, follow these steps:

1. Fork the repository.

2. Create a new branch:

   ```bash
   git checkout -b feature/my-feature
   ```

3. Make the desired changes and commit them:
   
   ```bash
   git commit -m "Add my feature"
   ```

4. Push to the branch:
      
   ```bash
   git push origin feature/my-feature
   ```

5. Open a pull request in the main repository.


## Contact

If you have any questions, suggestions, or feedback, please feel free to contact me:

- GitHub: [github.com/hamdi3](https://github.com/hamdi3)

I'm open to collaboration and look forward to hearing from you!
