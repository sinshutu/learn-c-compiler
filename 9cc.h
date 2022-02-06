// 抽象構文木のノードの種類
typedef enum {
  ND_ADD, // +
  ND_SUB, // -
  ND_MUL, // *
  ND_DIV, // /
  ND_EQ,  // ==
  ND_NE,  // !=
  ND_LT,  // <
  ND_LE,  // <=
  ND_NUM, // 整数
} NodeKind;

typedef struct Node Node;
struct Node {
  NodeKind kind;    // ノードの型
  Node *lhs;        // 左辺
  Node *rhs;        // 右辺
  int val;          // kindがND_NUMの場合のみ使う
};

// トークンの種類
typedef enum {
  TK_RESERVED, // 記号
  TK_NUM, // 数字
  TK_EOF, // 終端子
} TokenKind;

typedef struct Token Token;
struct Token {
  TokenKind kind;
  Token *next;
  int val;
  char *str;
  int len;
};

// parse
extern char *user_input;
extern Token *token;
void error(char *fmt, ...);
Token *tokenize(char *p);
Node *expr();
Node *equality();
Node *relationnal();
Node *add();
Node *mul();
Node *unary();
Node *primary();

// codegen
void gen(Node *node);

