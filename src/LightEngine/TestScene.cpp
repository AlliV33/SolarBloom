#include "TestScene.h"
#include "PhysicalEntity.h"
#include "Player.h"
#include "Platform.h"
#include "Vine.h"
#include "Station.h"
#include "Bulb.h"
#include "Nenuphloat.h"
#include "Thorn.h"
#include "Fongus.h"
#include "Ivy.h"
#include "Bramble.h"

#include "DummyEntity.h"
#include "Animation.h"
#include "Debug.h"
#include <iostream>

#include <SFML/Graphics.hpp>

#include <fstream>
#include <vector>
#include <string>
#include <filesystem>

void TestScene::OnInitialize()
{
	InitAssets();
	InitTransitions();

	int height = GetWindowHeight();
	int width = GetWindowWidth();

	mCam.Resize(width, height);

	pEntity1 = CreateEntity<Player>({ 50.f, 50.f }, sf::Color::White);
	pEntity1->SetPosition(width / 2.f, 750);
	pEntity1->SetRigidBody(true);
	pEntity1->SetIsHitboxActive(true);
	pEntity1->SetGravity(true);
	pEntity1->SetKineticBody(true);

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
	std::vector<Vine*> vines;
	std::vector<Nenuphloat*> nenuphloats;
	std::vector<Station*> stations;
	std::vector<Bulb*> bulbs;
	std::vector<Thorn*> thorns;
	std::vector<Fongus*> fonguss;
	std::vector<Ivy*> ivys;
	std::vector<Bramble*> brambles;
	std::vector<std::string> map;

	std::string line;
	while (std::getline(inputFile, line)) {
		map.push_back(line);
	}

	inputFile.close();

	const sf::Vector2f BLOCK_SIZE = { 60, 50 };
	int startX = width / 2 - 250; 
	int startY = height / 2 - 200;

	/*
	Map Légende :

	Platefrom :
	X : Land2
	L : BorderLand1
	l : CornerLand5
	C : CornerLand3
	c : CornerLand4
	E : EdgeLand1
	e : EdgeLand2
	S ; SideLand1
	s : SideLand2
	b : BorderDirt1
	B : BorderDirt2
	W : DeepWater2
	D : Dirt2
	d : DeepDirt2 

	Mob :
	V : Vine
	N : Nennuphloat
	v : Station Vitale
	U : Bulb
	T : Thorn
	F : Fongus
	I : Ivy
	R : Bramble
	*/

	for (size_t y = 0; y < map.size(); ++y)
	{
		for (size_t x = 0; x < map[y].size(); ++x) 
		{
			if (map[y][x] == 'X') {
				Platform* block = CreateEntity<Platform>({ BLOCK_SIZE.x, BLOCK_SIZE.y }, sf::Color::Red);
				block->GetAnimations()->LoadAnimationGrid("Land2");
				block->SetPosition(startX + x * BLOCK_SIZE.x, startY + y * BLOCK_SIZE.y);
				block->SetRigidBody(true);
				block->SetHitbox(BLOCK_SIZE.x, BLOCK_SIZE.y);
				platforms.push_back(block);
			}
			else if (map[y][x] == 'D') {
				Platform* block = CreateEntity<Platform>({ BLOCK_SIZE.x, BLOCK_SIZE.y }, sf::Color::White);
				block->GetAnimations()->LoadAnimationGrid("Dirt3");
				block->SetPosition(startX + x * BLOCK_SIZE.x, startY + y * BLOCK_SIZE.y);
				block->SetRigidBody(true);
				block->SetHitbox(BLOCK_SIZE.x, BLOCK_SIZE.y);
				platforms.push_back(block);
			}
			else if (map[y][x] == 'd') {
				Platform* block = CreateEntity<Platform>({ BLOCK_SIZE.x, BLOCK_SIZE.y }, sf::Color::White);
				block->GetAnimations()->LoadAnimationGrid("DeepDirt2");
				block->SetPosition(startX + x * BLOCK_SIZE.x, startY + y * BLOCK_SIZE.y);
				block->SetRigidBody(true);
				block->SetHitbox(BLOCK_SIZE.x, BLOCK_SIZE.y);
				platforms.push_back(block);
			}
			else if (map[y][x] == 'L') {
				Platform* block = CreateEntity<Platform>({ BLOCK_SIZE.x, BLOCK_SIZE.y }, sf::Color::White);
				block->GetAnimations()->LoadAnimationGrid("BorderLand1");
				block->SetPosition(startX + x * BLOCK_SIZE.x, startY + y * BLOCK_SIZE.y);
				block->SetRigidBody(true);
				block->SetHitbox(BLOCK_SIZE.x, BLOCK_SIZE.y);
				platforms.push_back(block);
			}
			else if (map[y][x] == 'l') {
				Platform* block = CreateEntity<Platform>({ BLOCK_SIZE.x, BLOCK_SIZE.y }, sf::Color::White);
				block->GetAnimations()->LoadAnimationGrid("CornerLand5");
				block->SetPosition(startX + x * BLOCK_SIZE.x, startY + y * BLOCK_SIZE.y);
				block->SetRigidBody(true);
				block->SetHitbox(BLOCK_SIZE.x, BLOCK_SIZE.y);
				platforms.push_back(block);
			}
			else if (map[y][x] == 'C') {
				Platform* block = CreateEntity<Platform>({ BLOCK_SIZE.x, BLOCK_SIZE.y }, sf::Color::White);
				block->GetAnimations()->LoadAnimationGrid("CornerLand3");
				block->SetPosition(startX + x * BLOCK_SIZE.x, startY + y * BLOCK_SIZE.y);
				block->SetRigidBody(true);
				block->SetHitbox(BLOCK_SIZE.x, BLOCK_SIZE.y);
				platforms.push_back(block);
			}
			else if (map[y][x] == 'c') {
				Platform* block = CreateEntity<Platform>({ BLOCK_SIZE.x, BLOCK_SIZE.y }, sf::Color::White);
				block->GetAnimations()->LoadAnimationGrid("CornerLand4");
				block->SetPosition(startX + x * BLOCK_SIZE.x, startY + y * BLOCK_SIZE.y);
				block->SetRigidBody(true);
				block->SetHitbox(BLOCK_SIZE.x, BLOCK_SIZE.y);
				platforms.push_back(block);
			}
			else if (map[y][x] == 'E') {
				Platform* block = CreateEntity<Platform>({ BLOCK_SIZE.x, BLOCK_SIZE.y }, sf::Color::White);
				block->GetAnimations()->LoadAnimationGrid("EdgeLand1");
				block->SetPosition(startX + x * BLOCK_SIZE.x, startY + y * BLOCK_SIZE.y);
				block->SetRigidBody(true);
				block->SetHitbox(BLOCK_SIZE.x, BLOCK_SIZE.y);
				platforms.push_back(block);
			}
			else if (map[y][x] == 'e') {
				Platform* block = CreateEntity<Platform>({ BLOCK_SIZE.x, BLOCK_SIZE.y }, sf::Color::White);
				block->GetAnimations()->LoadAnimationGrid("EdgeLand2");
				block->SetPosition(startX + x * BLOCK_SIZE.x, startY + y * BLOCK_SIZE.y);
				block->SetRigidBody(true);
				block->SetHitbox(BLOCK_SIZE.x, BLOCK_SIZE.y);
				platforms.push_back(block);
			}
			else if (map[y][x] == 'S') {
				Platform* block = CreateEntity<Platform>({ BLOCK_SIZE.x, BLOCK_SIZE.y }, sf::Color::White);
				block->GetAnimations()->LoadAnimationGrid("SideLand1");
				block->SetPosition(startX + x * BLOCK_SIZE.x, startY + y * BLOCK_SIZE.y);
				block->SetRigidBody(true);
				block->SetHitbox(BLOCK_SIZE.x, BLOCK_SIZE.y);
				platforms.push_back(block);
			}
			else if (map[y][x] == 's') {
				Platform* block = CreateEntity<Platform>({ BLOCK_SIZE.x, BLOCK_SIZE.y }, sf::Color::White);
				block->GetAnimations()->LoadAnimationGrid("SideLand2");
				block->SetPosition(startX + x * BLOCK_SIZE.x, startY + y * BLOCK_SIZE.y);
				block->SetRigidBody(true);
				block->SetHitbox(BLOCK_SIZE.x, BLOCK_SIZE.y);
				platforms.push_back(block);
			}
			else if (map[y][x] == 'b') {
				Platform* block = CreateEntity<Platform>({ BLOCK_SIZE.x, BLOCK_SIZE.y }, sf::Color::White);
				block->GetAnimations()->LoadAnimationGrid("BorderDirt1");
				block->SetPosition(startX + x * BLOCK_SIZE.x, startY + y * BLOCK_SIZE.y);
				block->SetRigidBody(true);
				block->SetHitbox(BLOCK_SIZE.x, BLOCK_SIZE.y);
				platforms.push_back(block);
			}
			else if (map[y][x] == 'B') {
				Platform* block = CreateEntity<Platform>({ BLOCK_SIZE.x, BLOCK_SIZE.y }, sf::Color::White);
				block->GetAnimations()->LoadAnimationGrid("BorderDirt2");
				block->SetPosition(startX + x * BLOCK_SIZE.x, startY + y * BLOCK_SIZE.y);
				block->SetRigidBody(true);
				block->SetHitbox(BLOCK_SIZE.x, BLOCK_SIZE.y);
				platforms.push_back(block);
			}
			else if (map[y][x] == 'W') {
				Platform* block = CreateEntity<Platform>({ BLOCK_SIZE.x, BLOCK_SIZE.y }, sf::Color::White);
				block->GetAnimations()->LoadAnimationGrid("DeepWater2");
				block->SetPosition(startX + x * BLOCK_SIZE.x, startY + y * BLOCK_SIZE.y);
				block->SetRigidBody(true);
				block->SetHitbox(BLOCK_SIZE.x, BLOCK_SIZE.y);
				platforms.push_back(block);
			}




			if (map[y][x] == 'V') {
				Vine* vine = CreateEntity<Vine>({ BLOCK_SIZE.x, BLOCK_SIZE.y }, sf::Color(172, 210, 128));
				vine->SetPosition(startX + x * BLOCK_SIZE.x, startY + y * BLOCK_SIZE.y);
				vines.push_back(vine);
			}
			if (map[y][x] == 'N') {
				Nenuphloat* nenuphloat = CreateEntity<Nenuphloat>({ BLOCK_SIZE.x, BLOCK_SIZE.y }, sf::Color(65, 106, 36));
				nenuphloat->SetPosition(startX + x * BLOCK_SIZE.x, startY + y * BLOCK_SIZE.y);
				nenuphloats.push_back(nenuphloat);
			}
			if (map[y][x] == 'v') {
				Station* station = CreateEntity<Station>({ BLOCK_SIZE.x, BLOCK_SIZE.y }, sf::Color(158, 144, 193));
				station->SetPosition(startX + x * BLOCK_SIZE.x, startY + y * BLOCK_SIZE.y - 50.f );
				stations.push_back(station);
			}
			if (map[y][x] == 'U') {
				Bulb* bulb = CreateEntity<Bulb>({ BLOCK_SIZE.x, BLOCK_SIZE.y }, sf::Color(213, 170, 63));
				bulb->SetPosition(startX + x * BLOCK_SIZE.x, startY + y * BLOCK_SIZE.y);
				bulbs.push_back(bulb);
			}
			if (map[y][x] == 'T') {
				Thorn* thorn = CreateEntity<Thorn>({ BLOCK_SIZE.x, BLOCK_SIZE.y }, sf::Color(133, 46, 46));
				thorn->SetPosition(startX + x * BLOCK_SIZE.x, startY + y * BLOCK_SIZE.y);
				thorns.push_back(thorn);
			}
			if (map[y][x] == 'F') {
				Fongus* fongus = CreateEntity<Fongus>({ BLOCK_SIZE.x, BLOCK_SIZE.y }, sf::Color(0, 255, 0));
				fongus->SetPosition(startX + x * BLOCK_SIZE.x, startY + y * BLOCK_SIZE.y);
				fonguss.push_back(fongus);
			}
			if (map[y][x] == 'I') {
				Ivy* ivy = CreateEntity<Ivy>({ BLOCK_SIZE.x, BLOCK_SIZE.y }, sf::Color(254, 237, 92));
				ivy->SetPosition(startX + x * BLOCK_SIZE.x, startY + y * BLOCK_SIZE.y);
				ivys.push_back(ivy);
			}
			if (map[y][x] == 'R') {
				Bramble* bramble = CreateEntity<Bramble>({ BLOCK_SIZE.x, BLOCK_SIZE.y }, sf::Color(66, 44, 40));
				bramble->SetPosition(startX + x * BLOCK_SIZE.x, startY + y * BLOCK_SIZE.y);
				brambles.push_back(bramble);
			}
		}
	}

	pEntitySelected = nullptr;

	assetManager->GetMusic("MainMusic")->play();
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
		mCam.FollowPlayer();
	}

	UpdateCamera();

	SoundManager();
}

