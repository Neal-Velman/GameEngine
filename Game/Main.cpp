#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include <fmod.hpp>
#include "Assets.h"
#include "SpaceGame.h"

#include <iostream>
#include <vector>
#include <map>


int main()
{

    // INITIALIZATION
    nu::SetWorkingDirectory("Assets");

    nu::Engine::Get().Initialize();

    SpaceGame game;
    game.Initialize();

    // Create font system
    nu::Font* font = new nu::Font();
    font->Load("Fonts/Jersey10Charted-Regular.ttf", 64);

    // Render the font
    nu::Text* text = new nu::Text(font);
    text->Create(nu::Engine::Get().GetRenderer(), "Hello World", nu::Color{1.0f, 1.0f, 1.0f});

    // create audio system
    FMOD::System* audio;
    FMOD::System_Create(&audio);

    void* extradriverdata = nullptr;
    audio->init(32, FMOD_INIT_NORMAL, extradriverdata);

    nu::Scene scene;

    PlayerDesc playerDesc;
    playerDesc.name = "Player";
    playerDesc.model = Assets::playerModel;
    playerDesc.transform = nu::Transform{ nu::Vector2 { 860.0f, 512.0f }, 0.0f, 50.0f };
    playerDesc.speed = 600.0f;
    playerDesc.damping = 1.5f;

    Player* player = new Player { playerDesc };
    scene.AddActor(player);

    for (int i = 0; i < 20; i++) {
        EnemyDesc enemyDesc;
        enemyDesc.name = "Enemy";
        enemyDesc.model = Assets::playerModel;
        enemyDesc.transform = nu::Transform{ nu::Vector2 { nu::RandomFloat((float)nu::Engine::Get().GetRenderer().GetWidth()), nu::RandomFloat((float)nu::Engine::Get().GetRenderer().GetHeigt())}, 180.0f, 25.0f };
        enemyDesc.speed = nu::RandomFloat(200.0f, 400.0f);
        enemyDesc.damping = 1.5f;

        Enemy* enemy = new Enemy { enemyDesc };
        scene.AddActor(enemy);
    }

    std::vector<nu::Vector2> points;
    std::vector<FMOD::Sound*> sounds;

    // MAIN LOOP


    FMOD::Sound* sound = nullptr;
    audio->createSound("Audio/test.wav", FMOD_DEFAULT, 0, &sound);
    audio->playSound(sound, 0, false, nullptr);

    FMOD::Sound* sound2 = nullptr;
    audio->createSound("Audio/bass.wav", FMOD_DEFAULT, 0, &sound2);
    sounds.push_back(sound2);

    FMOD::Sound* sound3 = nullptr;
    audio->createSound("Audio/cowbell.wav", FMOD_DEFAULT, 0, &sound3);
    sounds.push_back(sound3);


    bool quit = false;

    // UPDATE
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                quit = true;
            }
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE) {
                quit = true;
            }
        }

        // UPDATE ENGINE
        nu::Engine::Get().Update();
        audio->update();

        float dt = nu::Engine::Get().GetTime().GetDeltaTime();
        scene.Update(dt);
        /*player.Update(nu::engine.GetTime().GetDeltaTime());
        player.SetRotation(player.GetTransform().rotation);
        enemy.Update(dt);*/

        if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_1))
        {
            audio->playSound(sounds[0], nullptr, false, nullptr);
        }

        if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_2))
        {
            audio->playSound(sounds[1], nullptr, false, nullptr);
        }


        if (nu::Engine::Get().GetInput().GetMouseDown(nu::Input::MouseButton::LEFT)) {
            if (points.empty()) {
                points.push_back(nu::Engine::Get().GetInput().GetMousePosition());
            }
            else {
                nu::Vector2 v = points.back() - nu::Engine::Get().GetInput().GetMousePosition();
                if (v.Length() > 10.0f) {
                    points.push_back(nu::Engine::Get().GetInput().GetMousePosition());
                }
            }

        }

        if (nu::Engine::Get().GetInput().GetButtonPressed(nu::Input::MouseButton::RIGHT)) {
            if (!points.empty()) {
                points.pop_back();
            }
        }
        

        // RENDER
        nu::Engine::Get().GetRenderer().SetColor(0.0f, 0.0f, 0.0f);
        nu::Engine::Get().GetRenderer().Clear();

        for (int i = 0; i < (int)points.size() - 1; i++) {
            nu::Engine::Get().GetRenderer().SetColor(nu::RandomFloat(), nu::RandomFloat(), nu::RandomFloat());
            nu::Engine::Get().GetRenderer().DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i+1].y);
            nu::Engine::Get().GetRenderer().DrawFillRect(points[i].x, points[i].y, 10, 10);
        }

        // Character
        scene.Draw(nu::Engine::Get().GetRenderer());
        text->Draw(nu::Engine::Get().GetRenderer(), 40.0f, 40.0f);

        nu::Engine::Get().GetRenderer().Present();
    }

    // SHUTDOWN
    nu::Engine::Get().Shutdown();
    
    return 0;
}