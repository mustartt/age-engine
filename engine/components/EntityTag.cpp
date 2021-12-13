//
// Created by henry on 2021-12-09.
//

#include "EntityTag.h"

namespace AGE::Components {

EntityTagComponent::EntityTagComponent(std::string name) : tag(std::move(name)) {}
const std::string &EntityTagComponent::getTag() const { return tag; }

}
