

# File StopState.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**inc**](dir_9bceefd1de4616d8c4c29c5c810ccf2f.md) **>** [**Core**](dir_69060d94e27077a49c91b4da0482ce5e.md) **>** [**States**](dir_f0262115118909cf3466cd1f262a40c2.md) **>** [**StopState.h**](StopState_8h.md)

[Go to the documentation of this file](StopState_8h.md)


```C++
//
// Created by Monika on 13.04.2024.
//

#ifndef SR_ENGINE_CORE_STOP_STATE_H
#define SR_ENGINE_CORE_STOP_STATE_H

#include <Utils/TaskManager/ThreadWorker.h>

namespace SR_CORE_NS {
    class StopState : public SR_UTILS_NS::ThreadWorkerStateBase {
        SR_REGISTER_THREAD_STATE(StopState)
        using Super = SR_UTILS_NS::ThreadWorkerStateBase;
    public:
        SR_UTILS_NS::ThreadWorkerResult ExecuteImpl() override;

    };
}

#endif //SR_ENGINE_CORE_STOP_STATE_H
```


