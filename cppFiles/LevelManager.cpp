#include "pch.h"
#include "LevelManager.h"
#include <string>

using namespace tinyxml2;

LevelManager::LevelManager() {
	factories["Health"] = new HealthFactory(this);
	factories["Position"] = new PositionFactory();
	factories["Sprite"] = new SpriteFactory();
	factories["Renderer"] = new RendererFactory(this);
	factories["KeyboardControl"] = new KeyboardControlFactory(this);
	factories["Velocity"] = new VelocityFactory();
	factories["Collision"] = new CollisionFactory(this);
	ctrlSys = new ControlSystem();
	renderSys = new RenderSystem();
	collisionSys = new CollisionSystem();
	lifeSys = new LifeSystem();
}

LevelManager::~LevelManager() {
	delete factories["Health"];
	delete factories["Position"];
	delete factories["Sprite"];
	delete factories["Renderer"];
	delete factories["KeyboardControl"];
	delete factories["Velocity"];
	delete factories["Collision"];
	delete ctrlSys;
	delete renderSys;
	delete collisionSys;
	delete lifeSys;
}

void LevelManager::loadLevel(int level) {
	//load file and error check
	XMLError result = doc.LoadFile("Data/Levels.xml");
	assert(result == XML_SUCCESS);

	//setup root node access to the xml tree
	XMLElement *lvl = doc.FirstChildElement()->FirstChildElement();
	assert(lvl != NULL);

	//Loop through level rooms
	for (XMLElement *room = lvl->FirstChildElement(); room != NULL; room = room->NextSiblingElement()) {
		assert(room != NULL);

		//Loop through entities in room
		for (XMLElement *entity = room->FirstChildElement(); entity != NULL; entity = entity->NextSiblingElement()) {
			assert(entity != NULL);
			//create entity and store it in the room vector it should be in
			GameEntity *ge = createEntity(entity);
			allEntities.push_back(ge);
		}
	}
}

GameEntity* LevelManager::createEntity(tinyxml2::XMLElement *elem) {
	assert(elem != NULL);
	GameEntity * output = new GameEntity(this);
	for (XMLElement *elComp = elem->FirstChildElement(); elComp != NULL; elComp = elComp->NextSiblingElement()) {
		//DEBUG  std::cout << "creating component: " << comp->Value() << std::endl;
		Component* c = factories[elComp->Value()]->createInstance(elComp);
		c->parent = output;
		output->addComponent(c);
	}
	return output;
}

bool LevelManager::removeEntity(GameEntity* entity) {
	std::vector<GameEntity*>::iterator it;
	for (it = allEntities.begin(); it != allEntities.end(); it++) {
		if ((*it)->UID == entity->UID) {
			it = allEntities.erase(it);
			return true;
		}
	}
	return false;
}