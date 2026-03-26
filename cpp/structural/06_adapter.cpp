/**
 * 设计模式: 适配器模式 (Adapter)
 * 分类: 结构型
 *
 * 意图: 将一个类的接口转换成客户希望的另一个接口，使原本不兼容的类可以一起工作。
 * 核心思想: 包装器（Wrapper）封装不兼容接口，对外呈现目标接口。
 * 编程范式: OOP — 组合优于继承（对象适配器）。
 */

#include <iostream>
#include <string>
#include <memory>

// ── 目标接口（客户期望的接口）────────────────────────────────────────────
struct MediaPlayer {
    virtual void play(const std::string& filename) const = 0;
    virtual ~MediaPlayer() = default;
};

// ── 被适配者（已有的、不兼容的类）───────────────────────────────────────
struct AdvancedMediaPlayer {
    void playVlc(const std::string& f) const { std::cout << "[VLC]  playing: " << f << "\n"; }
    void playMp4(const std::string& f) const { std::cout << "[MP4]  playing: " << f << "\n"; }
};

// ── 适配器（对象适配器，用组合而非继承）─────────────────────────────────
struct MediaAdapter : MediaPlayer {
    std::string              format_;
    AdvancedMediaPlayer      player_;

    explicit MediaAdapter(std::string fmt) : format_(std::move(fmt)) {}

    void play(const std::string& filename) const override {
        if (format_ == "vlc") player_.playVlc(filename);
        else if (format_ == "mp4") player_.playMp4(filename);
        else std::cout << "Unsupported format: " << format_ << "\n";
    }
};

// ── 具体 MediaPlayer（内部用适配器扩展）─────────────────────────────────
struct AudioPlayer : MediaPlayer {
    void play(const std::string& filename) const override {
        auto ext = filename.substr(filename.rfind('.') + 1);
        if (ext == "mp3") {
            std::cout << "[MP3]  playing: " << filename << "\n";
        } else {
            MediaAdapter adapter(ext);
            adapter.play(filename);
        }
    }
};

int main() {
    AudioPlayer player;
    player.play("song.mp3");
    player.play("video.mp4");
    player.play("clip.vlc");
    return 0;
}
