"""
设计模式: 模板方法模式 (Template Method)
分类: 行为型

意图: 在基类中定义算法骨架，将某些步骤推迟到子类，子类可重定义步骤而不改变算法结构。
核心思想: 基类控制流程，抽象方法交由子类实现细节。
编程范式: OOP — 控制反转（Hollywood Principle）。
"""

from abc import ABC, abstractmethod


# ── 抽象基类（模板）──────────────────────────────────────────────────────
class DataProcessor(ABC):

    # 模板方法：定义算法骨架
    def process(self) -> None:
        self.read_data()
        self.process_data()
        self.write_result()

    @abstractmethod
    def read_data(self) -> None: ...

    @abstractmethod
    def process_data(self) -> None: ...

    def write_result(self) -> None:   # Hook（可覆盖）
        print("  [write]   saving to default output")


# ── 具体子类 ──────────────────────────────────────────────────────────────
class CSVProcessor(DataProcessor):
    def read_data(self)    -> None: print("  [read]    reading CSV")
    def process_data(self) -> None: print("  [process] parsing CSV rows")


class JsonProcessor(DataProcessor):
    def read_data(self)    -> None: print("  [read]    reading JSON")
    def process_data(self) -> None: print("  [process] deserializing JSON")
    def write_result(self) -> None: print("  [write]   sending to REST API")


# ── 演示 ──────────────────────────────────────────────────────────────────
if __name__ == "__main__":
    for name, proc in (("CSV", CSVProcessor()), ("JSON", JsonProcessor())):
        print(f"=== {name} ===")
        proc.process()
