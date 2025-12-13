#ifndef MAI_OOP_2025_GAME_H
#define MAI_OOP_2025_GAME_H

#include <atomic>
#include <chrono>
#include <mutex>
#include <queue>
#include <shared_mutex>
#include <thread>
#include <vector>

#include <lab7/npc.h>
#include <lab7/observer.h>


class Game final {
public:

    explicit Game(NPCFactoryPtr factory);

    ~Game();

public:

    auto StartGame() -> int32_t;

    auto AddNPC(NPCType type,
                Point point,
                const std::string &name) -> int32_t;

    auto SaveObjects(const std::string &filename) const -> int32_t;

    auto LoadObjects(const std::string &filename) -> int32_t;

    auto DumpObjects(std::ostream &ostream) const -> void;

    auto AddObserver(const ObserverPtr &observer) -> void;

    auto NotifyKill(const NPC &killer,
                    const NPC &killed) -> void;

private:

    auto AppendNPC(const NPCPtr &npc) -> int32_t;

    auto MovementThread() -> void;

    auto BattleThread() -> void;

    auto PrintMapThread() -> void;

    auto PrintMap() -> void;

private:

    std::vector<NPCPtr> _npcs;
    NPCFactoryPtr _npcFactory;
    std::vector<ObserverPtr> _observers;

    std::queue<std::pair<NPCPtr, NPCPtr>> _battleQueue;
    mutable std::mutex _npcsMutex;
    std::mutex _battleQueueMutex;
    std::mutex _coutMutex;
    std::atomic<bool> _running;

    std::thread _movementThread;
    std::thread _battleThread;
    std::thread _printThread;
};

#endif //MAI_OOP_2025_GAME_H
