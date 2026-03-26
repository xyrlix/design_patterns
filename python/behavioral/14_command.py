"""
设计模式: 命令模式 (Command)
分类: 行为型

意图: 将请求封装为对象，从而支持参数化、排队、日志、撤销/重做操作。
核心思想: 命令对象封装"动作 + 接收者"，调用者只依赖命令接口。
编程范式: OOP — 封装变化 + 撤销栈；Python 额外展示函数作为命令。
"""

from __future__ import annotations
from abc import ABC, abstractmethod
from collections import deque


# ── 接收者 ────────────────────────────────────────────────────────────────
class TextEditor:
    def __init__(self) -> None:
        self.text = ""

    def append(self, s: str) -> None:   self.text += s
    def delete_last(self, n: int) -> None: self.text = self.text[:-n] if n else self.text
    def print(self) -> None:            print(f'Text: "{self.text}"')


# ── 命令接口 ──────────────────────────────────────────────────────────────
class Command(ABC):
    @abstractmethod
    def execute(self) -> None: ...

    @abstractmethod
    def undo(self) -> None: ...


# ── 具体命令 ──────────────────────────────────────────────────────────────
class AppendCommand(Command):
    def __init__(self, editor: TextEditor, value: str) -> None:
        self._editor = editor
        self._value  = value

    def execute(self) -> None: self._editor.append(self._value)
    def undo(self)    -> None: self._editor.delete_last(len(self._value))


# ── 调用者 ────────────────────────────────────────────────────────────────
class CommandInvoker:
    def __init__(self) -> None:
        self._history: deque[Command] = deque()

    def run(self, cmd: Command) -> None:
        cmd.execute()
        self._history.append(cmd)

    def undo(self) -> None:
        if self._history:
            self._history.pop().undo()


# ── 演示 ──────────────────────────────────────────────────────────────────
if __name__ == "__main__":
    editor  = TextEditor()
    invoker = CommandInvoker()

    invoker.run(AppendCommand(editor, "Hello"))
    invoker.run(AppendCommand(editor, ", World"))
    editor.print()

    invoker.undo(); editor.print()
    invoker.undo(); editor.print()
