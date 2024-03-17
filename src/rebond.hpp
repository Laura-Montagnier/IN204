#pragma once
#include "defs.hpp"
#include "volumes.hpp"

Vecteur direction_difusee(const Vecteur &normale);
Vecteur direction_reflechie(const Vecteur &incident, const Vecteur &normale);
Vecteur direction_refractee(const Vecteur &incident, const Vecteur &normale);