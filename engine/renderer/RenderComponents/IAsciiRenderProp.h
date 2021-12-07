//
// Created by henry on 2021-12-01.
//

#ifndef FINAL_PROJECT_ENGINE_RENDERER_RENDERCOMPONENTS_IASCIIRENDERPROP_H_
#define FINAL_PROJECT_ENGINE_RENDERER_RENDERCOMPONENTS_IASCIIRENDERPROP_H_

namespace AGE::Renderer {

class IAsciiRenderProp {
  public:
    virtual void render(AsciiRenderer *renderer, int xOffset, int yOffset) = 0;
};

}

#endif //FINAL_PROJECT_ENGINE_RENDERER_RENDERCOMPONENTS_IASCIIRENDERPROP_H_
