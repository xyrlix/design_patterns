"""
设计模式: 解释器模式 (Interpreter)
分类: 行为型

意图: 给定一个语言，定义其文法表示，并定义一个解释器来解释该语言中的句子。
核心思想: AST 节点实现 eval 接口，递归求值表达式；适用于 DSL/简单脚本。
编程范式: OOP — 递归组合表达式树；Python 展示简单 tokenizer + AST 构建。
"""

from __future__ import annotations
from abc import ABC, abstractmethod
from dataclasses import dataclass


# ── 表达式接口 ────────────────────────────────────────────────────────────
class Expr(ABC):
    @abstractmethod
    def eval(self) -> int: ...


# ── 终结符 ────────────────────────────────────────────────────────────────
@dataclass
class NumberExpr(Expr):
    value: int
    def eval(self) -> int: return self.value


# ── 非终结符 ──────────────────────────────────────────────────────────────
@dataclass
class BinaryExpr(Expr):
    op:    str
    left:  Expr
    right: Expr

    def eval(self) -> int:
        l, r = self.left.eval(), self.right.eval()
        match self.op:
            case '+': return l + r
            case '-': return l - r
            case '*': return l * r
            case '/': return l // r if r else 0
        return 0


# ── 简单 Parser（递归下降，支持 +/-/*//，含优先级）────────────────────────
class Parser:
    def __init__(self, tokens: list[str]) -> None:
        self._tokens = tokens
        self._pos    = 0

    def _peek(self) -> str | None:
        return self._tokens[self._pos] if self._pos < len(self._tokens) else None

    def _consume(self) -> str:
        t = self._tokens[self._pos]; self._pos += 1; return t

    def parse(self) -> Expr:
        return self._expr()

    def _expr(self) -> Expr:          # additive
        node = self._term()
        while self._peek() in ('+', '-'):
            op = self._consume()
            node = BinaryExpr(op, node, self._term())
        return node

    def _term(self) -> Expr:          # multiplicative
        node = self._primary()
        while self._peek() in ('*', '/'):
            op = self._consume()
            node = BinaryExpr(op, node, self._primary())
        return node

    def _primary(self) -> Expr:
        return NumberExpr(int(self._consume()))


def tokenize(s: str) -> list[str]:
    import re
    return re.findall(r'\d+|[+\-*/]', s)


# ── 演示 ──────────────────────────────────────────────────────────────────
if __name__ == "__main__":
    # 手工构建 AST
    expr = BinaryExpr('*', BinaryExpr('+', NumberExpr(3), NumberExpr(4)), NumberExpr(2))
    print(f"(3 + 4) * 2 = {expr.eval()}")

    # 解析字符串
    for s in ("3 + 4 * 2", "10 - 3 * 2"):
        ast = Parser(tokenize(s)).parse()
        print(f"{s} = {ast.eval()}")
