"""
设计模式: 责任链模式 (Chain of Responsibility)
分类: 行为型

意图: 将请求沿着处理者链传递，每个处理者决定处理或传递请求。
核心思想: 处理者持有下一个处理者引用，形成链式结构，解耦请求发送者和接收者。
编程范式: OOP — 链式调用 + 单一职责。
"""

from __future__ import annotations
from abc import ABC, abstractmethod
from typing import Optional


# ── 处理者接口 ────────────────────────────────────────────────────────────
class Handler(ABC):
    def __init__(self) -> None:
        self._next: Optional[Handler] = None

    def set_next(self, handler: Handler) -> Handler:
        self._next = handler
        return handler  # 支持链式设置

    @abstractmethod
    def handle(self, request: int) -> None: ...

    def _pass(self, request: int) -> None:
        if self._next:
            self._next.handle(request)


# ── 具体处理者 ────────────────────────────────────────────────────────────
class LowLevelHandler(Handler):
    def handle(self, req: int) -> None:
        if req < 10:
            print(f"LowLevel handled: {req}")
        else:
            self._pass(req)


class MidLevelHandler(Handler):
    def handle(self, req: int) -> None:
        if req < 100:
            print(f"MidLevel handled: {req}")
        else:
            self._pass(req)


class HighLevelHandler(Handler):
    def handle(self, req: int) -> None:
        print(f"HighLevel handled: {req}")


# ── 演示 ──────────────────────────────────────────────────────────────────
if __name__ == "__main__":
    low  = LowLevelHandler()
    mid  = MidLevelHandler()
    high = HighLevelHandler()

    low.set_next(mid).set_next(high)

    for r in (5, 50, 500):
        low.handle(r)
