#include "ScoutManager.h"
#include "ProductionManager.h"
#include "UnitUtil.h"
#include <vector>
using namespace UAlbertaBot;

ScoutManager::ScoutManager() 

	//TODO consolidate with GameCommander
	:	_numScouts(10)
{
	_scouts = new std::vector<std::shared_ptr<Scout>>();
}

ScoutManager & ScoutManager::Instance() 
{
	static ScoutManager instance;
	return instance;
}

void ScoutManager::update()
{
    if (!Config::Modules::UsingScoutManager)
    {
        return;
    }

	removeDeadScouts();

	std::for_each(_scouts->begin(), _scouts->end(), [](std::shared_ptr<Scout> s){
		s->moveScouts();
		s->drawScoutInformation(200, 320);
	});

}

void ScoutManager::removeDeadScouts() {
	int i = 0;
	while (i < _scouts->size()) {
		if (!_scouts->at(i)->isValid()) {
			_scouts->erase(_scouts->begin() + i);
		}
		else {
			i++;
		}
	}
}

bool ScoutManager::scoutsFull() {
	return _scouts->size() >= _numScouts;
}

void ScoutManager::removeRandomScout() {

	int idxToErase = rand() % _scouts->size();
	auto scoutToRemove = _scouts->at(idxToErase);

	WorkerManager::Instance().finishedWithWorker(scoutToRemove->getWorkerScout());

	_scouts->erase(_scouts->begin() + idxToErase);
}

void ScoutManager::addNewScout(BWAPI::Unit unit) {
	_scouts->push_back(std::make_shared<Scout>(unit, getNextBaseToScout()));
	WorkerManager::Instance().setScoutWorker(unit);
}

BWTA::BaseLocation* ScoutManager::getNextBaseToScout() {

	BWTA::BaseLocation* nextBase;

	//decide whether we want to scout an occupied or unoccupied base with a 30/70 chance
	bool occupied = (rand() % 10 < 3);

	std::set<BWTA::BaseLocation*> allBaseLocations = BWTA::getBaseLocations();
	std::vector<BWTA::BaseLocation*> enemyOccupiedBases;
	std::vector<BWTA::BaseLocation*> unOccupiedBases;

	for (auto it = allBaseLocations.begin(); it != allBaseLocations.end(); it++) {
		if (InformationManager::Instance().isEnemyBuildingInRegion((*it)->getRegion())) {
			enemyOccupiedBases.push_back(*it);
		}
		else if(!InformationManager::Instance().isMyBuildingInRegion((*it)->getRegion())) {
			unOccupiedBases.push_back(*it);
		}
	}

	if (occupied) {
		return enemyOccupiedBases[rand() % enemyOccupiedBases.size()];
	}
	else {
		return unOccupiedBases[rand() % unOccupiedBases.size()];
	}
}

void ScoutManager::setWorkerScout(BWAPI::Unit unit)
{
    // if we have a previous worker scout, release it back to the worker manager
    if (scoutsFull())
    {
		removeRandomScout();
    }

	addNewScout(unit);
}

ScoutManager::~ScoutManager() {
	delete _scouts;
}

