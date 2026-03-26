"""
设计模式: 组合模式 (Composite)
分类: 结构型

意图: 将对象组合成树形结构表示"部分-整体"层次，使客户对单个对象和组合对象使用一致。
核心思想: 叶节点与容器节点实现相同接口，递归组合形成树。
编程范式: OOP — 递归组合 + 统一接口。
"""

from __future__ import annotations
from abc import ABC, abstractmethod


# ── 组件接口 ──────────────────────────────────────────────────────────────
class FileSystem(ABC):
    def __init__(self, name: str) -> None:
        self.name = name

    @abstractmethod
    def ls(self, depth: int = 0) -> None: ...

    def _indent(self, d: int) -> str:
        return "  " * d


# ── 叶节点 ────────────────────────────────────────────────────────────────
class File(FileSystem):
    def ls(self, depth: int = 0) -> None:
        print(f"{self._indent(depth)}- {self.name}")


# ── 容器节点 ──────────────────────────────────────────────────────────────
class Directory(FileSystem):
    def __init__(self, name: str) -> None:
        super().__init__(name)
        self._children: list[FileSystem] = []

    def add(self, item: FileSystem) -> "Directory":
        self._children.append(item)
        return self

    def ls(self, depth: int = 0) -> None:
        print(f"{self._indent(depth)}+ {self.name}/")
        for child in self._children:
            child.ls(depth + 1)


# ── 演示 ──────────────────────────────────────────────────────────────────
if __name__ == "__main__":
    root = Directory("root")
    src  = Directory("src").add(File("main.cpp")).add(File("utils.cpp"))
    inc  = Directory("include").add(File("utils.h"))

    root.add(src).add(inc).add(File("CMakeLists.txt"))
    root.ls()
