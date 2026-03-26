"""
设计模式: 桥接模式 (Bridge)
分类: 结构型

意图: 将抽象部分与实现部分分离，使它们可以独立变化。
核心思想: 抽象层持有实现层引用，两个维度分别扩展，避免继承爆炸。
编程范式: OOP — 组合 + 依赖注入。
"""

from __future__ import annotations
from abc import ABC, abstractmethod


# ── 实现层 ────────────────────────────────────────────────────────────────
class Renderer(ABC):
    @abstractmethod
    def render_circle(self, x: float, y: float, r: float) -> None: ...


class VectorRenderer(Renderer):
    def render_circle(self, x, y, r):
        print(f"Vector: circle at ({x},{y}) r={r}")


class RasterRenderer(Renderer):
    def render_circle(self, x, y, r):
        print(f"Raster: circle at ({x},{y}) r={r}")


# ── 抽象层 ────────────────────────────────────────────────────────────────
class Shape(ABC):
    def __init__(self, renderer: Renderer) -> None:
        self.renderer = renderer

    @abstractmethod
    def draw(self) -> None: ...

    @abstractmethod
    def resize(self, factor: float) -> None: ...


class Circle(Shape):
    def __init__(self, renderer: Renderer, x: float, y: float, radius: float) -> None:
        super().__init__(renderer)
        self.x, self.y, self.radius = x, y, radius

    def draw(self) -> None:
        self.renderer.render_circle(self.x, self.y, self.radius)

    def resize(self, factor: float) -> None:
        self.radius *= factor


# ── 演示 ──────────────────────────────────────────────────────────────────
if __name__ == "__main__":
    c1 = Circle(VectorRenderer(), 0, 0, 5)
    c2 = Circle(RasterRenderer(), 3, 4, 2)

    c1.draw(); c2.draw()
    c1.resize(2); c1.draw()
