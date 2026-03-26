/**
 * 设计模式: 解释器模式 (Interpreter)
 * 分类: 行为型
 *
 * 意图: 给定一个语言，定义它的文法的一种表示，并定义一个解释器，该解释器使用该表示来解释语言中的句子。
 * 核心思想: AST（抽象语法树）节点实现 interpret 接口，递归求值表达式。
 * 编程范式: OOP — 递归组合 + 表达式树；适用于 DSL/简单脚本解析。
 *
 * 示例语言：简单整数四则运算（中缀表达式解析）
 */

#include <iostream>
#include <memory>
#include <string>

// ── 表达式接口 ────────────────────────────────────────────────────────────
struct Expr {
    virtual int eval() const = 0;
    virtual ~Expr() = default;
};

// ── 终结符：数字字面量 ────────────────────────────────────────────────────
struct NumberExpr : Expr {
    int value;
    explicit NumberExpr(int v) : value(v) {}
    int eval() const override { return value; }
};

// ── 非终结符：二元运算 ────────────────────────────────────────────────────
struct BinaryExpr : Expr {
    char op;
    std::unique_ptr<Expr> left, right;
    BinaryExpr(char op, std::unique_ptr<Expr> l, std::unique_ptr<Expr> r)
        : op(op), left(std::move(l)), right(std::move(r)) {}

    int eval() const override {
        int l = left->eval(), r = right->eval();
        switch (op) {
            case '+': return l + r;
            case '-': return l - r;
            case '*': return l * r;
            case '/': return r != 0 ? l / r : 0;
        }
        return 0;
    }
};

// ── 辅助构造函数 ──────────────────────────────────────────────────────────
auto num(int v)  { return std::make_unique<NumberExpr>(v); }
auto add(std::unique_ptr<Expr> l, std::unique_ptr<Expr> r) {
    return std::make_unique<BinaryExpr>('+', std::move(l), std::move(r));
}
auto mul(std::unique_ptr<Expr> l, std::unique_ptr<Expr> r) {
    return std::make_unique<BinaryExpr>('*', std::move(l), std::move(r));
}

int main() {
    // (3 + 4) * 2 = 14
    auto expr = mul(add(num(3), num(4)), num(2));
    std::cout << "(3 + 4) * 2 = " << expr->eval() << "\n";

    // 10 - 3 * 2 = 4（此处 AST 已表示优先级）
    auto expr2 = std::make_unique<BinaryExpr>('-', num(10), mul(num(3), num(2)));
    std::cout << "10 - 3 * 2 = " << expr2->eval() << "\n";
    return 0;
}
