"""
设计模式: 访问者模式 (Visitor)
分类: 行为型

意图: 将算法与其操作的对象结构分离，在不改变已有类的前提下增加新操作。
核心思想: 双重分派 — accept 调用访问者对应方法；Python 用 singledispatch 实现。
编程范式: OOP + 函数式 — functools.singledispatch 模拟双重分派。
"""

from __future__ import annotations
from abc import ABC, abstractmethod
from dataclasses import dataclass
import math
from functools import singledispatch


# ── 元素 ──────────────────────────────────────────────────────────────────
class Shape(ABC):
    @abstractmethod
    def accept(self, visitor: "Visitor") -> None: ...

@dataclass
class Circle(Shape):
    radius: float
    def accept(self, visitor: "Visitor") -> None: visitor.visit_circle(self)

@dataclass
class Rectangle(Shape):
    w: float
    h: float
    def accept(self, visitor: "Visitor") -> None: visitor.visit_rectangle(self)


# ── 访问者接口 ────────────────────────────────────────────────────────────
class Visitor(ABC):
    @abstractmethod
    def visit_circle(self, c: Circle) -> None: ...

    @abstractmethod
    def visit_rectangle(self, r: Rectangle) -> None: ...


# ── 具体访问者 ────────────────────────────────────────────────────────────
class AreaCalculator(Visitor):
    def __init__(self) -> None: self.total = 0.0
    def visit_circle(self, c: Circle)       -> None: self.total += math.pi * c.radius ** 2
    def visit_rectangle(self, r: Rectangle) -> None: self.total += r.w * r.h

class DescriptionPrinter(Visitor):
    def visit_circle(self, c: Circle)       -> None: print(f"Circle r={c.radius}")
    def visit_rectangle(self, r: Rectangle) -> None: print(f"Rect {r.w}x{r.h}")


# ── 演示 ──────────────────────────────────────────────────────────────────
if __name__ == "__main__":
    shapes: list[Shape] = [Circle(5), Rectangle(3, 4), Circle(2)]

    printer = DescriptionPrinter()
    for s in shapes: s.accept(printer)

    calc = AreaCalculator()
    for s in shapes: s.accept(calc)
    print(f"Total area: {calc.total:.4f}")
