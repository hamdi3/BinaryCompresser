extern "C" {
    void file_to_binary_string(const char *input_file_path, const char *output_binary_path, const char *key = nullptr);
    void binary_string_to_file(const char *input_binary_path, const char *output_file_path, const char *key = nullptr);
}