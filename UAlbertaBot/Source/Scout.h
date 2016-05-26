#pragma once

#include <memory>
#include "Common.h"

namespace UAlbertaBot
{
class Scout
{
	BWAPI::Unit						_workerScout;
	std::string                     _scoutStatus;
	std::string                     _gasStealStatus;
	bool			                _scoutUnderAttack;
	bool                            _didGasSteal;
	bool                            _gasStealFinished;
	int                             _currentRegionVertexIndex;
	int                             _previousScoutHP;
	std::shared_ptr<std::vector<BWAPI::Position>>	_targetRegionVertices;
	
	bool                            enemyWorkerInRadius();
	bool			                immediateThreat();
	void                            gasSteal();
	int                             getClosestVertexIndex(BWAPI::Unit unit);
	BWAPI::Position                 getFleePosition();
	BWAPI::Unit						getEnemyGeyser();
	BWAPI::Unit						closestEnemyWorker();
	void                            followPerimeter();

	public:

		void calculateTargetRegionVertices(BWTA::BaseLocation*);

		Scout(BWAPI::Unit);
		~Scout();
		void update();

		void setWorkerScout(BWAPI::Unit unit);

		void                            moveScouts();
		void                            drawScoutInformation(int x, int y);

		BWAPI::Unit						getWorkerScout();
		bool							isValid();

		void onSendText(std::string text);
		void onUnitShow(BWAPI::Unit unit);
		void onUnitHide(BWAPI::Unit unit);
		void onUnitCreate(BWAPI::Unit unit);
		void onUnitRenegade(BWAPI::Unit unit);
		void onUnitDestroy(BWAPI::Unit unit);
		void onUnitMorph(BWAPI::Unit unit);
	};
}