void TestScene::UpdateCamera()
{
	sf::Vector2f camSize = mCam.GetSize();
	sf::Vector2f pPos = GetPlayer()->GetPosition();
	sf::Vector2f posLimite = sf::Vector2f(10000, 825);

	float minX = camSize.x / 2;
	float maxX = posLimite.x - camSize.x / 2;
	float minY = camSize.y / 2;
	float maxY = posLimite.y - camSize.y / 2;

	float newCamX = std::clamp(pPos.x, minX, maxX);
	float newCamY = std::clamp(pPos.y, minY, maxY);

	mCam.SetPosition({ newCamX, newCamY });

	GameManager::Get()->SetCamera(mCam);
}

bool TestScene::IsAllowedToCollide(int tag1, int tag2)
{
	return mInteractions[tag1][tag2];
}

void TestScene::InitSounds()
{
	assetManager->LoadMusic("MainMusic", "../../../res/Assets/music/mainmusic.wav")->setLoop(true);
	assetManager->GetMusic("MainMusic")->setVolume(100 * mVolume);
	assetManager->LoadSound("Waterdrop", "../../../res/Assets/sfx/waterdrop.wav")->setVolume(100 * mVolume);
	assetManager->LoadSound("WeedKiller", "../../../res/Assets/sfx/weedkiller.wav")->setVolume(75 * mVolume);
	assetManager->GetSound("WeedKiller")->setLoop(true);
	assetManager->LoadSound("Checkpoint", "../../../res/Assets/sfx/checkpoint.wav")->setVolume(50 * mVolume);
	assetManager->LoadSound("ReloadWater", "../../../res/Assets/sfx/reloadwater.wav")->setVolume(30 * mVolume);
	assetManager->LoadSound("PlayerJump", "../../../res/Assets/sfx/jump.wav")->setVolume(50 * mVolume);
	assetManager->LoadSound("PlayerShooting", "../../../res/Assets/sfx/shooting.wav")->setVolume(100 * mVolume);
	assetManager->LoadSound("PlayerDash", "../../../res/Assets/sfx/dash.wav")->setVolume(50 * mVolume);
	assetManager->LoadSound("Landing", "../../../res/Assets/sfx/landing.wav")->setVolume(25 * mVolume);
	assetManager->LoadSound("Bonk", "../../../res/Assets/sfx/bonk.wav")->setVolume(25 * mVolume);
	assetManager->LoadSound("Falling", "../../../res/Assets/sfx/falling.wav")->setVolume(50 * mVolume);
	assetManager->LoadSound("Hurt", "../../../res/Assets/sfx/hurt.wav")->setVolume(50 * mVolume);

	//A bouger au merge
	assetManager->LoadSound("Dead", "../../../res/Assets/sfx/dead.wav")->setVolume(25 * mVolume);
	assetManager->LoadSound("Button", "../../../res/Assets/sfx/button.wav")->setVolume(30 * mVolume);
}

