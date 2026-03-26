"""
设计模式: 抽象工厂模式 (Abstract Factory)
分类: 创建型

意图: 提供一个接口，创建一系列相关或相互依赖的对象，而无需指定具体类。
核心思想: 产品族 + 工厂族，切换工厂即切换整套产品风格。
编程范式: OOP — 接口隔离 + 依赖注入。
"""

from __future__ import annotations
from abc import ABC, abstractmethod


# ── 抽象产品 ──────────────────────────────────────────────────────────────
class Button(ABC):
    @abstractmethod
    def render(self) -> None: ...

class Checkbox(ABC):
    @abstractmethod
    def render(self) -> None: ...


# ── 具体产品 ──────────────────────────────────────────────────────────────
class WinButton(Button):
    def render(self) -> None: print("[Win] Button")

class WinCheckbox(Checkbox):
    def render(self) -> None: print("[Win] Checkbox")

class MacButton(Button):
    def render(self) -> None: print("[Mac] Button")

class MacCheckbox(Checkbox):
    def render(self) -> None: print("[Mac] Checkbox")


# ── 抽象工厂 ──────────────────────────────────────────────────────────────
class GUIFactory(ABC):
    @abstractmethod
    def create_button(self) -> Button: ...

    @abstractmethod
    def create_checkbox(self) -> Checkbox: ...


class WinFactory(GUIFactory):
    def create_button(self)   -> Button:   return WinButton()
    def create_checkbox(self) -> Checkbox: return WinCheckbox()

class MacFactory(GUIFactory):
    def create_button(self)   -> Button:   return MacButton()
    def create_checkbox(self) -> Checkbox: return MacCheckbox()


# ── 客户端 ────────────────────────────────────────────────────────────────
def render_ui(factory: GUIFactory) -> None:
    factory.create_button().render()
    factory.create_checkbox().render()


if __name__ == "__main__":
    for factory in (WinFactory(), MacFactory()):
        render_ui(factory)
