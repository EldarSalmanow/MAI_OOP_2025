#ifndef MAI_OOP_2025_NPC_H
#define MAI_OOP_2025_NPC_H

#include <memory>
#include <string>

#include <lab7/point.h>


enum class NPCType {
    Squirrel,
    Werewolf,
    Druid
};

auto NPCTypeToString(NPCType type) -> std::string_view;

auto StringToNPCType(const std::string &string) -> NPCType;

class Visitor;

class NPC;
using NPCPtr = std::shared_ptr<NPC>;

class NPC {
public:

    NPC(Point point,
        std::string name);

public:

    virtual ~NPC();

public:

    auto Kill() -> void;

    auto CanAttack(const NPC &defender,
                   double distance) const -> bool;

public:

    auto GetPoint() const -> const Point &;

    auto GetName() const -> const std::string &;

    auto GetKilled() const -> bool;

    auto Move(std::uint64_t map_size) -> void;

public:

    virtual auto Accept(Visitor *visitor) -> void = 0;

    virtual auto GetType() const -> NPCType = 0;

    virtual auto GetMoveDistance() const -> double = 0;

    virtual auto GetKillDistance() const -> double = 0;

private:

    Point _point;

    std::string _name;

    bool _killed;
};

class Druid final : public NPC {
public:

    Druid(Point point,
          std::string name);

public:

    auto Accept(Visitor *visitor) -> void override;

    auto GetType() const -> NPCType override;

    auto GetMoveDistance() const -> double override;

    auto GetKillDistance() const -> double override;
};

class Squirrel final : public NPC {
public:

    Squirrel(Point point,
             std::string name);

public:

    auto Accept(Visitor *visitor) -> void override;

    auto GetType() const -> NPCType override;

    auto GetMoveDistance() const -> double override;

    auto GetKillDistance() const -> double override;
};

class Werewolf final : public NPC {
public:

    Werewolf(Point point,
             std::string name);

public:

    auto Accept(Visitor *visitor) -> void override;

    auto GetType() const -> NPCType override;

    auto GetMoveDistance() const -> double override;

    auto GetKillDistance() const -> double override;
};

class NPCFactory {
public:

    virtual ~NPCFactory();

public:

    auto LoadNPC(std::istream &istream) const -> NPCPtr;

public:

    auto CreateNPC(NPCType type,
                   Point point,
                   const std::string &name) const -> NPCPtr;

    auto RandomNPC() const -> NPCPtr;
};

using NPCFactoryPtr = std::shared_ptr<NPCFactory>;

#endif //MAI_OOP_2025_NPC_H
