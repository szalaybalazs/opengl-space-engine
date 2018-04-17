#include "Planet.h"
#include "Entity.h"

Planet::Planet(Mesh model, Texture2D texture, ShaderProgram shader, int id, vector<Planet> subOrbits) :Entity(model, texture, shader, id) {
	this->subOrbits = subOrbits;
}

void Planet::rotate(double deltaTime) {
	int rotY = this->getRotation().y + 0.1f;
	rotation += rotationSpeed * deltaTime;
	this->setRotation(0, rotation, 0);
}

void Planet::orbit(double deltaTime) {
	float posY = orbitCenter.y;
	float posZ = (sinf(radians((float)orbitRotation)) * distanceFromCenter) + orbitCenter.z;
	float posX = (cosf(radians((float)orbitRotation)) * distanceFromCenter) + orbitCenter.x;

	float ovalZ = sinf(radians(orbitRotation + distortionAngle));
	float ovalX = sin(radians(orbitRotation + distortionAngle));

	orbitRotation = orbitRotation + (orbitalSpeed * deltaTime);

	this->setPosition(glm::vec3(posX + ovalX * distortion, posY, posZ + ovalZ * distortion));
	glm::vec3 currentPos = this->getPosition();

	for (int k = 0; k < subOrbits.size(); k++) {
		Planet orbit = subOrbits[k];
		orbit.setOrbitalCenter(currentPos);
		orbit.rotate(deltaTime);
		orbit.orbit(deltaTime);

		subOrbits[k] = orbit;
	};

}

void Planet::addSubOrbit(Planet orbit) {
	subOrbits.push_back(orbit);
}

void Planet::setDistortionAngle(float angle) {
	distortionAngle = angle;
}

void Planet::setPlanetAttributes(
	const string name,
	float planetRotation,
	float orbitalRotation,
	float planetRotationSpeed,
	float orbitalRotationSpeed,
	glm::vec3 orbitalCenter,
	float distanceFromCenter,
	float distortion) 
{
	this->setName(name);
	this->setPlanetRotation(planetRotation);
	this->setOrbitalRotation(orbitalRotation);
	this->setRotationSpeed(planetRotationSpeed);
	this->setOrbitalRotationSpeed(orbitalRotationSpeed);
	this->setOrbitalCenter(orbitalCenter);
	this->setDistanceFromCenter(distanceFromCenter);
	this->setDistortion(distortion);
}
void Planet::setName(const string name){
	this->name = name;
}
void Planet::setPlanetRotation(float rotation) {
	this->rotation = rotation;
}
void Planet::setOrbitalRotation(float orbitalRotation) {
	this->orbitRotation = orbitalRotation;
}
void Planet::setOrbitalCenter(glm::vec3 centerPosition) {
	this->orbitCenter = centerPosition;
}
void Planet::setDistanceFromCenter(float distanceFromCenter) {
	this->distanceFromCenter = distanceFromCenter;
}
void Planet::setRotationSpeed(float rotationSpeed) {
	this->rotationSpeed = rotationSpeed;
}
void Planet::setOrbitalRotationSpeed(float orbitalRotationSpeed) {
	this->orbitalSpeed = orbitalRotationSpeed;
}
void Planet::setDistortion(float distortion) {
	this->distortion = distortion;
}

string Planet::getName() {
	return name;
}

void Planet::planetRender() {
	this->render();
	for (Planet subOrbit : subOrbits) {
		subOrbit.render();
	}
}

void Planet::planetPickingRender() {
	this->pickingRender();
	for (Planet subOrbit : subOrbits) {
		subOrbit.pickingRender();
	}
}