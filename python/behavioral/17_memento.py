"""
设计模式: 备忘录模式 (Memento)
分类: 行为型

意图: 在不破坏封装性的前提下，捕获对象内部状态，以便日后恢复。
核心思想: 发起人创建/恢复备忘录，管理者保存历史，三角色分离。
编程范式: OOP — 状态快照；Python 用 dataclass + 嵌套类保护封装。
"""

from __future__ import annotations
from dataclasses import dataclass
from collections import deque


# ── 发起人 ────────────────────────────────────────────────────────────────
class Editor:

    @dataclass(frozen=True)
    class Memento:
        """不透明快照，仅 Editor 应使用"""
        _content: str

    def __init__(self) -> None:
        self._content = ""

    def type(self, text: str) -> None:
        self._content += text

    def print(self) -> None:
        print(f'Content: "{self._content}"')

    def save(self) -> "Editor.Memento":
        return Editor.Memento(self._content)

    def restore(self, memento: "Editor.Memento") -> None:
        self._content = memento._content


# ── 管理者 ────────────────────────────────────────────────────────────────
class History:
    def __init__(self) -> None:
        self._stack: deque[Editor.Memento] = deque()

    def push(self, m: Editor.Memento) -> None: self._stack.append(m)
    def pop(self) -> Editor.Memento | None:
        return self._stack.pop() if self._stack else None


# ── 演示 ──────────────────────────────────────────────────────────────────
if __name__ == "__main__":
    editor  = Editor()
    history = History()

    editor.type("Hello");           history.push(editor.save())
    editor.type(", World");         history.push(editor.save())
    editor.type("!!!");             editor.print()   # Hello, World!!!

    editor.restore(history.pop()); editor.print()   # Hello, World
    editor.restore(history.pop()); editor.print()   # Hello
