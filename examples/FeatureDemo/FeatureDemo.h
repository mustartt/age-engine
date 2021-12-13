//
// Created by henry on 2021-12-12.
//

#ifndef FINAL_PROJECT_EXAMPLES_FEATUREDEMO_FEATUREDEMO_H_
#define FINAL_PROJECT_EXAMPLES_FEATUREDEMO_FEATUREDEMO_H_

#include <entry/EntryPoint.h>
#include <renderer/RenderComponents/AsciiRenderProp.h>

namespace FeatureDemo {

using namespace AGE;
class FeatureDemo : public CursesApplicationContext {
    using ResourceManager = std::unordered_map<std::string, std::unique_ptr<Renderer::AsciiRenderProp>>;
    ResourceManager resources;
  public:
    FeatureDemo() : AGE::CursesApplicationContext(80, 25) {}
    ~FeatureDemo() override = default;
    void init() override;
    void stop() override;
};

}

#endif //FINAL_PROJECT_EXAMPLES_FEATUREDEMO_FEATUREDEMO_H_
