"""
设计模式: 享元模式 (Flyweight)
分类: 结构型

意图: 运用共享技术高效支持大量细粒度对象，减少内存占用。
核心思想: 分离内部状态（共享、不变）与外部状态（不共享、调用者传入）。
编程范式: OOP — 对象池/缓存 + 内外状态分离。
"""

from __future__ import annotations
from dataclasses import dataclass


# ── 享元：内部状态（共享）────────────────────────────────────────────────
@dataclass(frozen=True)
class TreeType:
    name: str
    color: str
    texture: str

    def draw(self, x: int, y: int) -> None:
        print(f"Tree[{self.name}/{self.color}] at ({x},{y})")


# ── 享元工厂 ──────────────────────────────────────────────────────────────
class TreeFactory:
    _types: dict[str, TreeType] = {}

    @classmethod
    def get(cls, name: str, color: str, texture: str) -> TreeType:
        key = f"{name}_{color}"
        if key not in cls._types:
            cls._types[key] = TreeType(name, color, texture)
            print(f"[Factory] created new TreeType: {key}")
        return cls._types[key]

    @classmethod
    def type_count(cls) -> int:
        return len(cls._types)


# ── 树实例：携带外部状态 ──────────────────────────────────────────────────
@dataclass
class Tree:
    x: int
    y: int
    tree_type: TreeType

    def draw(self) -> None:
        self.tree_type.draw(self.x, self.y)


# ── 演示 ──────────────────────────────────────────────────────────────────
if __name__ == "__main__":
    forest: list[Tree] = []
    for i in range(5):
        forest.append(Tree(i*10, i*5, TreeFactory.get("oak",   "green", "rough")))
        forest.append(Tree(i*7,  i*3, TreeFactory.get("pine",  "dark",  "smooth")))
        forest.append(Tree(i*3,  i*9, TreeFactory.get("birch", "white", "thin")))

    for tree in forest:
        tree.draw()

    print(f"TreeType instances: {TreeFactory.type_count()} (vs {len(forest)} trees)")
