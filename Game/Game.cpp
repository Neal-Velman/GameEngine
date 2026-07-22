#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include <fmod.hpp>

#include <iostream>
#include <vector>

int main()
{

    // create audio system
    FMOD::System* audio;
    FMOD::System_Create(&audio);

    void* extradriverdata = nullptr;
    audio->init(32, FMOD_INIT_NORMAL, extradriverdata);




    // INITIALIZATION
    nu::engine.Initialize();

    nu::Mesh mesh{ { { 2, 0 }, { -1, 2 }, { -0.5, 1.5 }, { 0, 0 }, {-0.5, -1.5 }, { -1, -2 }, { 2, 0 } }, nu::Color{ 0.75f, 0.25f, 0.25f } };
    nu::Mesh mesh2{ { { 2, 0 }, { -1, 3 }, { -1, 2 }, { 0, 0 }, { -1, -2 }, { -1, -3 }, { 2, 0 } }, nu::Color{ 0.25f, 0.5f, 0.25f } };
    nu::Mesh mesh3{ { { 2, 0 }, { -1, 2 }, { 0, 0 }, { -1, -2 }, { 2, 0 } }, nu::Color{ 0.1f, 0.2f, 0.75f } };
    nu::Model model{ std::vector<nu::Mesh> { mesh, mesh2, mesh3 } };

    nu::Scene scene;

    PlayerDesc playerDesc;
    playerDesc.name = "Player";
    playerDesc.model = model;
    playerDesc.transform = nu::Transform{ nu::Vector2 { 860.0f, 512.0f }, 0.0f, 50.0f };
    playerDesc.speed = 400.0f;

    Player* player = new Player { playerDesc };
    scene.AddActor(player);

    for (int i = 0; i < 20; i++) {
        EnemyDesc enemyDesc;
        enemyDesc.name = "Enemy";
        enemyDesc.model = model;
        enemyDesc.transform = nu::Transform{ nu::Vector2 { nu::RandomFloat((float)nu::engine.GetRenderer().GetWidth()), nu::RandomFloat((float)nu::engine.GetRenderer().GetHeigt())}, 180.0f, 25.0f };
        enemyDesc.speed = 400.0f;

        Enemy* enemy = new Enemy { enemyDesc };
        scene.AddActor(enemy);
    }

    std::vector<nu::Vector2> points;

    // MAIN LOOP

    std::vector<FMOD::Sound*> sounds;

    FMOD::Sound* sound = nullptr;
    audio->createSound("test.wav", FMOD_DEFAULT, 0, &sound);

    FMOD::Sound* sound2 = nullptr;
    audio->createSound("bass.wav", FMOD_DEFAULT, 0, &sound2);
    sounds.push_back(sound2);

    FMOD::Sound* sound3 = nullptr;
    audio->createSound("cowbell.wav", FMOD_DEFAULT, 0, &sound3);
    sounds.push_back(sound3);

    audio->playSound(sound, 0, false, nullptr);

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
        nu::engine.Update();
        audio->update();

        float dt = nu::engine.GetTime().GetDeltaTime();
        scene.Update(dt);
        /*player.Update(nu::engine.GetTime().GetDeltaTime());
        player.SetRotation(player.GetTransform().rotation);
        enemy.Update(dt);*/

        if (nu::engine.GetInput().GetKeyPressed(SDL_SCANCODE_1))
        {
            audio->playSound(sounds[0], nullptr, false, nullptr);
        }

        if (nu::engine.GetInput().GetKeyPressed(SDL_SCANCODE_2))
        {
            audio->playSound(sounds[1], nullptr, false, nullptr);
        }


        if (nu::engine.GetInput().GetMouseDown(nu::Input::MouseButton::LEFT)) {
            if (points.empty()) {
                points.push_back(nu::engine.GetInput().GetMousePosition());
            }
            else {
                nu::Vector2 v = points.back() - nu::engine.GetInput().GetMousePosition();
                if (v.Length() > 10.0f) {
                    points.push_back(nu::engine.GetInput().GetMousePosition());
                }
            }

        }

        if (nu::engine.GetInput().GetButtonPressed(nu::Input::MouseButton::RIGHT)) {
            if (!points.empty()) {
                points.pop_back();
            }
        }
        

        // RENDER
        nu::engine.GetRenderer().SetColor(0.0f, 0.0f, 0.0f);
        nu::engine.GetRenderer().Clear();

        for (int i = 0; i < (int)points.size() - 1; i++) {
            nu::engine.GetRenderer().SetColor(nu::RandomFloat(), nu::RandomFloat(), nu::RandomFloat());
            nu::engine.GetRenderer().DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i+1].y);
            nu::engine.GetRenderer().DrawFillRect(points[i].x, points[i].y, 10, 10);
        }

        // Character
        /*player.Draw(nu::engine.GetRenderer());
        enemy.Draw(nu::engine.GetRenderer());*/
        scene.Draw(nu::engine.GetRenderer());

        nu::engine.GetRenderer().Present();
    }

    // SHUTDOWN
    nu::engine.Shutdown();
    

    return 0;
}