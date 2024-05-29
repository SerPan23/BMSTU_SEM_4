#include "HistoryManager.h"

#include "ManagerSolution.h"

void HistoryManager::getPrevState(int objectId)
{
    auto memento = careTaker.getMemento(objectId);

    auto sceneManager = ManagerSolution::getSceneManager();
    auto obj = sceneManager->getObject(objectId);

    obj->restoreMemento(memento);
}

void HistoryManager::saveState(int objectId)
{
    auto sceneManager = ManagerSolution::getSceneManager();
    auto obj = sceneManager->getObject(objectId);

    auto data = CareTaker::saveData(obj, obj->createMemento());

    careTaker.setMemento(objectId, data);
}
