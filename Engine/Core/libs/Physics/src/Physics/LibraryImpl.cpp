//
// Created by Monika on 22.11.2022.
//

#include <Physics/LibraryImpl.h>

namespace SR_PHYSICS_NS {
    LibraryImpl::LibraryImpl()
        : Super()
    { }

    bool LibraryImpl::Initialize() {
        SRHalt("LibraryImpl::Initialize() : called initialization method in basic class!");
        return false;
    }
}