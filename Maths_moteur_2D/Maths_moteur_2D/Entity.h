#pragma once
#include "rigidbody.h"

class Entity :
    public Rigidbody
{
    inline static std::vector<Entity*> allEntities;
    float totalMaxAcc;  // L'accélération maximale produite par l'Entity
    Rigidbody* target = nullptr;  // le rigidbody suivi par l'Entity

public:
    Entity(std::vector<float> initialPositionWorld);  // Constructeur le plus petit
    Entity(std::vector<float> initialPositionWorld, Rigidbody*);  // Ce constructeur donne immédiatement une cible à l'entité

    void followTarget();  // Fonction pour ajuster l'accélération, afin de s'approcher de la cible

    // Getters et setters
    static std::vector<Entity*> getAllEntities() { return allEntities; }

    void setTarget(Rigidbody* targetBody) { target = targetBody; }
    Rigidbody* getTarget() const { return target; }

    void setTotatMaxAcc(float acc) { totalMaxAcc = acc; }
    float getTotalMaxAcc() const { return totalMaxAcc; }
};

