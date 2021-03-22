
set(LINEARMATH_SRC
        ${BULLET3_ROOT_DIR}/LinearMath/TaskScheduler/btTaskScheduler.cpp
        ${BULLET3_ROOT_DIR}/LinearMath/TaskScheduler/btThreadSupportPosix.cpp
        ${BULLET3_ROOT_DIR}/LinearMath/TaskScheduler/btThreadSupportWin32.cpp

        ${BULLET3_ROOT_DIR}/LinearMath/btAlignedAllocator.cpp
        ${BULLET3_ROOT_DIR}/LinearMath/btQuickprof.cpp
        ${BULLET3_ROOT_DIR}/LinearMath/btConvexHull.cpp
        ${BULLET3_ROOT_DIR}/LinearMath/btReducedVector.cpp
        ${BULLET3_ROOT_DIR}/LinearMath/btConvexHullComputer.cpp
        ${BULLET3_ROOT_DIR}/LinearMath/btPolarDecomposition.cpp
        ${BULLET3_ROOT_DIR}/LinearMath/btSerializer.cpp
        ${BULLET3_ROOT_DIR}/LinearMath/btGeometryUtil.cpp
        ${BULLET3_ROOT_DIR}/LinearMath/btSerializer64.cpp
        ${BULLET3_ROOT_DIR}/LinearMath/btThreads.cpp
        ${BULLET3_ROOT_DIR}/LinearMath/btVector3.cpp
        )

set(LINEARMATH_INC_PUBLIC
        ${BULLET3_ROOT_DIR}
        )

set(LINEARMATH_INC_PRIVATE

        )

set(LINEARMATH_INC_INSTANCE

        )
