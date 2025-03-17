#include "TestScene.h"
#include "PhysicalEntity.h"
#include "Player.h"
#include "Platform.h"
#include "DummyEntity.h"

#include "Debug.h"
#include <iostream>

#include <SFML/Graphics.hpp>

#include <fstream>
#include <vector>
#include <string>
#include "SFML/Graphics.hpp"
#include <filesystem>

void TestScene::OnInitialize()
{
	int height = GetWindowHeight();
	int width = GetWindowWidth();

	mCam.Resize(width, height);

	pEntity1 = CreateEntity<Player>({ 50.f, 50.f }, sf::Color::White);
	pEntity1->SetPosition(width / 2.f, height / 2.f);
	pEntity1->SetRigidBody(true);
	pEntity1->SetIsHitboxActive(true);
	pEntity1->SetGravity(true);
	
	sf::Texture* texture = assetManager->GetTexture("../../../res/Assets/248259.png");
	pEntity1->GetShape()->setTexture(texture);

	mCam.SetOwner(pEntity1);
	mCam.SetFocus(true);

	std::string filepath = "../../../res/map.txt";
	std::ifstream inputFile(filepath);

	if (!std::filesystem::exists(filepath)) {
		std::cerr << "Erreur : Le fichier n'existe pas a l'emplacement : " << filepath << std::endl;
	}

	if (!inputFile) {
		std::cerr << "Erreur : Impossible d'ouvrir " << filepath << std::endl;
	}

	std::vector<Platform*> platforms;
	std::vector<std::string> map;

	std::string line;
	while (std::getline(inputFile, line)) {
		map.push_back(line);
	}

	inputFile.close();

	const int BLOCK_SIZE = 24;
	int startX = width / 2 - 250; 
	int startY = height / 2 - 200;

	for (size_t y = 0; y < map.size(); ++y) {
		for (size_t x = 0; x < map[y].size(); ++x) {
			if (map[y][x] == 'X') {
				Platform* block = CreateEntity<Platform>({ 24,24 }, sf::Color::Red);
				block->SetPosition(startX + x * BLOCK_SIZE, startY + y * BLOCK_SIZE);
				block->SetRigidBody(false);
				block->SetHitbox(BLOCK_SIZE, BLOCK_SIZE);
				platforms.push_back(block);
			}
		}
	}


	pEntitySelected = nullptr;
}

void TestScene::OnEvent(const sf::Event& event)
{
	if (event.type != sf::Event::EventType::MouseButtonPressed && event.type != sf::Event::EventType::KeyPressed)
		return;

	sf::RenderWindow* win = GameManager::Get()->GetWindow();
	sf::Vector2f mousePos = win->mapPixelToCoords(sf::Mouse::getPosition(*win));

	if (event.mouseButton.button == sf::Mouse::Button::Right)
	{
		TrySetSelectedEntity(pEntity1, mousePos.x, mousePos.y);
	}

	if (event.mouseButton.button == sf::Mouse::Button::Left)
	{
		if (pEntitySelected != nullptr)
		{
			pEntitySelected->GoToPosition(mousePos.x, mousePos.y, 200.f);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
	{
		if (mCam.GetFocus())
		{
			mCam.SetFocus(false);
		}
		else
		{
			if (pEntity1 != nullptr)
			{
				if (pEntity1->ToDestroy() == false)
					mCam.SetFocus(true);
			}
		}
	}

	if (pEntitySelected != nullptr)
	{
		if (event.key.code == sf::Keyboard::H)
		{
			if (pEntitySelected->GetHitbox()->isActive)
				pEntitySelected->SetIsHitboxActive(false);
			else
				pEntitySelected->SetIsHitboxActive();
		}
	}
}

void TestScene::TrySetSelectedEntity(PhysicalEntity* pEntity, int x, int y)
{
	if (pEntity->IsInside(x, y) == false)
		return;

	pEntitySelected = pEntity;
}

void TestScene::OnUpdate()
{
	float dt = GetDeltaTime();

	if (mCam.GetFocus() == true)
	{
		mCam.FollowPlayer(); // Pour suivre l'entite 1   
	}

	if (pEntitySelected != nullptr)
	{
		sf::Vector2f position = pEntitySelected->GetPosition();
		Debug::DrawCircle(position.x, position.y, 10, sf::Color::Blue);
	}

	UpdateCamera();
}

void TestScene::UpdateCamera()
{
	GameManager::Get()->SetCamera(mCam);
}
