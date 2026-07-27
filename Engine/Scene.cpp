#include "pch.h"
#include "Scene.h"
#include "Actor.h"

namespace nu {

	void Scene::AddActor(Actor* actor) {
		actor->m_scene = this;
		m_pendingActors.push_back(actor); 
	}

	void Scene::Update(float dt) {
		// uodate actors
		for (auto actor : m_actors) {
			actor->Update(dt);
		}
		// update collisions
		UpdateCollisions();

		//remove destroyed actors
		std::erase_if(m_actors, [](auto actor) { return actor->m_destroyed; });

		// add pending actors
		m_actors.insert(m_actors.end(), m_pendingActors.begin(), m_pendingActors.end());
		m_pendingActors.clear();
	}

	void Scene::Draw(const class Renderer& renderer) {
		for (auto actor : m_actors) {
			actor->Draw(renderer);
		}
	}

	void Scene::UpdateCollisions() {
		for (auto& actorA : m_actors) {
			for (auto& actorB : m_actors) {
				// Check for self, or destroyed objects
				if (actorA == actorB || actorA->m_destroyed || actorB->m_destroyed) {
					continue;
				}

				float distance = (actorA->m_transform.position - actorB->m_transform.position).Length();
				if (distance <= actorA->GetRadius() + actorB->GetRadius()) {
					actorA->OnCollision(actorB);
					actorB->OnCollision(actorA);
				}
			}
		}
	}
}