#include "Coil.h"

#include "Cat.h"
#include "PlayerComponent.h"
#include "Physics/PhysicsManager.h"

Coil::Coil() :
	HandleOnCollision(this, &Coil::OnCollision)
{
}


Coil::~Coil()
{
}

bool Coil::use() {
	Contraption::use();
	
	std::cout << "COIL is being used" << std::endl;

	// drop self
	GetEntity()->transform.setLocalPosition(GetEntity()->transform.getWorldPosition());
	GetEntity()->SetParent(OmegaEngine::Instance().GetRoot());
	fieldEntity->SetEnabled(true);

	std::cout << "COIL is being used" << std::endl;
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
		// deal damage
		this->Drop();
		this->GetEntity()->Destroy();
	}
}

void Coil::show() {
	Contraption::show();
}

void Coil::OnCollision(PhysicsComponent * other)
{

}

void Coil::OnInitialized()
{
	Contraption::OnInitialized();
	// GetEntity()->GetComponent<PhysicsComponent>()->onCollide.Attach(HandleOnCollision);
}

void Coil::Update(float dt)
{	
	if (!_isPlaced) return;

	auto pos = GetEntity()->transform.getWorldPosition();
	auto bl = glm::vec2(pos.x, pos.z) + glm::vec2(-1, -1) * (FIELD_RANGE / 2);
	auto tr = glm::vec2(pos.x, pos.z) + glm::vec2(1, 1) * (FIELD_RANGE / 2);

	auto hits = PhysicsManager::instance()->areaCheck(nullptr, checkFor, new Vector2D(bl), new Vector2D(tr));
	bool hitCat = hits.size() > 0;

	if (!_collidedCat && hitCat)
	{
		std::cout << "coil hit cat" << std::endl;
		_collidedCat = hits[0]->GetEntity()->GetComponent<PlayerComponent>();
		_catSpeed = _collidedCat->GetSpeed();
		_collidedCat->SetSpeed(_catSpeed * SLOW_MULTIPLIER);
	}
	else if (_collidedCat && !hitCat)
	{
		_collidedCat->SetSpeed(_catSpeed);
		_collidedCat = nullptr;
	}
}