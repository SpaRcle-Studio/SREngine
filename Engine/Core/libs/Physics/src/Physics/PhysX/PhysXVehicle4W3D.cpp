//
// Created by innerviewer on 2/28/2023.
//

#include <Physics/PhysX/PhysXVehicle4W3D.h>
#include <Physics/PhysX/PhysXMaterialImpl.h>
#include <Physics/PhysicsMaterial.h>

namespace SR_PTYPES_NS {
    PhysXVehicle4W3D::PhysXVehicle4W3D(Super::LibraryPtr pLibrary)
            : Super(pLibrary)
    { }

    PhysXVehicle4W3D::~PhysXVehicle4W3D() {
        if (m_wheelsSimData) {
            delete m_wheelsSimData;
            m_wheelsSimData = nullptr;
        }

        if (m_vehActor) {
            m_vehActor->release();
            m_vehActor = nullptr;
        }
    }

    physx::PxVehicleWheelsSimData* PhysXVehicle4W3D::SetupWheelsSimulationData() {
        physx::PxVehicleWheelsSimData* wheelsSimData = physx::PxVehicleWheelsSimData::allocate(4);

        //Set up the wheels.
        physx::PxVehicleWheelData wheels[4];
        {
            //Set up the wheel data structures with mass, moi, radius, width.
            for (auto& wheel : wheels)
            {
                wheel.mMass = GetWheelMass();
                wheel.mMOI = GetWheelMOI();
                wheel.mRadius = GetWheelRadius();
                wheel.mWidth = GetWheelWidth();
            }

            //Enable the handbrake for the rear wheels only.
            wheels[physx::PxVehicleDrive4WWheelOrder::eREAR_LEFT].mMaxHandBrakeTorque = GetMaxHandBrakeTorque();
            wheels[physx::PxVehicleDrive4WWheelOrder::eREAR_RIGHT].mMaxHandBrakeTorque = GetMaxHandBrakeTorque();
            //Enable steering for the front wheels only.
            wheels[physx::PxVehicleDrive4WWheelOrder::eFRONT_LEFT].mMaxSteer = SR_PI * GetMaxSteer();
            wheels[physx::PxVehicleDrive4WWheelOrder::eFRONT_RIGHT].mMaxSteer = SR_PI * GetMaxSteer();
        }

        //Set up the tires.
        physx::PxVehicleTireData tires[4];
        {
            //Set up the tires.
            for (auto & tire : tires)
            {
                tire.mType = 0; /// TODO: Заменить.
            }
        }

        physx::PxVec3 pxWheelCenterActorOffsets[4];
        physx::PxVec3 pxChassisCMOffset = SR_PHYSICS_UTILS_NS::FV3ToPxV3(GetChassisCMOffset());

        for (uint32_t i = 0; i < 4; i++) {
            pxWheelCenterActorOffsets[i] = SR_PHYSICS_UTILS_NS::FV3ToPxV3(GetWheelCAOffsets()[i]);
        }

        //Set up the suspensions
        physx::PxVehicleSuspensionData suspensions[4];
        {
            //Compute the mass supported by each suspension spring.
            float_t suspSprungMasses[4];
            physx::PxVehicleComputeSprungMasses(
                    4,
                    &pxWheelCenterActorOffsets[0],
                    pxChassisCMOffset,
                    GetChassisMass(),
                    1,
                    suspSprungMasses);


            //Set the suspension data.
            for (uint32_t i = 0; i < 4; i++)
            {
                suspensions[i].mMaxCompression = 0.3f;
                suspensions[i].mMaxDroop = 0.1f;
                suspensions[i].mSpringStrength = 35000.0f;
                suspensions[i].mSpringDamperRate = 4500.0f;
                suspensions[i].mSprungMass = suspSprungMasses[i];
            }

            //Set the camber angles.
            const float_t camberAngleAtRest = 0.0f;
            const float_t camberAngleAtMaxDroop = 0.01f;
            const float_t camberAngleAtMaxCompression = -0.01f;
            for (uint32_t i = 0; i < 4; i += 2)
            {
                suspensions[i + 0].mCamberAtRest =  camberAngleAtRest;
                suspensions[i + 1].mCamberAtRest =  -camberAngleAtRest;
                suspensions[i + 0].mCamberAtMaxDroop = camberAngleAtMaxDroop;
                suspensions[i + 1].mCamberAtMaxDroop = -camberAngleAtMaxDroop;
                suspensions[i + 0].mCamberAtMaxCompression = camberAngleAtMaxCompression;
                suspensions[i + 1].mCamberAtMaxCompression = -camberAngleAtMaxCompression;
            }
        }

        //Set up the wheel geometry.
        physx::PxVec3 suspTravelDirections[4];
        physx::PxVec3 wheelCentreCMOffsets[4];
        physx::PxVec3 suspForceAppCMOffsets[4];
        physx::PxVec3 tireForceAppCMOffsets[4];
        {
            //Set the geometry data.
            for (uint32_t i = 0; i < 4; i++)
            {
                //Vertical suspension travel.
                suspTravelDirections[i] = physx::PxVec3(0,-1,0);

                //Wheel center offset is offset from rigid body center of mass.
                wheelCentreCMOffsets[i] =
                        pxWheelCenterActorOffsets[i] - pxChassisCMOffset;

                //Suspension force application point 0.3 metres below
                //rigid body center of mass.
                suspForceAppCMOffsets[i] =
                        physx::PxVec3(wheelCentreCMOffsets[i].x,-0.3f,wheelCentreCMOffsets[i].z);

                //Tire force application point 0.3 metres below
                //rigid body center of mass.
                tireForceAppCMOffsets[i] =
                        physx::PxVec3(wheelCentreCMOffsets[i].x,-0.3f,wheelCentreCMOffsets[i].z);
            }
        }

        //Set up the filter data of the raycast that will be issued by each suspension.
        physx::PxFilterData qryFilterData;
        ///setupNonDrivableSurface(qryFilterData);
        qryFilterData.word3 = 0; //TODO: based.

        //Set the wheel, tire and suspension data.
        //Set the geometry data.
        //Set the query filter data
        for(uint32_t i = 0; i < 4; i++)
        {
            wheelsSimData->setWheelData(i, wheels[i]);
            wheelsSimData->setTireData(i, tires[i]);
            wheelsSimData->setSuspensionData(i, suspensions[i]);
            wheelsSimData->setSuspTravelDirection(i, suspTravelDirections[i]);
            wheelsSimData->setWheelCentreOffset(i, wheelCentreCMOffsets[i]);
            wheelsSimData->setSuspForceAppPointOffset(i, suspForceAppCMOffsets[i]);
            wheelsSimData->setTireForceAppPointOffset(i, tireForceAppCMOffsets[i]);
            wheelsSimData->setSceneQueryFilterData(i, qryFilterData);
            wheelsSimData->setWheelShapeMapping(i, i);
        }

        return wheelsSimData;
    }

