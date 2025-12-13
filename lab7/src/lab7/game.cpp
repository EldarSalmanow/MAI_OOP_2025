#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>

#include <lab7/constants.h>
#include <lab7/game.h>
#include <lab7/utils.h>
#include <lab7/visitor.h>


Game::Game(NPCFactoryPtr factory)
        : _npcFactory(std::move(factory)),
          _running(false) {}

Game::~Game() {
    _running = false;

    if (_movementThread.joinable()) {
        _movementThread.join();
    }

    if (_battleThread.joinable()) {
        _battleThread.join();
    }

    if (_printThread.joinable()) {
        _printThread.join();
    }
}

auto Game::StartGame() -> int32_t {
    if (_running) {
        return 1;
    }

    for (int32_t i = 0; i < static_cast<std::int32_t>(kNPCCount); ++i) {
        NPCPtr npc = _npcFactory->RandomNPC();

        if (AppendNPC(npc) != 0) {
            --i;
        }
    }

    _running = true;
    _movementThread = std::thread([this] () {
        MovementThread();
    });
    _battleThread = std::thread([this] () {
        BattleThread();
    });
    _printThread = std::thread([this] () {
        PrintMapThread();
    });

    std::this_thread::sleep_for(std::chrono::seconds(kGameDurationSeconds));
    _running = false;

    _movementThread.join();
    _battleThread.join();
    _printThread.join();

    DumpObjects(std::cout);
    std::cout << "Alive: " << _npcs.size() << std::endl;

    return 0;
}

auto Game::AddNPC(NPCType type,
                  Point point,
                  const std::string &name) -> int32_t {
    auto npc = _npcFactory->CreateNPC(type,
                                             point,
                                             name);

    if (!npc) {
        return 1;
    }

    return AppendNPC(npc);
}

auto Game::SaveObjects(const std::string &filename) const -> int32_t {
    std::ofstream file(filename);

    if (!file.is_open()) {
        return 1;
    }

    DumpObjects(file);

    file.close();

    return 0;
}

auto Game::LoadObjects(const std::string &filename) -> int32_t {
    std::ifstream file(filename);

    if (!file.is_open()) {
        return 1;
    }

    while (auto npc = _npcFactory->LoadNPC(file)) {
        if (AppendNPC(npc)) {
            break;
        }
    }

    file.close();

    return 0;
}

auto Game::DumpObjects(std::ostream &ostream) const -> void {
    std::lock_guard lock(_npcsMutex);

    for (const auto &npc : _npcs) {
        std::ostringstream string_stream;

        auto type = npc->GetType();
        const auto &name = npc->GetName();
        auto point = npc->GetPoint();

        string_stream << "[" << NPCTypeToString(type) << "] "
                      << name << " [" << point.GetX() << "," << point.GetY() << "]" << std::endl;

        ostream << string_stream.str();
    }
}

auto Game::AddObserver(const ObserverPtr &observer) -> void {
    _observers.emplace_back(observer);
}

auto Game::NotifyKill(const NPC &killer,
                      const NPC &killed) -> void {
    for (auto &observer : _observers) {
        observer->OnKill(killer,
                         killed);
    }
}

auto Game::AppendNPC(const NPCPtr &npc) -> int32_t {
    if (std::ranges::find_if(_npcs,
                             [npc](const NPCPtr &tmp) -> bool {
                                 return tmp->GetName() == npc->GetName();
                             }) != _npcs.end()) {
        return 1;
    }

    _npcs.emplace_back(npc);

    return 0;
}

auto Game::MovementThread() -> void {
    while (_running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        std::lock_guard lock(_npcsMutex);

        for (auto &npc : _npcs) {
            if (npc->GetKilled()) {
                continue;
            }

            npc->Move(kMapSize);

            double kill_distance = npc->GetKillDistance();
            std::vector<NPCPtr> targets;

            for (const auto &other : _npcs) {
                if (other != npc && !other->GetKilled() && !npc->GetKilled()) {
                    if (npc->CanAttack(*other, static_cast<double>(kill_distance))) {
                        targets.push_back(other);
                    }
                }
            }

            {
                std::lock_guard queue_lock(_battleQueueMutex);

                for (const auto &target : targets) {
                    _battleQueue.emplace(npc, target);
                }
            }
        }
    }
}

auto Game::BattleThread() -> void {
    while (_running || !_battleQueue.empty()) {
        std::pair<NPCPtr, NPCPtr> battle;

        {
            std::lock_guard lock(_battleQueueMutex);

            if (_battleQueue.empty()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));

                continue;
            }

            battle = _battleQueue.front();
            _battleQueue.pop();
        }

        auto attacker = battle.first;
        auto defender = battle.second;

        Battle battle_visitor(*this);
        battle_visitor.SetTarget(defender);

        if (!attacker->CanAttack(*defender, attacker->GetKillDistance())) {
            continue;
        }

        auto attack_power = RandomInRange(1, 6);
        auto defense_power = RandomInRange(1, 6);

        if (attack_power <= defense_power) {
            continue;
        }

        {
            std::lock_guard lock(_npcsMutex);

            attacker->Accept(&battle_visitor);

            if (defender->GetKilled()) {
                std::erase(_npcs, defender);
            }
        }
    }
}

auto Game::PrintMapThread() -> void {
    while (_running) {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        PrintMap();
    }
}

auto Game::PrintMap() -> void {
    std::lock_guard coutLock(_coutMutex);

    std::cout << "\n=============== Карта ===============\n";

    std::vector map(kMapSize, std::vector(kMapSize, '.'));

    {
        std::lock_guard lock(_npcsMutex);

        for (const auto &npc : _npcs) {
            if (!npc->GetKilled()) {
                auto point = npc->GetPoint();
                char symbol = '?';

                switch (npc->GetType()) {
                    case NPCType::Squirrel:
                        symbol = 'S';
                        break;
                    case NPCType::Druid:
                        symbol = 'D';

                        break;
                    case NPCType::Werewolf:
                        symbol = 'W';

                        break;
                }

                if (point.GetX() < kMapSize && point.GetY() < kMapSize) {
                    map[point.GetY()][point.GetX()] = symbol;
                }
            }
        }
    }

    for (std::uint64_t y = 0; y < kMapSize; ++y) {
        for (std::uint64_t x = 0; x < kMapSize; ++x) {
            std::cout << map[y][x];
        }

        std::cout << '\n';
    }

    std::cout << std::flush;
}
