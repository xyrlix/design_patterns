"""
设计模式: 状态模式 (State)
分类: 行为型

意图: 允许对象在内部状态改变时改变行为，对象看起来似乎修改了它的类。
核心思想: 将每个状态封装为独立类，Context 持有当前状态并委托行为。
编程范式: OOP — 多态替换 if-else 状态机；状态自主转换。
"""

from __future__ import annotations
from abc import ABC, abstractmethod


# ── 状态接口 ──────────────────────────────────────────────────────────────
class State(ABC):
    @abstractmethod
    def handle(self, ctx: "TrafficLight") -> None: ...

    @abstractmethod
    def name(self) -> str: ...


# ── Context ───────────────────────────────────────────────────────────────
class TrafficLight:
    def __init__(self, state: State) -> None:
        self.state = state

    def next(self) -> None:
        print(f"Current: {self.state.name()} → ", end="")
        self.state.handle(self)
        print(self.state.name())


# ── 具体状态 ──────────────────────────────────────────────────────────────
class GreenState(State):
    def handle(self, ctx: TrafficLight) -> None: ctx.state = YellowState()
    def name(self) -> str: return "Green"

class YellowState(State):
    def handle(self, ctx: TrafficLight) -> None: ctx.state = RedState()
    def name(self) -> str: return "Yellow"

class RedState(State):
    def handle(self, ctx: TrafficLight) -> None: ctx.state = GreenState()
    def name(self) -> str: return "Red"


# ── 演示 ──────────────────────────────────────────────────────────────────
if __name__ == "__main__":
    light = TrafficLight(GreenState())
    for _ in range(6):
        light.next()
