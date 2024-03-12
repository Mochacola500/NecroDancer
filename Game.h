#pragma once
class Game
{
private:
	MSG mMessage;

public:
	int GameProcess();
	void Run();
	void Init();
	void Release();

public:
	Game() = default;
	~Game() = default;

	Game(const Game&) = delete;
	const Game& operator= (const Game&) = delete;
};

