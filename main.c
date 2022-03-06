#include <stdio.h>
#include "./9cc.h"

int main(int argc, char **argv){
  if (argc != 2) {
    error("引数の個数が正しくありません\n");
    return 1;
  }

  user_input = argv[1];
  token = tokenize(argv[1]);

  Token *token_tmp = token;
  while(token_tmp->kind != TK_EOF) {
      printf("// t_kind %d, val %d, len %d\n", token_tmp->kind, token_tmp->val, token_tmp->len);
      token_tmp = token_tmp->next;
  }
  Node **node = program();

  printf(".intel_syntax noprefix\n");
  printf(".global main\n");
  printf("main:\n");

  // プロローグ
  // 変数26個分の領域を確保する
  printf("  push rbp\n");
  printf("  mov rbp, rsp\n");
  printf("  sub rsp, 208\n");

  int i = 0;
  while(node[i]) {
      gen(node[i++]);
      printf("  pop rax\n");
  }

  printf("  mov rsp, rbp\n");
  printf("  pop rbp\n");
  printf("  ret\n");

  return 0;
}
