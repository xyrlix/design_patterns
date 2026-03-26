"""
设计模式: 中介者模式 (Mediator)
分类: 行为型

意图: 用一个中介对象封装一系列对象交互，使各对象不需要直接引用彼此。
核心思想: 同事对象只与中介者通信，中介者协调各同事的交互。
编程范式: OOP — 集中控制 + 解耦网状依赖为星型依赖。
"""

from __future__ import annotations
from abc import ABC, abstractmethod
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    pass


# ── 中介者接口 ────────────────────────────────────────────────────────────
class Mediator(ABC):
    @abstractmethod
    def notify(self, sender: "Colleague", event: str) -> None: ...


# ── 同事基类 ──────────────────────────────────────────────────────────────
class Colleague:
    def __init__(self, name: str) -> None:
        self.name     = name
        self.mediator: Mediator | None = None


# ── 具体同事 ──────────────────────────────────────────────────────────────
class Button(Colleague):
    def click(self) -> None:
        print(f"[Button:{self.name}] clicked")
        if self.mediator:
            self.mediator.notify(self, "click")


class TextBox(Colleague):
    def __init__(self, name: str) -> None:
        super().__init__(name)
        self.text = ""

    def set_text(self, t: str) -> None:
        self.text = t
        print(f'[TextBox:{self.name}] = "{t}"')

    def clear(self) -> None:
        self.text = ""
        print(f"[TextBox:{self.name}] cleared")


# ── 具体中介者 ────────────────────────────────────────────────────────────
class DialogMediator(Mediator):
    def __init__(self, btn: Button, input_box: TextBox, status_box: TextBox) -> None:
        self._btn    = btn
        self._input  = input_box
        self._status = status_box
        for c in (btn, input_box, status_box):
            c.mediator = self

    def notify(self, sender: Colleague, event: str) -> None:
        if sender is self._btn and event == "click":
            self._status.set_text(f"Submitted: {self._input.text}")
            self._input.clear()


# ── 演示 ──────────────────────────────────────────────────────────────────
if __name__ == "__main__":
    btn    = Button("Submit")
    inp    = TextBox("Input")
    status = TextBox("Status")
    DialogMediator(btn, inp, status)

    inp.set_text("hello@example.com")
    btn.click()
