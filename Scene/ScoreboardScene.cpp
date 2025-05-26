#include "ScoreboardScene.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/AudioHelper.hpp"
#include "UI/Component/Image.hpp"
#include "UI/Component/Label.hpp"
#include "UI/Component/ImageButton.hpp"
#include <functional>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
int perPage = 5;

// static int CompareScore(const void* a, const void* b) {
//     const std::string* sa = (const std::string*)a;
//     const std::string* sb = (const std::string*)b;

//     int scoreA = std::stoi(sa->substr(sa->find_last_of(' ') + 1));
//     int scoreB = std::stoi(sb->substr(sb->find_last_of(' ') + 1));
//     return scoreB - scoreA; // 遞減排序（高分在前）
// }
static int CompareScore(const void* a, const void* b) {
    const std::string* sa = (const std::string*)a;
    const std::string* sb = (const std::string*)b;

    std::istringstream isa(*sa), isb(*sb);
    std::string nameA, timeA;
    std::string nameB, timeB;
    int scoreA, scoreB;

    isa >> nameA >> scoreA >> timeA;
    isb >> nameB >> scoreB >> timeB;

    return scoreB - scoreA;  // 分數高的排前面
}
static std::vector<std::string> LoadLines(const std::string& filepath) {
    std::vector<std::string> lines;
    std::ifstream infile(filepath);
    std::string line;
    while (std::getline(infile, line)) {
        if (!line.empty()) {
            lines.push_back(line);
        }
    }
    infile.close();
    // 使用 qsort 排序
    if (!lines.empty()) {
        qsort(lines.data(), lines.size(), sizeof(std::string), CompareScore);
    }
    // 寫回檔案
    std::ofstream outfile(filepath, std::ios::trunc);
    for (const auto& sortedLine : lines) {
        outfile << sortedLine << "\n";
    }
    outfile.close();

    return lines;
}

void ScoreboardScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;

    bool first = (currentPage == 0);
    std::string colar[2];
    if(first){
        colar[0] = "stage-select/floor.png";
    }else{
        colar[0] = "stage-select/dirt.png";
    }


    int totalPages = (scores.size() + perPage - 1) / perPage;  
    bool final = (currentPage == totalPages - 1);
    if(final){
        colar[1] = "stage-select/floor.png";
    }else{
        colar[1] = "stage-select/dirt.png";
    }
    // 標題


    AddNewObject(new Engine::Label("Scoreboard", "pirulen.ttf", 64, halfW, halfH / 4, 255, 255, 255, 255,0.5, 0.5));

    scores = LoadLines("C:/Users/user/Desktop/2025_I2P2_TowerDefense-main/Resource/scoreboard.txt");

    int start = currentPage * perPage;
    int end = std::min(static_cast<int>(scores.size()), start + perPage);

    for (int i = start; i < end; ++i) {
        // 拆解「序號. 姓名 分數 時間」
        std::istringstream iss(scores[i]);
        std::string name, time;
        int score;
        iss >> name >> score >> time;

        float y = halfH / 2 + (i - start) * 80;
        float x0 = 50;    // 左邊界座標（可再調整）

        // 序號
        AddNewObject(new Engine::Label(
            std::to_string(i + 1) + ".",
            "pirulen.ttf", 42,
            x0, y,
            255, 255, 255, 255,    // 白色
            0.0, 0.5              // 向左對齊（x 錨點 0.0）
        ));

        // 姓名（藍色）
        AddNewObject(new Engine::Label(
            name,
            "pirulen.ttf", 42,
            x0 + 100, y,
            0, 102, 204, 255,
            0.0, 0.5
        ));

        // 分數（綠色）
        AddNewObject(new Engine::Label(
            std::to_string(score),
            "pirulen.ttf", 42,
            x0 + 500, y,
            0, 204, 102, 255,
            0.0, 0.5
        ));

        // 時間（灰色）
        AddNewObject(new Engine::Label(
            time,
            "pirulen.ttf", 42,
            x0 + 800, y,
            160, 160, 160, 255,
            0.0, 0.5
        ));
    }





    // Previous 按鈕
    Engine::ImageButton* prevBtn = new Engine::ImageButton(colar[0], "stage-select/floor.png", halfW - 400, halfH*1.8 - 50, 200, 100);
    prevBtn->SetOnClickCallback(std::bind(&ScoreboardScene::PrevOnClick, this));
    AddNewControlObject(prevBtn);
    AddNewObject(new Engine::Label("Previous", "pirulen.ttf", 28, halfW - 300, halfH*1.8, 0, 0, 0, 255, 0.5, 0.5));

    // Next 按鈕
    Engine::ImageButton* nextBtn = new Engine::ImageButton(colar[1], "stage-select/floor.png", halfW + 200, halfH*1.8 - 50, 200, 100);
    nextBtn->SetOnClickCallback(std::bind(&ScoreboardScene::NextOnClick, this));
    AddNewControlObject(nextBtn);
    AddNewObject(new Engine::Label("Next", "pirulen.ttf", 32, halfW + 300, halfH*1.8, 0, 0, 0, 255, 0.5, 0.5));

    // 返回按鈕
    Engine::ImageButton* backBtn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 100, halfH*1.8 - 50, 200, 100);
    backBtn->SetOnClickCallback(std::bind(&ScoreboardScene::BackOnClick, this, 1));
    AddNewControlObject(backBtn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 32, halfW, halfH*1.8, 0, 0, 0, 255, 0.5, 0.5));

    // 如果需要背景音樂：
    // bgmInstance = AudioHelper::PlaySample("scoreboard_bgm.ogg", true, AudioHelper::BGMVolume);
}

void ScoreboardScene::Terminate() {
    if (bgmInstance) {
        AudioHelper::StopSample(bgmInstance);
        bgmInstance.reset();
    }
    IScene::Terminate();
}

void ScoreboardScene::BackOnClick(int stage) {
    currentPage = 0;
    Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}


void ScoreboardScene::PrevOnClick() {
    if (currentPage > 0) {
        currentPage--;
        //Terminate();
        //Initialize();
        Engine::GameEngine::GetInstance().ChangeScene("scoreboard");
    }
}

void ScoreboardScene::NextOnClick() {
    int totalPages = (scores.size() + perPage - 1) / perPage;
    if (currentPage < totalPages - 1) {
        currentPage++;
        //Terminate();
        //Initialize();
        Engine::GameEngine::GetInstance().ChangeScene("scoreboard");

    }
}