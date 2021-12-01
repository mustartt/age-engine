//
// Created by henry on 2021-12-01.
//

#ifndef FINAL_PROJECT_ENGINE_RENDERER_RENDERTARGET_H_
#define FINAL_PROJECT_ENGINE_RENDERER_RENDERTARGET_H_

#include "ScreenBuffer.h"

namespace AGE {
namespace Renderer {

class RenderTarget {
  public:
    virtual void render(ScreenBuffer &buffer) const = 0;
};

}
}

#endif //FINAL_PROJECT_ENGINE_RENDERER_RENDERTARGET_H_