    physx::PxVehicleDriveSimData4W* PhysXVehicle4W3D::SetupDriveSimData4W() {
        if (!m_wheelsSimData){
            SRHalt("m_wheelsSimData is nullptr!");
            return nullptr;
        }

        auto driveSimData = new physx::PxVehicleDriveSimData4W();

        //Diff
        physx::PxVehicleDifferential4WData diff;
        diff.mType = physx::PxVehicleDifferential4WData::eDIFF_TYPE_LS_4WD;
        driveSimData->setDiffData(diff);

        //Engine
        physx::PxVehicleEngineData engine;
        engine.mPeakTorque = GetPeakTorque();
        engine.mMaxOmega = GetMaxOmega();
        driveSimData->setEngineData(engine);

        //Gears
        physx::PxVehicleGearsData gears;
        gears.mSwitchTime = GetSwitchTime();
        driveSimData->setGearsData(gears);

        //Clutch
        physx::PxVehicleClutchData clutch;
        clutch.mStrength = GetStrength();
        driveSimData->setClutchData(clutch);

        //Ackermann steer accuracy
        physx::PxVehicleAckermannGeometryData ackermann;
        ackermann.mAccuracy = GetAccuracy();

        ackermann.mAxleSeparation =
                m_wheelsSimData->getWheelCentreOffset(physx::PxVehicleDrive4WWheelOrder::eFRONT_LEFT).z -
                m_wheelsSimData->getWheelCentreOffset(physx::PxVehicleDrive4WWheelOrder::eREAR_LEFT).z;

        ackermann.mFrontWidth =
                m_wheelsSimData->getWheelCentreOffset(physx::PxVehicleDrive4WWheelOrder::eFRONT_RIGHT).x -
                m_wheelsSimData->getWheelCentreOffset(physx::PxVehicleDrive4WWheelOrder::eFRONT_LEFT).x;

        ackermann.mRearWidth =
                m_wheelsSimData->getWheelCentreOffset(physx::PxVehicleDrive4WWheelOrder::eREAR_RIGHT).x -
                m_wheelsSimData->getWheelCentreOffset(physx::PxVehicleDrive4WWheelOrder::eREAR_LEFT).x;

        driveSimData->setAckermannGeometryData(ackermann);

        return driveSimData;
    }

