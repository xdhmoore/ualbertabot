#pragma once

#include "Common.h"
#include "MicroManager.h"
#include "InformationManager.h"
#include "Scout.h"

namespace UAlbertaBot
{
class ScoutManager 
{
	std::vector<Scout> *			_scouts;
	unsigned int					_numScouts;

	ScoutManager();

	bool							scoutsFull();
	void							removeRandomScout();
	void							addNewScout(BWAPI::Unit);
	
public:
	
    static ScoutManager & Instance();

	~ScoutManager();

	void update();
	
    void setWorkerScout(BWAPI::Unit unit);

	void onSendText(std::string text);
	void onUnitShow(BWAPI::Unit unit);
	void onUnitHide(BWAPI::Unit unit);
	void onUnitCreate(BWAPI::Unit unit);
	void onUnitRenegade(BWAPI::Unit unit);
	void onUnitDestroy(BWAPI::Unit unit);
	void onUnitMorph(BWAPI::Unit unit);
};
}