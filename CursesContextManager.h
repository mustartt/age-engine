
#ifndef FINAL_PROJECT__CURSESCONTEXTMANAGER_H_
#define FINAL_PROJECT__CURSESCONTEXTMANAGER_H_

#include <memory>
#include "CursesRenderer.h"

class CursesContextManager {
    std::unique_ptr<CursesRenderer> renderer;
  public:
    explicit CursesContextManager(std::unique_ptr<CursesRenderer> renderer);
    ~CursesContextManager();
};

#endif //FINAL_PROJECT__CURSESCONTEXTMANAGER_H_
