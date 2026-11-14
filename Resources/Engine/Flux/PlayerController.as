class PlayerController : ScriptBehaviour
{
    EntityRef<GameObject> camera;
    EntityRef<GameObject> body;
    EntityRef<GameObject> headModel;
    EntityRef<GameObject> headBone;

    float walkSpeed = 4.0f;
    float runSpeed = 10.0f;
    float jumpSpeed = 5.0f;
    float mouseSensitivity = 0.1f;
    float cameraFollowSpeed = 1.0f;
    float cameraSmoothing = 12.0f;
    float skinWidth = 0.01f;
    float rotationSpeed = 5.0f;

    bool onlyPlayMode = false;

    private CharacterController@ m_controller;
    private Animator@ m_animator;
    private CursorLock m_cursorLock;

    private float m_verticalVelocity = 0.0f;
    private float m_cameraPitch = 0.0f;
    private float m_bodyYawTarget = 0.0f;
    private float m_bodyYaw = 0.0f;

    private float gravity = 9.81f;

    void Awake()
    {
        m_cursorLock.SetLockMode(CursorLockMode::PlayMode);
        m_cursorLock.Lock();

        if (gameObject is null)
            return;

        @m_controller = cast<CharacterController@>(gameObject.GetComponent("CharacterController"));
        @m_animator = cast<Animator@>(gameObject.GetComponent("Animator"));
        if (m_animator is null) {
            GameObject@ bodyObject = body.get();
            if (bodyObject !is null)
                @m_animator = cast<Animator@>(bodyObject.GetComponent("Animator"));
        }
    }

    void FixedUpdate()
    {
        Input@ input = Input::Instance();
        MathUtils@ math = MathUtils::Instance();

        if (m_animator is null || m_controller is null || (!input.IsPlayMode() && onlyPlayMode))
            return;

        GameObject@ bodyObject = body.get();
        if (bodyObject is null)
            return;

        Transform@ movementTransform = gameObject.GetTransform();

        const bool running = input.GetKey(KeyCode::LShift);
        const float speed = running ? runSpeed : walkSpeed;
        const float dt = Time::Instance().FixedDeltaTime();

        FVector3 direction = FVector3();
        if (input.GetKey(KeyCode::W)) direction.z += 1.0f;
        if (input.GetKey(KeyCode::S)) direction.z -= 1.0f;
        if (input.GetKey(KeyCode::A)) direction.x -= 1.0f;
        if (input.GetKey(KeyCode::D)) direction.x += 1.0f;

        const bool forward = input.GetKey(KeyCode::W);
        const bool backward = input.GetKey(KeyCode::S);
        const bool left = input.GetKey(KeyCode::A);
        const bool right = input.GetKey(KeyCode::D);
        m_bodyYawTarget = 0.0f;
        if (left || right) {
            const float angle = (forward || backward) ? 45.0f : 90.0f;
            m_bodyYawTarget = angle * (backward ? -1.0f : 1.0f) * (right ? 1.0f : -1.0f);
        }

        const float length = MathUtils::Instance().Length(direction);
        direction = movementTransform.TransformDirection(direction);
        direction = math.Normalize(direction);
        direction.x *= speed * dt;
        direction.z *= speed * dt;

        // The ground probe can still reach the floor during the first frames of ascent.
        const bool grounded = m_verticalVelocity <= 0.0f && m_controller.IsGrounded();
        if (input.GetKeyDown(KeyCode::Space) && grounded) {
            m_verticalVelocity = jumpSpeed;
            if (m_animator !is null)
                m_animator.FastForwardState("Jump");
        }
        else if (grounded)
            m_verticalVelocity = 0.0f;

        if (!grounded || m_verticalVelocity > 0.0f) {
            direction.y = m_verticalVelocity * dt - 0.5f * gravity * dt * dt;
            m_verticalVelocity -= gravity * dt;
        }

        // PhysX treats this argument as minimum movement distance, not capsule skin width.
        // Keep small vertical steps near the apex instead of discarding them.
        const float minMoveDistance = direction.y != 0.0f ? 0.0f : skinWidth;
        m_controller.Move(direction, minMoveDistance, dt);

        const bool landed = m_verticalVelocity <= 0.0f && m_controller.IsGrounded();
        if (landed) {
            m_verticalVelocity = 0.0f;
            const bool moving = length > 0.0f;
            m_animator.SetBool("Idle", !(moving || running));
            m_animator.SetBool("Walk", moving && !running);
            m_animator.SetBool("Run", moving && running);
            if (input.GetKeyDown(KeyCode::J))
                m_animator.FastForwardState("Dancing");
        }
        m_animator.SetBool("Falling", !landed);
    }

    void Update(float dt)
    {
        Input@ input = Input::Instance();
        MathUtils@ math = MathUtils::Instance();
        if (!input.IsPlayMode() && onlyPlayMode)
            return;

        FVector2@ mouseDrag = input.GetMouseDrag();
        if (gameObject !is null)
            gameObject.GetTransform().RotateXYZ(0.0f, mouseDrag.x * mouseSensitivity, 0.0f);

        GameObject@ cameraObject = camera.get();
        if (cameraObject !is null)
        {
            Transform@ cameraTransform = cameraObject.GetTransform();
            if (cameraTransform !is null)
            {
                m_cameraPitch += mouseDrag.y * mouseSensitivity;
                if (m_cameraPitch < -89.0f) m_cameraPitch = -89.0f;
                if (m_cameraPitch > 89.0f) m_cameraPitch = 89.0f;
                cameraTransform.SetRotationXYZ(m_cameraPitch, 0.0f, 0.0f);
            }
        }

        GameObject@ headModelObject = headModel.get();
        if (headModelObject !is null)
            headModelObject.SetEnabled(!input.IsPlayMode());

        GameObject@ bodyObject = body.get();
        if (bodyObject is null)
            return;

        Transform@ bodyTransform = bodyObject.GetTransform();

        const float rotationFactor = math.ClampFloat(rotationSpeed * Time::Instance().DeltaTime(), 0.0f, 1.0f);
        m_bodyYaw = math.LerpAngle(m_bodyYaw, m_bodyYawTarget, rotationFactor);
        bodyTransform.SetRotationXYZ(0.0f, m_bodyYaw, 0.0f);

        GameObject@ headBoneObject = headBone.get();
        if (cameraObject !is null && headBoneObject !is null)
        {
            Transform@ cameraTransform = cameraObject.GetTransform();
            Transform@ headTransform = headBoneObject.GetTransform();
            if (cameraTransform is null || headTransform is null)
                return;

            Quaternion@ quat = math.InverseQuaternion(math.QuaternionFromEulerAngles(0.f, m_bodyYaw, 0.f));
            FVector3@ dir = headTransform.TransformDirection(math.MakeFVector3(0.13f, -0.21f, 0.f));
            FVector3@ offset = math.MultiplyFVector3Quat(dir, quat);

            const float smoothingStep = math.ClampFloat(cameraSmoothing, 0.0f, 1000.0f)
                * math.ClampFloat(dt, 0.0f, 1.0f);
            const float followFactor = math.ClampFloat(cameraFollowSpeed, 0.0f, 1.0f)
                * smoothingStep / (1.0f + smoothingStep);
            cameraTransform.Follow(headTransform, offset, followFactor);
        }
    }
}
