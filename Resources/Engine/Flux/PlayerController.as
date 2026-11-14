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
    float cameraFollowSpeed = 0.1f;
    float skinWidth = 0.01f;

    bool onlyPlayMode = false;

    private CharacterController@ m_controller;
    private Animator@ m_animator;
    private CursorLock m_cursorLock;

    private float m_verticalVelocity = 0.0f;
    private float m_cameraPitch = 0.0f;
    private float m_cameraYaw = 0.0f;
    private float m_bodyYawTarget = 0.0f;
    private FVector3@ m_direction = FVector3();

    private float gravity = 9.81f;

    void Awake()
    {
        if (gameObject is null)
            return;

        @m_controller = cast<CharacterController@>(gameObject.GetComponent("CharacterController"));
        @m_animator = cast<Animator@>(gameObject.GetComponent("Animator"));

        if (m_animator is null)
        {
            GameObject@ cameraObject = camera.get();
            if (cameraObject !is null)
                @m_animator = cast<Animator@>(cameraObject.GetComponent("Animator"));
        }

        if (m_animator is null)
        {
            GameObject@ bodyObject = body.get();
            if (bodyObject !is null)
                @m_animator = cast<Animator@>(bodyObject.GetComponent("Animator"));
        }
    }

    void FixedUpdate()
    {
        Input@ input = Input::Instance();
        MathUtils@ math = MathUtils::Instance();

        if (m_controller is null || (!input.IsPlayMode() && onlyPlayMode))
            return;

        GameObject@ bodyObject = body.get();
        if (bodyObject is null)
            return;

        Transform@ bodyTransform = bodyObject.GetTransform();

        const bool running = input.GetKey(KeyCode::LShift);
        const float speed = running ? runSpeed : walkSpeed;
        const float dt = Time::Instance().FixedDeltaTime();

        FVector3 direction = m_direction;
        const float length = MathUtils::Instance().Length(direction);
        if (length > 0.0f) {
            direction.x /= length;
            direction.z /= length;
        }
        direction = bodyTransform.TransformDirection(direction);
        direction = math.Normalize(direction);
        direction.x *= speed * dt;
        direction.z *= speed * dt;

        const bool grounded = m_controller.IsGrounded();
        if (input.GetKeyDown(KeyCode::Space) && grounded)
        {
            m_verticalVelocity = jumpSpeed;
            if (m_animator !is null)
                m_animator.FastForwardState("Jump");
        }
        else if (grounded)
            m_verticalVelocity = 0.0f;
        else
            m_verticalVelocity -= gravity * dt;
        direction.y = m_verticalVelocity * dt;

        m_controller.Move(direction, skinWidth, dt);

        if (m_animator !is null)
        {
            const bool moving = length > 0.0f;
            m_animator.SetBool("Run", moving && running);
            m_animator.SetBool("Walk", moving && !running);
            m_animator.SetBool("Falling", !m_controller.IsGrounded());
            if (input.GetKeyDown(KeyCode::J))
                m_animator.FastForwardState("Dancing");
        }
    }

    void Update(float dt)
    {
        Input@ input = Input::Instance();
        MathUtils@ math = MathUtils::Instance();
        if (!input.IsPlayMode() && onlyPlayMode)
            return;

        m_direction = FVector3();
        if (input.GetKey(KeyCode::W)) m_direction.z += 1.0f;
        if (input.GetKey(KeyCode::S)) m_direction.z -= 1.0f;
        if (input.GetKey(KeyCode::A)) m_direction.x -= 1.0f;
        if (input.GetKey(KeyCode::D)) m_direction.x += 1.0f;

        m_cursorLock.SetLockMode(CursorLockMode::PlayMode);
        m_cursorLock.Lock();

        FVector2@ mouseDrag = input.GetMouseDrag();
        GameObject@ cameraObject = camera.get();
        if (cameraObject !is null)
        {
            Transform@ cameraTransform = cameraObject.GetTransform();
            if (cameraTransform !is null)
            {
                m_cameraYaw += mouseDrag.x * mouseSensitivity;
                m_cameraPitch += mouseDrag.y * mouseSensitivity;
                if (m_cameraPitch < -89.0f) m_cameraPitch = -89.0f;
                if (m_cameraPitch > 89.0f) m_cameraPitch = 89.0f;
                cameraTransform.SetRotationXYZ(m_cameraPitch, m_cameraYaw, 0.0f);
            }
        }

        GameObject@ headModelObject = headModel.get();
        if (headModelObject !is null)
            headModelObject.SetEnabled(!input.GetKey(KeyCode::LShift));

        GameObject@ bodyObject = body.get();
        if (bodyObject is null)
            return;

        Transform@ bodyTransform = bodyObject.GetTransform();

        const float rotationSpeed = 5.0f;
        m_bodyYawTarget = math.LerpAngle(m_bodyYawTarget, m_cameraYaw, rotationSpeed * dt);
        bodyTransform.SetRotationXYZ(0.0f, m_bodyYawTarget, 0.0f);

        GameObject@ headBoneObject = headBone.get();
        if (cameraObject !is null && headBoneObject !is null)
        {
            Transform@ cameraTransform = cameraObject.GetTransform();
            Transform@ headTransform = headBoneObject.GetTransform();

            Quaternion@ quat = math.InverseQuaternion(math.QuaternionFromEulerAngles(0.f, m_bodyYawTarget, 0.f));
            FVector3@ dir = bodyTransform.TransformDirection(math.MakeFVector3(0.f, -0.2f, 0.f));
            FVector3@ offset = math.MultiplyFVector3Quat(dir, quat);

            if (cameraTransform !is null && headTransform !is null)
                cameraTransform.Follow(headTransform, offset, cameraFollowSpeed);
        }
    }
}
