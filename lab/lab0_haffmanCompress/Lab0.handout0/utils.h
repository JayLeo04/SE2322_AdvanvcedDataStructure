#ifndef UTILS_H
#define UTILS_H
#include <bitset>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
const int BITSET_SIZE = 8;
namespace utils
{
    std::string getFileName(const std::string &fileName, const std::string &suffix)
    {
        size_t final_pos = fileName.find_last_of("/\\");
        size_t suffix_pos = fileName.find_last_of('.');
        return final_pos == std::string::npos ? "./output/" + fileName.substr(0, suffix_pos) + suffix : "./output/" + fileName.substr(final_pos + 1, suffix_pos - final_pos - 1) + suffix;
    }

    std::string parseText(const std::string &input) {
        std::ifstream file(input);
        std::stringstream buffer;

        // 检查文件是否成功打开
        if (file) {
            // 读取文件内容到字符串流中
            buffer << file.rdbuf();
        } else {
            // 如果文件打开失败，应该处理错误
            throw std::runtime_error("Could not open the file.");
        }

        // 将字符串流内容转换为字符串并返回
        return buffer.str();
    }

// 这个函数将字符串数据写入到指定的文件中
    void output(const std::string &output, const std::string &data) {
        // 创建一个ofstream对象用于写入文件
        std::ofstream outFile(output, std::ios::binary); // 使用二进制模式以防数据包含非文本字符

        if (!outFile) {
            // 如果文件创建失败，应该处理错误，例如抛出异常
            throw std::runtime_error("Could not create the file.");
        }

        // 写入数据
        outFile.write(data.c_str(), data.size());

        // 关闭文件
        outFile.close();
    }

    std::string codingTable2String(const std::map<std::string, std::string> &codingTable) {
        std::ostringstream oss;

        for (const auto &entry : codingTable) {
            // 保持之前的格式："字符:编码;"
            oss << entry.first << ':' << entry.second << ';';
        }

        return oss.str();
    }

    void loadCodingTable(const std::string &input, std::map<std::string, std::string> &codingTable) {
        std::ifstream inFile(input);
        std::string line;
        while (std::getline(inFile, line)) {
            // 假设输入文件中的每行都是字符和编码的配对，它们之间用空格或其他分隔符分开
            std::istringstream iss(line);
            std::string key, value;
            if (!(iss >> key >> value)) { break; } // 处理错误或文件结束
            codingTable[key] = value;
        }
    }

    std::string compress(const std::map<std::string, std::string> &codingTable, const std::string& text) {
        std::string bit_string; // 存储比特流
        // 把字符转换为比特串
        for (char c : text) {
            std::string charStr(1, c);
            auto it = codingTable.find(charStr);
            if (it != codingTable.end()) {
                bit_string += it->second;
            } else {
                // 在映射中找不到字符 c 的编码，可能抛出一个异常或处理错误
                throw std::runtime_error("Character encoding not found for 1" + charStr);
            }
        }

        // 计算补足0的数量
        size_t padding = (BITSET_SIZE - (bit_string.length() % BITSET_SIZE)) % BITSET_SIZE;
        bit_string.append(padding, '0');

        // 将压缩后的比特流大小（有效比特数）添加到结果中
        size_t effective_bits = bit_string.length() - padding;
        std::string result;
        // 小端模式存储有效比特数
        for (int i = 0; i < sizeof(size_t); ++i) {
            result.push_back(static_cast<char>((effective_bits >> (i * BITSET_SIZE)) & 0xFF));
        }

        // 将比特串转换为字节流
        for (size_t i = 0; i < bit_string.length(); i += BITSET_SIZE) {
            std::bitset<BITSET_SIZE> b(bit_string.substr(i, BITSET_SIZE));
            result.push_back(static_cast<unsigned char>(b.to_ulong()));
        }

        return result;
    }
};

#endif