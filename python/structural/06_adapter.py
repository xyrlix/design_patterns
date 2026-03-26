"""
设计模式: 适配器模式 (Adapter)
分类: 结构型

意图: 将一个类的接口转换成客户希望的另一个接口，使不兼容的类可以一起工作。
核心思想: 包装器封装不兼容接口，对外呈现目标接口。
编程范式: OOP — 组合优于继承（对象适配器）。
"""

from abc import ABC, abstractmethod


# ── 目标接口 ──────────────────────────────────────────────────────────────
class MediaPlayer(ABC):
    @abstractmethod
    def play(self, filename: str) -> None: ...


# ── 被适配者 ──────────────────────────────────────────────────────────────
class AdvancedMediaPlayer:
    def play_vlc(self, f: str) -> None: print(f"[VLC]  playing: {f}")
    def play_mp4(self, f: str) -> None: print(f"[MP4]  playing: {f}")


# ── 适配器 ────────────────────────────────────────────────────────────────
class MediaAdapter(MediaPlayer):
    def __init__(self, fmt: str) -> None:
        self._fmt    = fmt
        self._player = AdvancedMediaPlayer()

    def play(self, filename: str) -> None:
        if self._fmt == "vlc":
            self._player.play_vlc(filename)
        elif self._fmt == "mp4":
            self._player.play_mp4(filename)
        else:
            print(f"Unsupported format: {self._fmt}")


# ── 具体播放器 ────────────────────────────────────────────────────────────
class AudioPlayer(MediaPlayer):
    def play(self, filename: str) -> None:
        ext = filename.rsplit(".", 1)[-1]
        if ext == "mp3":
            print(f"[MP3]  playing: {filename}")
        else:
            MediaAdapter(ext).play(filename)


# ── 演示 ──────────────────────────────────────────────────────────────────
if __name__ == "__main__":
    player = AudioPlayer()
    for f in ("song.mp3", "video.mp4", "clip.vlc"):
        player.play(f)
