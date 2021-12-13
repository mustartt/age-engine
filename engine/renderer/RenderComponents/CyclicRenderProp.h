//
// Created by henry on 2021-12-12.
//

#ifndef FINAL_PROJECT_ENGINE_RENDERER_RENDERCOMPONENTS_CYCLICRENDERPROP_H_
#define FINAL_PROJECT_ENGINE_RENDERER_RENDERCOMPONENTS_CYCLICRENDERPROP_H_

#include "AsciiRenderProp.h"

namespace AGE::Renderer {

class CyclicRenderProp : public AsciiRenderProp {
    std::vector<AsciiRenderProp *> forms;
    int index;
  public:
    explicit CyclicRenderProp(std::vector<AsciiRenderProp *> cycle) : forms(std::move(cycle)), index(0) {}
    void render(AsciiRenderer *renderer, int xOffset, int yOffset) override {
        forms[index]->render(renderer, xOffset, yOffset);
        incrementRenderForm();
    }
    void incrementRenderForm() {
        index = (index + 1) % (int)forms.size();
    }
};

}

#endif //FINAL_PROJECT_ENGINE_RENDERER_RENDERCOMPONENTS_CYCLICRENDERPROP_H_