void TestScene::SoundManager()
{
	if (mProgressToChangeVolume > mDelayToChangeVolume)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		{
			AddRemoveVolume(-0.1f);

			UpdateVolume();

			mProgressToChangeVolume = 0.f;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
		{
			AddRemoveVolume(0.1f);

			UpdateVolume();


			mProgressToChangeVolume = 0.f;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
		{
			if (isStopSound == false)
			{
				isStopSound = true; 
				StopSound(); 
			}
			else
			{
				isStopSound = false; 
				UpdateVolume(); 
			}

			mProgressToChangeVolume = 0.f;
		}
	}
	else
	{
		mProgressToChangeVolume += GetDeltaTime();
	}
}

void TestScene::UpdateVolume() 
{
	if (isStopSound)
		return;

	assetManager->GetMusic("MainMusic")->setVolume(100 * mVolume);
	assetManager->GetSound("Waterdrop")->setVolume(100 * mVolume);
	assetManager->GetSound("WeedKiller")->setVolume(75 * mVolume);
	assetManager->GetSound("WeedKiller")->setLoop(true);
	assetManager->GetSound("Checkpoint")->setVolume(50 * mVolume);
	assetManager->GetSound("ReloadWater")->setVolume(30 * mVolume);
	assetManager->GetSound("PlayerJump")->setVolume(75 * mVolume);
	assetManager->GetSound("PlayerShooting")->setVolume(100 * mVolume);
	assetManager->GetSound("PlayerDash")->setVolume(50 * mVolume);
	assetManager->GetSound("Landing")->setVolume(25 * mVolume);
	assetManager->GetSound("Bonk")->setVolume(25 * mVolume);
	assetManager->GetSound("Falling")->setVolume(50 * mVolume);
	assetManager->GetSound("Hurt")->setVolume(50 * mVolume);

	//A bouger au merge
	assetManager->GetSound("Dead")->setVolume(25 * mVolume);
	assetManager->GetSound("Button")->setVolume(30 * mVolume);
}

void TestScene::StopSound()
{
	assetManager->GetMusic("MainMusic")->setVolume(0);
	assetManager->GetSound("Waterdrop")->setVolume(0);
	assetManager->GetSound("WeedKiller")->setVolume(0);
	assetManager->GetSound("WeedKiller")->setLoop(true);
	assetManager->GetSound("Checkpoint")->setVolume(0);
	assetManager->GetSound("ReloadWater")->setVolume(0);
	assetManager->GetSound("PlayerJump")->setVolume(0);
	assetManager->GetSound("PlayerShooting")->setVolume(0);
	assetManager->GetSound("PlayerDash")->setVolume(0);
	assetManager->GetSound("Landing")->setVolume(0);
	assetManager->GetSound("Bonk")->setVolume(0);
	assetManager->GetSound("Falling")->setVolume(0);
	assetManager->GetSound("Hurt")->setVolume(0);

	//A bouger au merge
	assetManager->GetSound("Dead")->setVolume(0);
	assetManager->GetSound("Button")->setVolume(0);
}

void TestScene::InitTextures()
{
	assetManager->LoadTexture("Terrain", "../../../res/Assets/Textures/SpriteSheet_Terrain.png");
	assetManager->LoadTexture("Nenuphloat", "../../../res/Assets/Textures/SpriteSheet_Nenuphloat.png");
	assetManager->LoadTexture("Vine", "../../../res/Assets/Textures/SpriteSheet_Liane.png");
	assetManager->LoadTexture("Station", "../../../res/Assets/Textures/SpriteSheet_Station.png");
	assetManager->LoadTexture("Bulb", "../../../res/Assets/Textures/SpriteSheet_BulbeLumina.png");
	assetManager->LoadTexture("Bramble", "../../../res/Assets/Textures/SpriteSheet_Bramble.png");
	assetManager->LoadTexture("Ivy", "../../../res/Assets/Textures/SpriteSheet_Ivy.png");
	assetManager->LoadTexture("Thorn", "../../../res/Assets/Textures/SpriteSheet_Thorn.png");
	assetManager->LoadTexture("Fongus", "../../../res/Assets/Textures/SpriteSheet_Fongus.png");
	assetManager->LoadTexture("FongusCloud", "../../../res/Assets/Textures/SpriteSheet_FongusCloud.png");
	assetManager->LoadTexture("BrambleExplosion", "../../../res/Assets/Textures/SpriteSheet_BrambleExplosion.png");
}

void TestScene::InitAssets()
{
	InitSounds();
	InitTextures();
}

void TestScene::InitTransitions()
{
	for (int i = 0; i < TAG_COUNT; i++)
	{
		for (int j = 0; j < TAG_COUNT; j++)
		{
			mInteractions[i][j] = false;
		}
	}

	SetInteractionWith(TPlayer, TPlatform, true);
	SetInteractionWith(TWater, TPlatform, true); 

	SetInteractionWith(TPlayer, TAlly, true);
	SetInteractionWith(TPlayer, TEnemy, true);

	SetInteractionWith(TWater, TAlly, true);
	SetInteractionWith(TAcid, TEnemy, true);
}

void TestScene::AddRemoveVolume(float value)
{
	if (mProgressToChangeVolume <= mDelayToChangeVolume || isStopSound)
		return;

	mVolume += value;

	if (mVolume > 1)
	{
		mVolume = 1;
		return;
	}

	if (mVolume <= 0)
	{
		mVolume = 0;
		return;
	}

	assetManager->GetSound("Button")->play();
}
