//
// Created by henry on 2021-12-13.
//

#include <memory>
#include <entry/EntryPoint.h>
#include <FeatureDemo.h>

// resolve entry point extern
std::unique_ptr<AGE::ApplicationContext> gameEntryPoint(int argc, char *argv[]) {
    return std::make_unique<FeatureDemo::FeatureDemo>();
}