    physx::PxRigidDynamic* PhysXVehicle4W3D::SetupVehicleActor(
            const physx::PxVehicleChassisData &chassisData,
            physx::PxMaterial **wheelMaterials,
            physx::PxConvexMesh **wheelConvexMeshes,
            const physx::PxFilterData &wheelSimFilterData,
            physx::PxMaterial **chassisMaterials,
            physx::PxConvexMesh **chassisConvexMeshes,
            uint32_t numChassisMeshes,
            const physx::PxFilterData &chassisSimFilterData,
            physx::PxPhysics &physics
    ) {
        //We need a rigid body actor for the vehicle.
        //Don't forget to add the actor to the scene after setting up the associated vehicle.
        physx::PxRigidDynamic* vehActor = physics.createRigidDynamic(physx::PxTransform(physx::PxIdentity));

        //Wheel and chassis query filter data.
        //Optional: cars don't drive on other cars.
        physx::PxFilterData wheelQryFilterData;
        ///setupNonDrivableSurface(wheelQryFilterData);
        wheelQryFilterData.word3 = 0;
        physx::PxFilterData chassisQryFilterData;
        ///setupNonDrivableSurface(chassisQryFilterData);
        chassisQryFilterData.word3 = 0;

        //Add all the wheel shapes to the actor.
        for(uint32_t i = 0; i < 4; i++)
        {
            physx::PxConvexMeshGeometry geom(wheelConvexMeshes[i]);
            physx::PxShape* wheelShape = physx::PxRigidActorExt::createExclusiveShape(*vehActor, geom, *wheelMaterials[i]);
            wheelShape->setQueryFilterData(wheelQryFilterData);
            wheelShape->setSimulationFilterData(wheelSimFilterData);
            wheelShape->setLocalPose(physx::PxTransform(physx::PxIdentity));
        }

        //Add the chassis shapes to the actor.
        for(uint32_t i = 0; i < numChassisMeshes; i++)
        {
            physx::PxShape* chassisShape = physx::PxRigidActorExt::createExclusiveShape(*vehActor, physx::PxConvexMeshGeometry(chassisConvexMeshes[i]), *chassisMaterials[i]);
            chassisShape->setQueryFilterData(chassisQryFilterData);
            chassisShape->setSimulationFilterData(chassisSimFilterData);
            chassisShape->setLocalPose(physx::PxTransform(physx::PxIdentity));
        }

        vehActor->setMass(chassisData.mMass);
        vehActor->setMassSpaceInertiaTensor(chassisData.mMOI);
        vehActor->setCMassLocalPose(physx::PxTransform(chassisData.mCMOffset,physx::PxQuat(physx::PxIdentity)));

        return vehActor;
    }

    bool PhysXVehicle4W3D::InitVehicle() {
        if (!Super::InitVehicle()) {
            SRHalt("failed to init base vehicle!");
            return false;
        }


        return Super::InitVehicle();
    }

    void *PhysXVehicle4W3D::GetHandle() const noexcept {
        return nullptr;
    }
}