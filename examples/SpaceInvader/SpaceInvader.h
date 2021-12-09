//
// Created by henry on 2021-12-08.
//

#ifndef FINAL_PROJECT_EXAMPLES_SPACEINVADER_SPACEINVADER_H_
#define FINAL_PROJECT_EXAMPLES_SPACEINVADER_SPACEINVADER_H_

#include <entry/EntryPoint.h>
#include <renderer/RenderComponents/AsciiRenderProp.h>

namespace SpaceInvader {

using namespace AGE;
class SpaceInvader : public CursesApplicationContext {
    using ResourceManager = std::unordered_map<std::string, std::unique_ptr<Renderer::AsciiRenderProp>>;
    ResourceManager resources;
  public:
    SpaceInvader() : AGE::CursesApplicationContext(80, 25) {}
    ~SpaceInvader() override = default;
    void init() override;
    void stop() override;
};

}

#endif //FINAL_PROJECT_EXAMPLES_SPACEINVADER_SPACEINVADER_H_
