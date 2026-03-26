"""
设计模式: 外观模式 (Facade)
分类: 结构型

意图: 为子系统中的一组接口提供统一的高层接口，使子系统更容易使用。
核心思想: 外观类封装复杂子系统，对外暴露简洁接口，降低耦合度。
编程范式: OOP — 封装 + 迪米特法则。
"""


# ── 子系统组件 ────────────────────────────────────────────────────────────
class CPU:
    def freeze(self) -> None:          print("CPU: freeze")
    def jump(self, pos: int) -> None:  print(f"CPU: jump to {pos:#x}")
    def execute(self) -> None:         print("CPU: execute")


class Memory:
    def load(self, pos: int, data: str) -> None:
        print(f'Memory: load "{data}" at {pos:#x}')


class HardDrive:
    def read(self, sector: int, size: int) -> str:
        print(f"HDD: read sector={sector} size={size}")
        return "bootloader"


# ── 外观 ──────────────────────────────────────────────────────────────────
class ComputerFacade:
    def __init__(self) -> None:
        self._cpu    = CPU()
        self._memory = Memory()
        self._hdd    = HardDrive()

    def start(self) -> None:
        print("=== booting ===")
        self._cpu.freeze()
        data = self._hdd.read(0, 512)
        self._memory.load(0x0, data)
        self._cpu.jump(0x0)
        self._cpu.execute()
        print("=== boot done ===")


# ── 演示 ──────────────────────────────────────────────────────────────────
if __name__ == "__main__":
    ComputerFacade().start()
