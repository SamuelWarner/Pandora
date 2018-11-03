#include "pch.h"
#include "Factory.h"
#include "LevelManager.h"

using namespace tinyxml2;

	Health* HealthFactory::createInstance(const XMLElement& element) {
		float hp, maxHP;
		tinyxml2::XMLError eResult = element.QueryFloatAttribute("hp", &hp);
		assert(eResult == tinyxml2::XML_SUCCESS);
		eResult = element.QueryFloatAttribute("maxHP", &maxHP);
		assert(eResult == tinyxml2::XML_SUCCESS);

		Health* output = new Health(hp, maxHP);
		lm->lifeSys->addComponent(output);

		return output;
	
	}

	Position* PositionFactory::createInstance(const XMLElement& element) {
		float xx, yy;
		tinyxml2::XMLError eResult = element.QueryFloatAttribute("x", &xx);
		assert(eResult == tinyxml2::XML_SUCCESS);
		eResult = element.QueryFloatAttribute("y", &yy);
		assert(eResult == tinyxml2::XML_SUCCESS);
		return new Position(xx, yy);
	}

	Sprite* SpriteFactory::createInstance(const XMLElement& element) {
		std::string str = element.Attribute("filePath");
		return new Sprite(element.Attribute("filePath"));
	}

	Renderer* RendererFactory::createInstance(const XMLElement& element) {
		Renderer* output = new Renderer();
		lm->renderSys->addComponent(output);
		return output;
	}

	Velocity* VelocityFactory::createInstance(const XMLElement& element) {
		return new Velocity(2);
	}

	KeyboardControl* KeyboardControlFactory::createInstance(const XMLElement& element) {
		KeyboardControl* output = new KeyboardControl();
		lm->ctrlSys->addComponent(output);
		return output;
	}

	Collision* CollisionFactory::createInstance(const XMLElement& element) {
		float left, right, top, bottom, val;
		std::cout << "Building collider" << std::endl;
		tinyxml2::XMLError eResult = element.QueryFloatAttribute("offsetTop", &top);
		assert(eResult == tinyxml2::XML_SUCCESS);
		eResult = element.QueryFloatAttribute("offsetBottom", &bottom);
		assert(eResult == tinyxml2::XML_SUCCESS);
		eResult = element.QueryFloatAttribute("offsetLeft", &left);
		assert(eResult == tinyxml2::XML_SUCCESS);
		eResult = element.QueryFloatAttribute("offsetRight", &right);
		assert(eResult == tinyxml2::XML_SUCCESS);
		eResult = element.QueryFloatAttribute("trigger", &val);
		assert(eResult == tinyxml2::XML_SUCCESS);

		Collision* output = new Collision(left, right, top, bottom, val);

		
		for (const XMLElement *effectSpec = element.FirstChildElement(); effectSpec != NULL; effectSpec = effectSpec->NextSiblingElement()) {
			eResult = effectSpec->QueryFloatAttribute("value", &val);
			assert(eResult == tinyxml2::XML_SUCCESS);
			output->effects->push_back(std::pair<std::string, float>(effectSpec->Value(), val));
		}
		
		lm->collisionSys->addComponent(output);
		return output;
	}