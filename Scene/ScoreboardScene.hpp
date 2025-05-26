#ifndef SCOREBOARDSCENE_HPP
#define SCOREBOARDSCENE_HPP
#include "Engine/IScene.hpp"
#include <allegro5/allegro_audio.h>
#include <memory>
/*
class ScoreboardScene : public Engine::IScene {
public:
    ScoreboardScene() = default;
    virtual ~ScoreboardScene() = default;
    int currentPage = 0;
    std::vector<std::string> scores;
    void RenderScores();
    void PrevOnClick();
    void NextOnClick();
    void Initialize() override;
    void Terminate() override;
    void Update(float dt) override {}
    void BackOnClick(int stage);

private:
    std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
};*/
namespace Engine { class Label; }

class ScoreboardScene : public Engine::IScene {
public:
    ScoreboardScene() = default;
    virtual ~ScoreboardScene() = default;

    void Initialize() override;
    void Terminate() override;
    void Update(float dt) override {}

    void PrevOnClick();
    void NextOnClick();
    void BackOnClick(int stage);

private:
   // void RenderScores();

    int currentPage = 0;
    std::vector<std::string> scores;
    std::vector<Engine::Label*> scoreLabels;    // << 用來記錄當前頁面用到的 Label
    void RemoveScoreLabel(Engine::Label* lbl);
    std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
};
#endif   // LOSESCENE_HPP
