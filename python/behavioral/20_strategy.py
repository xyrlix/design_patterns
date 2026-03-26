"""
设计模式: 策略模式 (Strategy)
分类: 行为型

意图: 定义一系列算法，将每个算法封装起来，使它们可以互换。
核心思想: 策略接口 + 具体策略，Context 在运行时切换算法。
编程范式: OOP — 依赖注入；Python 函数即策略（一等函数）。
"""

from __future__ import annotations
from abc import ABC, abstractmethod
from typing import Callable


# ── 策略接口 ──────────────────────────────────────────────────────────────
class SortStrategy(ABC):
    @abstractmethod
    def sort(self, data: list[int]) -> list[int]: ...

    @abstractmethod
    def name(self) -> str: ...


# ── 具体策略（类形式）────────────────────────────────────────────────────
class BubbleSort(SortStrategy):
    def sort(self, data: list[int]) -> list[int]:
        d = data[:]
        for i in range(len(d)):
            for j in range(len(d) - i - 1):
                if d[j] > d[j+1]:
                    d[j], d[j+1] = d[j+1], d[j]
        return d

    def name(self) -> str: return "BubbleSort"


class QuickSort(SortStrategy):
    def sort(self, data: list[int]) -> list[int]:
        return sorted(data)   # 借用 Timsort

    def name(self) -> str: return "QuickSort"


# ── Context ───────────────────────────────────────────────────────────────
class Sorter:
    def __init__(self, strategy: SortStrategy) -> None:
        self._strategy = strategy

    def set_strategy(self, s: SortStrategy) -> None:
        self._strategy = s

    def execute(self, data: list[int]) -> None:
        result = self._strategy.sort(data)
        print(f"{self._strategy.name()}: {result}")


# ── 函数即策略（Python 惯用写法）────────────────────────────────────────
def functional_sort(data: list[int],
                    key_fn: Callable[[int], int] = lambda x: x) -> list[int]:
    return sorted(data, key=key_fn)


# ── 演示 ──────────────────────────────────────────────────────────────────
if __name__ == "__main__":
    data = [5, 3, 1, 4, 2]

    sorter = Sorter(BubbleSort())
    sorter.execute(data)

    sorter.set_strategy(QuickSort())
    sorter.execute(data)

    # 函数式策略
    print("reverse:", functional_sort(data, key_fn=lambda x: -x))
