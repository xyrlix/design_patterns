"""
设计模式: 原型模式 (Prototype)
分类: 创建型

意图: 通过复制现有对象来创建新对象，而不是通过实例化类。
核心思想: 对象自身提供 clone 接口，Python 用 copy.deepcopy 实现深拷贝。
编程范式: OOP — 多态克隆 + 原型注册表。
"""

import copy
from abc import ABC, abstractmethod


# ── 原型接口 ──────────────────────────────────────────────────────────────
class Shape(ABC):
    def __init__(self, color: str) -> None:
        self.color = color

    @abstractmethod
    def clone(self) -> "Shape": ...

    @abstractmethod
    def draw(self) -> None: ...


# ── 具体原型 ──────────────────────────────────────────────────────────────
class Circle(Shape):
    def __init__(self, color: str, radius: int) -> None:
        super().__init__(color)
        self.radius = radius

    def clone(self) -> "Circle":
        return copy.deepcopy(self)

    def draw(self) -> None:
        print(f"Circle color={self.color} r={self.radius}")


class Rectangle(Shape):
    def __init__(self, color: str, w: int, h: int) -> None:
        super().__init__(color)
        self.w, self.h = w, h

    def clone(self) -> "Rectangle":
        return copy.deepcopy(self)

    def draw(self) -> None:
        print(f"Rectangle color={self.color} {self.w}x{self.h}")


# ── 原型注册表 ────────────────────────────────────────────────────────────
class ShapeRegistry:
    def __init__(self) -> None:
        self._cache: dict[str, Shape] = {}

    def add(self, key: str, shape: Shape) -> None:
        self._cache[key] = shape

    def get(self, key: str) -> Shape:
        return self._cache[key].clone()


# ── 演示 ──────────────────────────────────────────────────────────────────
if __name__ == "__main__":
    registry = ShapeRegistry()
    registry.add("red_circle",     Circle("red", 10))
    registry.add("blue_rectangle", Rectangle("blue", 5, 3))

    s1 = registry.get("red_circle")
    s2 = registry.get("blue_rectangle")
    s3 = registry.get("red_circle")

    s1.draw(); s2.draw(); s3.draw()
    print(f"s1 is not s3 (different objects): {s1 is not s3}")
