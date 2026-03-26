"""
设计模式: 工厂方法模式 (Factory Method)
分类: 创建型

意图: 定义创建对象的接口，由子类决定实例化哪个类。
核心思想: 抽象基类声明工厂方法，子类覆盖以返回具体产品。
编程范式: OOP — 多态 + 依赖倒置（高层依赖抽象）。
"""

from __future__ import annotations
from abc import ABC, abstractmethod


# ── 产品接口 ──────────────────────────────────────────────────────────────
class Logger(ABC):
    @abstractmethod
    def log(self, msg: str) -> None: ...


class ConsoleLogger(Logger):
    def log(self, msg: str) -> None:
        print(f"[Console] {msg}")


class FileLogger(Logger):
    def log(self, msg: str) -> None:
        print(f"[File]    {msg}")


# ── 工厂接口 ──────────────────────────────────────────────────────────────
class LoggerFactory(ABC):
    @abstractmethod
    def create(self) -> Logger: ...

    # 模板方法：工厂方法嵌入业务逻辑
    def deliver(self, msg: str) -> None:
        logger = self.create()
        logger.log(msg)


class ConsoleLoggerFactory(LoggerFactory):
    def create(self) -> Logger:
        return ConsoleLogger()


class FileLoggerFactory(LoggerFactory):
    def create(self) -> Logger:
        return FileLogger()


# ── 演示 ──────────────────────────────────────────────────────────────────
if __name__ == "__main__":
    for factory in (ConsoleLoggerFactory(), FileLoggerFactory()):
        factory.deliver("application started")
