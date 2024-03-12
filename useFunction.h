#pragma once


inline void MakeParticles(string image, Vector2 location, PARTICLE_TYPE type, float rotationSpeed, float angle, float speed, int count, Object* p)
{
	for (int i = 0; i < count; ++i) {
		p->objectm->m_Particles.push_back(new Particle(image, location, type, rotationSpeed, angle, speed));
	}
}

inline void MakeParticlesRandom(string image, Vector2 location, PARTICLE_TYPE type, float rotationSpeed, float angle, int count, Object* p)
{
	for (int i = 0; i < count; ++i) {
		p->objectm->m_Particles.push_back(new Particle(image, location, type, rotationSpeed, angle, (rand() % 8) + 5.f));
	}
}
