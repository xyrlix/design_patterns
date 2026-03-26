"""
设计模式: 迭代器模式 (Iterator)
分类: 行为型

意图: 提供顺序访问聚合对象元素的方法，而不暴露其内部表示。
核心思想: 迭代器封装遍历逻辑；Python 通过 __iter__/__next__ 实现迭代器协议。
编程范式: OOP — 迭代器协议；Python Generator 作为惰性迭代器。
"""

from __future__ import annotations
from typing import Iterator as IterT


# ── 自定义迭代器 ──────────────────────────────────────────────────────────
class NumberRange:
    """支持自定义步长的数字范围，惰性求值"""

    def __init__(self, start: int, stop: int, step: int = 1) -> None:
        self.start, self.stop, self.step = start, stop, step

    def __iter__(self) -> IterT[int]:
        return _NumberRangeIterator(self.start, self.stop, self.step)

    def __repr__(self) -> str:
        return f"NumberRange({self.start}, {self.stop}, {self.step})"


class _NumberRangeIterator:
    def __init__(self, current: int, stop: int, step: int) -> None:
        self._current = current
        self._stop    = stop
        self._step    = step

    def __iter__(self) -> "_NumberRangeIterator":
        return self

    def __next__(self) -> int:
        if self._current >= self._stop:
            raise StopIteration
        val = self._current
        self._current += self._step
        return val


# ── Generator 版本（Python 惯用写法）────────────────────────────────────
def number_range_gen(start: int, stop: int, step: int = 1):
    current = start
    while current < stop:
        yield current
        current += step


# ── 演示 ──────────────────────────────────────────────────────────────────
if __name__ == "__main__":
    r = NumberRange(0, 20, 3)
    print(list(r))
    print("sum =", sum(r))

    print("generator:", list(number_range_gen(0, 20, 3)))
