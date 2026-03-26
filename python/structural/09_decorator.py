"""
设计模式: 装饰器模式 (Decorator)
分类: 结构型

意图: 动态地为对象附加额外职责，是继承的灵活替代方案。
核心思想: 装饰器与被装饰对象实现相同接口，层层包裹扩展行为。
编程范式: OOP — 组合 + 透明包装；Python 同时展示函数式装饰器。
"""

from __future__ import annotations
from abc import ABC, abstractmethod
from functools import wraps


# ── 组件接口 ──────────────────────────────────────────────────────────────
class TextProcessor(ABC):
    @abstractmethod
    def process(self, text: str) -> str: ...


# ── 具体组件 ──────────────────────────────────────────────────────────────
class PlainText(TextProcessor):
    def process(self, text: str) -> str:
        return text


# ── 抽象装饰器 ────────────────────────────────────────────────────────────
class TextDecorator(TextProcessor):
    def __init__(self, wrapped: TextProcessor) -> None:
        self._wrapped = wrapped


# ── 具体装饰器 ────────────────────────────────────────────────────────────
class UpperCaseDecorator(TextDecorator):
    def process(self, text: str) -> str:
        return self._wrapped.process(text).upper()


class TrimDecorator(TextDecorator):
    def process(self, text: str) -> str:
        return self._wrapped.process(text).strip()


class ExclamationDecorator(TextDecorator):
    def process(self, text: str) -> str:
        return self._wrapped.process(text) + "!!!"


# ── 演示：OOP 装饰器 ──────────────────────────────────────────────────────
if __name__ == "__main__":
    pipeline = ExclamationDecorator(
               UpperCaseDecorator(
               TrimDecorator(
               PlainText())))

    print(pipeline.process("  hello world  "))

    # ── 函数式装饰器（Python 语言特性展示）────────────────────────────────
    def log_call(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            print(f"[log] calling {func.__name__}")
            return func(*args, **kwargs)
        return wrapper

    @log_call
    def greet(name: str) -> str:
        return f"Hello, {name}!"

    print(greet("xyrlix"))
