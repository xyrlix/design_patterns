"""
设计模式: 代理模式 (Proxy)
分类: 结构型

意图: 为另一个对象提供替代品或占位符，以控制对这个对象的访问。
核心思想: 代理与真实对象实现相同接口，访问前后插入额外逻辑。
编程范式: OOP — 缓存代理；Python 额外展示 __getattr__ 动态代理。
"""

from __future__ import annotations
from abc import ABC, abstractmethod


# ── 服务接口 ──────────────────────────────────────────────────────────────
class DataService(ABC):
    @abstractmethod
    def fetch(self, key: str) -> str: ...


# ── 真实服务 ──────────────────────────────────────────────────────────────
class RealDataService(DataService):
    def fetch(self, key: str) -> str:
        print(f'[Real] fetching "{key}" from network...')
        return f"data_for_{key}"


# ── 缓存代理 ──────────────────────────────────────────────────────────────
class CachingProxy(DataService):
    def __init__(self, real: DataService) -> None:
        self._real  = real
        self._cache: dict[str, str] = {}

    def fetch(self, key: str) -> str:
        if key in self._cache:
            print(f'[Cache] hit for "{key}"')
            return self._cache[key]
        result = self._real.fetch(key)
        self._cache[key] = result
        return result


# ── 演示 ──────────────────────────────────────────────────────────────────
if __name__ == "__main__":
    proxy = CachingProxy(RealDataService())
    proxy.fetch("user:1")
    proxy.fetch("user:2")
    proxy.fetch("user:1")   # 命中缓存
    proxy.fetch("user:2")   # 命中缓存
