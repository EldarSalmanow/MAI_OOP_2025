#include <algorithm>
#include <cmath>
#include <sstream>
#include <random>

#include <lab7/constants.h>
#include <lab7/npc.h>
#include <lab7/utils.h>
#include <lab7/visitor.h>


auto NPCTypeToString(NPCType type) -> std::string_view {
    switch (type) {
        case NPCType::Squirrel:
            return "Squirrel";
        case NPCType::Werewolf:
            return "Werewolf";
        case NPCType::Druid:
            return "Druid";
    }

    return "<unknown>";
}

auto StringToNPCType(const std::string &string) -> NPCType {
    if (string == "Druid") {
        return NPCType::Druid;
    }
    else if (string == "Squirrel") {
        return NPCType::Squirrel;
    }
    else if (string == "Werewolf") {
        return NPCType::Werewolf;
    }

    throw std::runtime_error("[ERROR] Unknown type!");
}

NPC::NPC(Point point,
         std::string name)
    : _point(point),
      _name(std::move(name)),
      _killed(false) {}

NPC::~NPC() = default;

auto NPC::Kill() -> void {
    _killed = true;
}

auto NPC::CanAttack(const NPC &defender,
                    double distance) const -> bool {
    const double EPSILON = 1e-9;

    if (this == &defender) {
        return false;
    }

    if (GetKilled() || defender.GetKilled()) {
        return false;
    }

    auto x       = _point.GetX(), y                = _point.GetY();
    auto x_other = defender.GetPoint().GetX(), y_other    = defender.GetPoint().GetY();
    auto dist_x = x - x_other, dist_y = y - y_other;

    return (distance - std::sqrt(dist_x * dist_x + dist_y * dist_y)) > EPSILON;
}

auto NPC::GetPoint() const -> const Point & {
    return _point;
}

auto NPC::GetName() const -> const std::string & {
    return _name;
}

auto NPC::GetKilled() const -> bool {
    return _killed;
}

auto NPC::Move(std::uint64_t map_size) -> void {
    if (_killed) {
        return;
    }

    double move_distance = GetMoveDistance();
    auto x_distance = RandomInRange(-1, 1) * static_cast<int>(move_distance);
    auto y_distance = RandomInRange(-1, 1) * static_cast<int>(move_distance);

    std::int64_t new_x = static_cast<std::int64_t>(_point.GetX()) + x_distance;
    std::int64_t new_y = static_cast<std::int64_t>(_point.GetY()) + y_distance;

    new_x = std::max(0L, std::min(new_x, static_cast<std::int64_t>(map_size - 1)));
    new_y = std::max(0L, std::min(new_y, static_cast<std::int64_t>(map_size - 1)));

    _point.SetX(static_cast<std::uint64_t>(new_x));
    _point.SetY(static_cast<std::uint64_t>(new_y));
}

Druid::Druid(Point point,
             std::string name)
        : NPC(std::move(point),
              std::move(name)) {}

auto Druid::Accept(Visitor *visitor) -> void {
    return visitor->Visit(this);
}

auto Druid::GetType() const -> NPCType {
    return NPCType::Druid;
}

auto Druid::GetMoveDistance() const -> double {
    return 10;
}

auto Druid::GetKillDistance() const -> double {
    return 10;
}

Squirrel::Squirrel(Point point,
                   std::string name)
        : NPC(point,
              std::move(name)) {}

auto Squirrel::Accept(Visitor *visitor) -> void {
    return visitor->Visit(this);
}

auto Squirrel::GetType() const -> NPCType {
    return NPCType::Squirrel;
}

auto Squirrel::GetMoveDistance() const -> double {
    return 5;
}

auto Squirrel::GetKillDistance() const -> double {
    return 5;
}

Werewolf::Werewolf(Point point,
                   std::string name)
        : NPC(point,
              std::move(name)) {}

auto Werewolf::Accept(Visitor *visitor) -> void {
    return visitor->Visit(this);
}

auto Werewolf::GetType() const -> NPCType {
    return NPCType::Werewolf;
}

auto Werewolf::GetMoveDistance() const -> double {
    return 40;
}

auto Werewolf::GetKillDistance() const -> double {
    return 5;
}

NPCFactory::~NPCFactory() = default;

auto NPCFactory::LoadNPC(std::istream &istream) const -> NPCPtr {
    std::string line;

    std::getline(istream, line);

    if (istream.eof()) {
        return nullptr;
    }

    std::istringstream string_stream(line);

    std::string str_type, name, str_point;
    string_stream >> str_type >> name >> str_point;

    NPCType type  = StringToNPCType(str_type.substr(1, str_type.size() - 2));
    std::string x = str_point.substr(1, str_point.find(','));
    std::string y = str_point.substr(str_point.find(',') + 1, str_point.size() - str_point.find(',') - 1);
    Point point(std::atoi(x.c_str()), std::atoi(y.c_str()));

    return CreateNPC(type, point, name);
}

auto NPCFactory::CreateNPC(NPCType type,
                           Point point,
                           const std::string &name) const -> NPCPtr {
    if (point.GetX() > 100 || point.GetY() > 100) {
        return nullptr;
    }

    switch (type) {
        case NPCType::Squirrel:
            return std::make_shared<Squirrel>(point,
                                              std::move(name));
        case NPCType::Werewolf:
            return std::make_shared<Werewolf>(point,
                                              std::move(name));
        case NPCType::Druid:
            return std::make_shared<Druid>(point,
                                           std::move(name));
    }

    throw std::runtime_error("[INTERNAL] Missed NPC type handling in NPCFactory::CreateNPC!");
}

auto NPCFactory::RandomNPC() const -> NPCPtr {
    static uint64_t id = 1;

    auto npc = CreateNPC(
        static_cast<NPCType>(RandomInRange(0, 2)),
        Point {
            static_cast<std::uint64_t>(RandomInRange(0, kMapSize - 1)),
            static_cast<std::uint64_t>(RandomInRange(0, kMapSize - 1))
        },
        "NPC_" + std::to_string(id));

    if (!npc) {
        return nullptr;
    }

    ++id;

    return npc;
}
