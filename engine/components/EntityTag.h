//
// Created by henry on 2021-12-09.
//

#ifndef FINAL_PROJECT_ENGINE_COMPONENTS_ENTITYTAG_H_
#define FINAL_PROJECT_ENGINE_COMPONENTS_ENTITYTAG_H_

#include <string>

namespace AGE::Components {

class EntityTagComponent {
    std::string tag;
  public:
    explicit EntityTagComponent(std::string name = "unknown_tag");
    [[nodiscard]]
    const std::string &getTag() const;
};

}

#endif //FINAL_PROJECT_ENGINE_COMPONENTS_ENTITYTAG_H_
