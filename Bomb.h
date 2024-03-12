#pragma once
class Bomb :
	public Object
{
private:
	Animation booooom;
	int count;
	int swapCount;
	int swapTime;
	bool isSwap;
	bool last;

public:
	Bomb(Vector2 position) {
		booooom.Initialize("bomb", &mCenter);
		booooom.CalibratedImageLocation(Vector2(5,2));
		this->mCenter = position;
		count = 0;
		swapCount = 0;
		swapTime = 8;
		isSwap = true;
		last = false;
	}
	~Bomb() = default;

	void Update() override
	{
		if (count == 3) {
			this->mAlive = false;
			Explosive();
		}
	}

	void Render() override
	{
		if (booooom.CheckLastImage() || last)
		{
			last = true;
			if (swapCount > swapTime) {
				swapCount = 0;
				swapTime--;
				isSwap == true ? isSwap = false : isSwap = true;
			}
			else
			{
				swapCount++;
			}
			if (isSwap) {
				booooom.FrameRender(Vector2(4, 0));
			}
			else
			{
				booooom.FrameRender(Vector2(3, 0));
			}
		}
		else
		{
			booooom.SetImageSize(Vector2(TILESIZE_X,TILESIZE_Y));
			booooom.Render();
		}
	}

	void Explosive()
	{
			for (int i = 0; i < 9; ++i) {
				int exdx = mCenter.x + xdx[i] * TILESIZE_X;
				int exdy = mCenter.y + xdy[i] * TILESIZE_Y;
				Vector2 destroyed (exdx, exdy);
				OBJECT->m_Particles.push_back(new Particle("3x3_explosion", destroyed, PARTICLE_TYPE::SHOVING));
				if (OBJECT->GetTile(destroyed)->item != nullptr) {
					SAFE_DELETE(OBJECT->GetTile(destroyed)->item);
					OBJECT->GetTile(destroyed)->item = nullptr;
				}
				if (OBJECT->GetTile(destroyed)->p != nullptr) {
					OBJECT->GetTile(destroyed)->p->GetDamege(100);
				}
			}
			this->mAlive = false;
		
	}

	void BeatUpdate() override
	{
		count++;
	}
};

