// WordCount.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//输入输出说明
//输入：[parameter][input_file_name]
//注：[parameter]为控制参数，取” - c”和” - w”之一；[input_file_name]为要被处理的文本文件名，默认存放在执行文件目录下。
//输出：根据[parameter]为以下形式之一
//单词数：n
//其中n为统计的字符数或单词数
//例如：
//wordCount.exe - c input.txt //统计input.txt中的字符数
//wordCount.exe - w input.txt //统计input.txt中的单词数

#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_FILENAME_LENGTH 100

// 函数用于统计字符数
int countCharacters(FILE* file) {
    int count = 0;
    int c;
    while ((c = fgetc(file)) != EOF) {
        count++;
    }
    return count;
}

// 函数用于统计单词数
int countWords(FILE* file) {
    int count = 0;
    int c;
    int in_word = 0; // 标记是否在单词中
    while ((c = fgetc(file)) != EOF) {
        if (isspace(c) || c == ',' || c == '\n' || c == '\t') {
            in_word = 0;
        }
        else if (!in_word) {
            in_word = 1;
            count++;
        }
    }
    return count;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s [-c | -w] [input_file_name]\n", argv[0]);
        return 1;
    }

    char* parameter = argv[1];
    char* filename = argv[2];

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error");
        return 1;
    }

    int count = 0;

    if (parameter[0] == '-' && (parameter[1] == 'c' || parameter[1] == 'w') && parameter[2] == '\0') {
        if (parameter[1] == 'c') {
            count = countCharacters(file);
            printf("字符数：%d\n", count);
        }
        else if (parameter[1] == 'w') {
            count = countWords(file);
            printf("单词数：%d\n", count);
        }
    }
    else {
        printf("Invalid parameter. Please use -c or -w.\n");
        return 1;
    }

    fclose(file);
    return 0;
}