#include "Bomb.h"

#include "Mice.h"

Bomb::Bomb()
{
}


Bomb::~Bomb()
{
}

bool Bomb::use() {
	Contraption::use();

	// need to dissapear after exploding
	fieldEntity->SetParent(OmegaEngine::Instance().GetRoot());
	fieldEntity->transform.setLocalPosition(GetEntity()->transform.getWorldPosition());
	fieldEntity->SetEnabled(true);
 
	std::cout << "BOMB is being used" << std::endl;
	PhysicsComponent* pc = GetEntity()->GetComponent<PhysicsComponent>();
	std::vector<PhysObjectType::PhysObjectType> stuff;

	if (pc->type = PhysObjectType::CONTRAPTION_DOWN) {
		stuff.push_back(PhysObjectType::CAT_DOWN);
		stuff.push_back(PhysObjectType::OBSTACLE_DOWN);
	}

	if (pc->type = PhysObjectType::CONTRAPTION_UP) {
		stuff.push_back(PhysObjectType::CAT_UP);
		stuff.push_back(PhysObjectType::OBSTACLE_UP);
	}

	auto p1 = fieldEntity->transform;
	auto pos = p1.getWorldPosition();
	auto bl = pos - glm::vec3(-1, 0, -1);
	auto tr = pos - glm::vec3(1, 0, 1);
	auto target = pc->areaCheck(stuff, new Vector2D(bl.x, bl.z), new Vector2D(tr.x, tr.z));
	if (find(target.begin(), target.end(), PhysObjectType::CAT_DOWN) != target.end()) {
		this->Drop();
		this->GetEntity()->Destroy();
	}
}

void Bomb::show() {
	Contraption::use();
}
