"""
设计模式: 观察者模式 (Observer)
分类: 行为型

意图: 定义对象间一对多依赖，当主题状态改变时所有依赖者自动收到通知。
核心思想: 主题维护观察者列表，状态变化时广播通知，实现发布-订阅。
编程范式: OOP — 事件驱动；Python 额外展示弱引用避免内存泄漏。
"""

from __future__ import annotations
from abc import ABC, abstractmethod
import weakref


# ── 观察者接口 ────────────────────────────────────────────────────────────
class Observer(ABC):
    @abstractmethod
    def update(self, event: str, value: int) -> None: ...


# ── 主题混入 ──────────────────────────────────────────────────────────────
class Subject:
    def __init__(self) -> None:
        self._observers: list[weakref.ref[Observer]] = []

    def subscribe(self, o: Observer) -> None:
        self._observers.append(weakref.ref(o))

    def unsubscribe(self, o: Observer) -> None:
        self._observers = [r for r in self._observers if r() is not None and r() is not o]

    def _notify(self, event: str, value: int) -> None:
        dead = []
        for ref in self._observers:
            obs = ref()
            if obs is None:
                dead.append(ref)
            else:
                obs.update(event, value)
        for r in dead:
            self._observers.remove(r)


# ── 具体主题 ──────────────────────────────────────────────────────────────
class StockMarket(Subject):
    def __init__(self) -> None:
        super().__init__()
        self._price = 100

    def set_price(self, p: int) -> None:
        self._price = p
        self._notify("price_changed", p)


# ── 具体观察者 ────────────────────────────────────────────────────────────
class Logger(Observer):
    def update(self, event: str, value: int) -> None:
        print(f"[Logger] {event} = {value}")


class AlertSystem(Observer):
    def __init__(self, threshold: int) -> None:
        self.threshold = threshold

    def update(self, event: str, value: int) -> None:
        if value > self.threshold:
            print(f"[Alert!] Price {value} > threshold {self.threshold}")


# ── 演示 ──────────────────────────────────────────────────────────────────
if __name__ == "__main__":
    market = StockMarket()
    logger = Logger()
    alert  = AlertSystem(120)

    market.subscribe(logger)
    market.subscribe(alert)

    market.set_price(110)
    market.set_price(130)

    market.unsubscribe(logger)
    market.set_price(90)   # logger 不再收到
