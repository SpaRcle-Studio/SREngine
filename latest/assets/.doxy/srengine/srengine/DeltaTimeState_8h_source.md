

# File DeltaTimeState.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**inc**](dir_384e30eefdcc60ad4aa259e47cd19ad6.md) **>** [**Engine**](dir_92c4f4d9e201e1e90834671676ddd6c7.md) **>** [**States**](dir_47b13ed3d798ea68f4d2bbbaf5b643b1.md) **>** [**DeltaTimeState.h**](DeltaTimeState_8h.md)

[Go to the documentation of this file](DeltaTimeState_8h.md)


```C++
//
// Created by Monika on 13.04.2024.
//

#ifndef SR_ENGINE_CORE_DELTA_TIME_STATE_H
#define SR_ENGINE_CORE_DELTA_TIME_STATE_H

#include <Utils/TaskManager/ThreadWorker.h>
#include <Utils/Types/Time.h>

namespace SR_CORE_NS {
    class DeltaTimeState : public SR_UTILS_NS::ThreadWorkerStateBase {
        SR_REGISTER_THREAD_STATE(DeltaTimeState)
        using Super = SR_UTILS_NS::ThreadWorkerStateBase;
    public:
        SR_UTILS_NS::ThreadWorkerResult ExecuteImpl() override;

    private:
        std::optional<SR_UTILS_NS::TimePointType> m_timeStart;

    };
}

#endif //SR_ENGINE_CORE_DELTA_TIME_STATE_H
```


