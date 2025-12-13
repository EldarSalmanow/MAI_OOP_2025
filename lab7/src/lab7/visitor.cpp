#include <lab7/game.h>
#include <lab7/visitor.h>


Visitor::~Visitor() = default;

Battle::Battle(Game &game)
        : _game(game),
          _target(nullptr) {}

auto Battle::SetTarget(const NPCPtr &target) -> void {
    _target = std::move(target);
}

auto Battle::Visit(Druid *druid) -> void {
    (void) druid;
}

auto Battle::Visit(Squirrel *squirrel) -> void {
    bool can_attack = false;

    switch (_target->GetType()) {
        case NPCType::Werewolf:
        case NPCType::Druid:
            can_attack = true;

            break;
        default:
            break;
    }

    if (!can_attack) {
        return;
    }

    _target->Kill();
    _game.NotifyKill(*squirrel, *_target);
}

auto Battle::Visit(Werewolf *werewolf) -> void {
    bool can_attack = false;

    switch (_target->GetType()) {
        case NPCType::Druid:
            can_attack = true;

            break;
        default:
            break;
    }

    if (!can_attack) {
        return;
    }

    _target->Kill();
    _game.NotifyKill(*werewolf, *_target);
}
