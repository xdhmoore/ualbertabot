#include "ScoutManager.h"
#include "ProductionManager.h"

using namespace UAlbertaBot;

ScoutManager::ScoutManager() 

	//TODO consolidate with GameCommander
	:	_numScouts(10)
{
	_scouts = new std::vector<Scout>();
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

	std::for_each(_scouts->begin(), _scouts->end(), [](Scout s){
		s.moveScouts();
		s.drawScoutInformation(200, 320);
	});

}

bool ScoutManager::scoutsFull() {
	return _scouts->size() >= _numScouts;
}

void ScoutManager::removeRandomScout() {

	int idxToErase = rand() % _scouts->size();
	Scout scoutToRemove = _scouts->at(idxToErase);

	WorkerManager::Instance().finishedWithWorker(scoutToRemove.getWorkerScout());

	_scouts->erase(_scouts->begin() + idxToErase);
}

void ScoutManager::addNewScout(BWAPI::Unit unit) {
	Scout scout(unit);
	_scouts->push_back(scout);
	WorkerManager::Instance().setScoutWorker(unit);
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

