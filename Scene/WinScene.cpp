
#include <functional>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Point.hpp"
#include "PlayScene.hpp"
#include "UI/Component/Image.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "WinScene.hpp"
#include <random>
#include <fstream>
#include <ctime>
std::string playerName = "";
void WinScene::Initialize() {
    ticks = 0;
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    AddNewObject(new Engine::Image("win/benjamin-sad.png", halfW, halfH+40, 0, 0, 0.5, 0.5));
    AddNewObject(new Engine::Label("You Win!", "pirulen.ttf", 48, halfW, halfH / 4 - 10, 255, 255, 255, 255, 0.5, 0.5));
    Engine::ImageButton *btn;
    btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", halfW - 200, halfH * 7 / 4 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&WinScene::BackOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 7 / 4, 0, 0, 0, 255, 0.5, 0.5));
    
    nameLabel = new Engine::Label(
        "",                  // 初始為空，因為玩家還未輸入
        "pirulen.ttf", 36,   // 字型與大小，與其他標籤一致
        halfW, halfH / 4 + 120,  // 位置：螢幕中間，稍微低於「Enter your name: 」
        255, 255, 255, 255,  // 白色文字
        0.5, 0.5            // 錨點置中
    );
    AddNewObject(nameLabel);
    score = PlayScene::lives * 100 + PlayScene::money;
    // 2. 顯示分數
    AddNewObject(new Engine::Label(
        "Score: " + std::to_string(score),
        "pirulen.ttf", 36,
        halfW, halfH / 4 + 40,
        255, 255, 0, 255,
        0.5, 0.5
    ));

    // 3. 讀取玩家名稱並寫入 score.txt（每次附加）

    //AddNewObject(new Engine::Label("Enter your name: ", "pirulen.ttf", 48, halfW, halfH / 4 - 10, 255, 255, 255, 255, 0.5, 0.5));
    AddNewObject(new Engine::Label(
        "Enter your name: ",
        "pirulen.ttf", 36,
        halfW, halfH / 4 + 80,
        255, 255, 0, 255,
        0.5, 0.5
    ));
    // std::ofstream outfile("C:/Users/user/Desktop/2025_I2P2_TowerDefense-main/Resource/scoreboard.txt", std::ios::app);
    // if (outfile.is_open()) {
    //     outfile << playerName << " " << score << "\n";
    //     //outfile << playerName << " " << score << " " << buf << "\n";
    // }
    // outfile.close();
    bgmId = AudioHelper::PlayAudio("win.wav");
}
void WinScene::Terminate() {
    IScene::Terminate();
    AudioHelper::StopBGM(bgmId);
}
void WinScene::Update(float deltaTime) {
    ticks += deltaTime;
    if (ticks > 4 && ticks < 100 &&
        dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetScene("play"))->MapId == 2) {
        int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
        int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
        int halfW = w / 2;
        int halfH = h / 2;
        ticks = 100;
        bgmId = AudioHelper::PlayBGM("happy.ogg");
    }
}
void WinScene::BackOnClick(int stage) {
    // Change to select scene.
    std::string name = inputName.empty() ? "Anonymous" : inputName;
    std::ofstream outfile("C:/Users/user/Desktop/2025_I2P2_TowerDefense-main/Resource/scoreboard.txt", std::ios::app);
   
    // if (outfile.is_open()) {
    //     outfile << name << " " << score << "\n";
    //     outfile.close();
    // }
    if (outfile.is_open()) {
        // 1. 取得現在時間
        std::time_t t = std::time(nullptr);
        std::tm tm;
        localtime_s(&tm, &t);
        // 2. 格式化時間字串
        char buf[20];
        // 例如：2025-05-17_14:45:30
        std::strftime(buf, sizeof(buf), "%Y-%m-%d_%H:%M:%S", &tm);

        // 3. 寫入「名稱 分數 時間」
        outfile << name << " "
                << score << " "
                << buf
                << "\n";

        outfile.close();
    }
    Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}
void WinScene::OnKeyDown(int keyCode) {
    IScene::OnKeyDown(keyCode);
    // Handle alphanumeric input, space, and backspace
    if (keyCode >= ALLEGRO_KEY_A && keyCode <= ALLEGRO_KEY_Z) {
        if (inputName.length() < 10) {
            inputName += 'A' + (keyCode - ALLEGRO_KEY_A);
        }
    } else if (keyCode >= ALLEGRO_KEY_0 && keyCode <= ALLEGRO_KEY_9) {
        if (inputName.length() <10) {
            inputName += '0' + (keyCode - ALLEGRO_KEY_0);
        }
    } else if (keyCode == ALLEGRO_KEY_SPACE) {
        if (inputName.length() <10) {
            inputName += ' ';
        }
    } else if (keyCode == ALLEGRO_KEY_BACKSPACE) {
        if (!inputName.empty()) {
            inputName.pop_back();
        }
    }
    // Update displayed name
    nameLabel->Text = inputName;
}
