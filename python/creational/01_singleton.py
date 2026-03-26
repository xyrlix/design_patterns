"""
设计模式: 单例模式 (Singleton)
分类: 创建型

意图: 保证一个类只有一个实例，并提供全局访问点。
核心思想: 重写 __new__ 控制对象创建，线程安全加锁。
编程范式: OOP — metaclass / __new__ 元编程控制实例化。
"""

import threading


class SingletonMeta(type):
    """线程安全的单例元类"""
    _instances: dict = {}
    _lock: threading.Lock = threading.Lock()

    def __call__(cls, *args, **kwargs):
        with cls._lock:
            if cls not in cls._instances:
                instance = super().__call__(*args, **kwargs)
                cls._instances[cls] = instance
        return cls._instances[cls]


class Database(metaclass=SingletonMeta):
    def __init__(self) -> None:
        self.connection = "connected"
        print("[DB] connected")

    def query(self, sql: str) -> None:
        print(f"[DB] query: {sql}")


# ── 演示 ──────────────────────────────────────────────────────────────────
if __name__ == "__main__":
    db1 = Database()
    db2 = Database()

    db1.query("SELECT * FROM users")
    db2.query("INSERT INTO logs VALUES (1)")

    print(f"same instance: {db1 is db2}")
