#pragma once

enum class PARTICLE_TYPE
{
	ATTACK,
	DIG,
	HIT,
	FOLLOW,
	SHOVING,
	DEAD,
	SPREAD,
	END
};

// 파티클 시스템
/*****************************************************
1. 오브젝트 매니저에서 관리함. 생명주기가 끝나면 자동으로 자원 회수
2. 사용시 MakeParticles 함수를 통해 1개에서 다수 객체 생성

******************************************************/
class Particle
{
private:
	Animation image;
	PARTICLE_TYPE type;
	Vector2 location;
	bool alive;
	float alpha;
	float rotationSpeed;
	float angle;
	float speed;
	float timer;
	float shootangle;
	float up;
	Image* image2;
	Vector2 particleSize;

public:
	Particle(string image, Vector2 location, PARTICLE_TYPE type, Vector2 particleSize = { TILESIZE_X ,TILESIZE_X }, float angle = 0.f)
	{
		this->image.Initialize(image, &(this->location), 6.0, 25 * TIME->getElapedTime());
		this->particleSize = particleSize;
		this->location = location + 26.f;
		if (type == PARTICLE_TYPE::DEAD) this->location -= 26.f;
		this->type = type;
		alive = true;
		alpha = 1.0f;
		this->angle = angle;
	}

	Particle(string image, Vector2 location, PARTICLE_TYPE type, float rotationSpeed, float angle = 0.f, float speed = 5.f)
	{
		this->type = type;
		this->image2 = IMAGE->FindImage(image);
		this->location = location + 26.f;
		this->rotationSpeed = rotationSpeed;
		this->angle = angle;
		this->speed = speed;
		shootangle = static_cast<float>(rand() % 360);
		alive = true;
		alpha = 1.0f;
	}

	~Particle() = default;

	void Render()
	{
		switch (type)
		{
		case PARTICLE_TYPE::DEAD:
			image.SetImageSize(Vector2(TILESIZE_X,TILESIZE_Y));
			image.SetAlpha(alpha);
			image.Render();
			alpha -= 0.02f;
			break;

		case PARTICLE_TYPE::ATTACK:
			image.SetAngle(angle);
			image.SetImageSize(particleSize);
			image.CalibratedImageLocation(Vector2(-15, -40));
			image.Render();
			if (image.CheckLastImage()) {
				this->alive = false;
			}
			break;

		case PARTICLE_TYPE::SHOVING:
			image.SetImageSize(Vector2(42, 42));
			image.CalibratedImageLocation(Vector2(-16, -6));
			image.Render();
			if (image.CheckLastImage()) {
				this->alive = false;
			}
			break;

		case PARTICLE_TYPE::DIG:
			image2->SetAlpha(alpha);
			image2->SetSize(Vector2(15, 15));
			image2->Render(this->location, true);

			alpha -= 0.1f;
			timer += 1.f;

			this->location.x += cosf(shootangle * 3.141592f / 180.f) * speed;
			this->location.y -= sinf(shootangle * 3.141592f / 180.f) * speed;

			if (timer > 32) {
				this->alive = false;
			}
			break;
		case PARTICLE_TYPE::HIT:
			image2->SetAlpha(alpha);
			image2->SetSize(Vector2(15, 15));
			image2->Render(this->location, true);

			alpha -= 0.05f;
			timer += 1.f;

			this->location.x += cosf(shootangle * 3.141592f / 180.f) * speed;
			this->location.y -= sinf(shootangle * 3.141592f / 180.f) * speed;

			if (timer > 32) {
				this->alive = false;
			}
			break;

		case PARTICLE_TYPE::SPREAD:
			break;
		}
	}


	bool EndImage() const
	{
		return alive;
	}
};
