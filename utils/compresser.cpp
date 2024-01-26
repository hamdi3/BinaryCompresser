#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <bitset>
#include <cstring>
#include <zlib.h>
#include "compresser.h"
using namespace std;

// Compression function
string compress_string(const string &input)
{
    z_stream zs;
    memset(&zs, 0, sizeof(zs));

    if (deflateInit(&zs, Z_BEST_COMPRESSION) != Z_OK)
    {
        throw runtime_error("Failed to compress the file.");
    }

    zs.next_in = reinterpret_cast<Bytef *>(const_cast<char *>(input.data()));
    zs.avail_in = static_cast<uInt>(input.size());

    int ret;
    char outbuffer[32768];
    string compressed_string;

    do
    {
        zs.next_out = reinterpret_cast<Bytef *>(outbuffer);
        zs.avail_out = sizeof(outbuffer);

        ret = deflate(&zs, Z_FINISH);

        if (compressed_string.size() < zs.total_out)
        {
            compressed_string.append(outbuffer, zs.total_out - compressed_string.size());
        }
    } while (ret == Z_OK);

    deflateEnd(&zs);

    cout << "Binary Compressed Successfully" << endl;

    return compressed_string;
}

// Save compressed String
void save_binary_string_to_file(const string binary_string, const char *file_path)
{
    cout << "Saving Binary" << endl;
    try
    {
        ofstream file(file_path, ios::out | ios::binary);
        if (!file)
        {
            throw runtime_error("Failed to open file for writing.");
        }
        const string str_binary_string(binary_string);
        file.write(str_binary_string.data(), str_binary_string.size());
        if (!file)
        {
            throw runtime_error("Failed to write binary data to file.");
        }
        file.close();
        cout << "Saved Binary successfully at: " << file_path << endl;
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << endl;
    }
}

// Vernam cipher
string xor_encrypt_decrypt(const string &input, const string &key)
{
    string output = input;
    for (size_t i = 0; i < input.size(); ++i)
    {
        output[i] = input[i] ^ key[i % key.size()];
    }
    return output;
}

// File to Binary function
void file_to_binary_string(const char *input_file_path, const char *output_binary_path, const char *key)
{
    ifstream f(input_file_path, ios::binary | ios::ate);
    if (!f)
    {
        cout << "File Path in c++: " << input_file_path << endl;
        cout << "Error code: " << strerror(errno) << endl;
    }

    size_t size = f.tellg();
    char *buffer = new char[size];
    f.seekg(0, ios::beg);
    f.read(buffer, size);
    f.close();

    string binary_string;
    for (size_t i = 0; i < size; ++i)
    {
        binary_string += bitset<8>(buffer[i]).to_string();
    }
    delete[] buffer;

    cout << "File Converted to Binary Successfully" << endl;

    string compressed_binary_string = compress_string(binary_string);

    string encrypted_binary_string = compressed_binary_string;
    if (key != nullptr)
    {
        string key_str(key);
        encrypted_binary_string = xor_encrypt_decrypt(compressed_binary_string, key_str);
    }

    cout << "File Encrypted Successfully" << endl;

    save_binary_string_to_file(encrypted_binary_string, output_binary_path);
}

// Load Binray string from file
string load_binary_string_from_file(const char *file_path)
{
    cout << "Loading Binary" << endl;
    try
    {
        ifstream file(file_path, ios::binary | ios::ate);
        if (!file)
        {
            throw runtime_error("Failed to open file for reading.");
        }
        streamsize size = file.tellg();
        file.seekg(0, ios::beg);
        vector<char> buffer(size);
        if (!file.read(buffer.data(), size))
        {
            throw runtime_error("Failed to read binary data from file.");
        }
        file.close();
        cout << "Loaded Binary Successfully" << endl;

        string str = string(buffer.begin(), buffer.end());
        return str;
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << endl;
        return "";
    }
}

// Decompression function
string decompress_string(const string &input)
{
    z_stream zs;
    memset(&zs, 0, sizeof(zs));

    if (inflateInit(&zs) != Z_OK)
    {
        return "";
    }

    zs.next_in = reinterpret_cast<Bytef *>(const_cast<char *>(input.data()));
    zs.avail_in = static_cast<uInt>(input.size());

    int ret;
    char outbuffer[32768];
    string decompressed_string;

    do
    {
        zs.next_out = reinterpret_cast<Bytef *>(outbuffer);
        zs.avail_out = sizeof(outbuffer);

        ret = inflate(&zs, 0);

        if (decompressed_string.size() < zs.total_out)
        {
            decompressed_string.append(outbuffer, zs.total_out - decompressed_string.size());
        }
    } while (ret == Z_OK);

    inflateEnd(&zs);

    cout << "Binary decompressed successfully" << endl;

    return decompressed_string;
}

// Binary to file function
void binary_string_to_file(const char *input_binary_path, const char *output_file_path, const char *key)
{
    ofstream file(output_file_path, ios::binary);
    if (!file)
    {
        cout << "Failed to create the file" << endl;
        return;
    }

    // Decompress string
    string binary_string = load_binary_string_from_file(input_binary_path);
    string decrypted_binary_string = binary_string;
    if (key != nullptr)
    {
        string key_str(key);
        decrypted_binary_string = xor_encrypt_decrypt(binary_string, key_str);
    }
    cout << "Binary Decrypted successfully" << endl;
    
    string binary_string_decompressed = decompress_string(decrypted_binary_string);

    // Convert the binary string back to bytes and write them to the file
    for (size_t i = 0; i < binary_string_decompressed.length(); i += 8)
    {
        string byteStr = binary_string_decompressed.substr(i, 8);
        char byte = static_cast<char>(bitset<8>(byteStr).to_ulong());
        file.write(&byte, sizeof(byte));
    }

    file.close();

    cout << "File generated successfully: " << output_file_path << endl;
}