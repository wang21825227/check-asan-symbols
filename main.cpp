#include <iostream>
#include <fstream>
#include <stdio.h>>

using namespace std;

// 實現KMP算法的函數
bool
HAS_ASAN_SYMBOL(string text, string pattern)
{
  int m = text.length();
  int n = pattern.length();
  if (n == 0 || m == 0) {
    return false;
  }
  if (m < n) {
    return false;
  }

  // next[i] 存儲下一個最佳部分匹配的索引
  int next[n + 1];
  for (int i = 0; i < n + 1; i++) {
    next[i] = 0;
  }

  for (int i = 1; i < n; i++) {
    int j = next[i + 1];
    while (j > 0 && pattern[j] != pattern[i]) {
      j = next[j];
    }
    if (j > 0 || pattern[j] == pattern[i]) {
      next[i + 1] = j + 1;
    }
  }

  for (int i = 0, j = 0; i < m; i++) {
    if (text[i] == pattern[j]) {
      if (++j == n) {
        //cout << "The pattern occurs with shift " << i - j + 1 << endl;
        return true;
      }
    } else if (j > 0) {
      j = next[j];
      i--; // 因為 `i` 將在下一次迭代中遞增
    }
  }
  return false;
}

int main(int argc, char* argv[])
{
  string content;
  if (argc != 3) {
    cout << "cmd parameter numbers error" << endl;
    return 0;
  }
  const char *file_path = argv[1];
  const char *pattern = argv[2];
  FILE * file = fopen(file_path, "rb+");
  if (file == NULL) {
    cout << "open file error" << endl;
    return 0;
  }
  char line[1024];
  memset(line, 0, 1024);
  while(!feof(file)) {
    fgets(line, 1024, file);
    content += line;
  }
  cout << HAS_ASAN_SYMBOL(content, pattern);
  return 0;
}
