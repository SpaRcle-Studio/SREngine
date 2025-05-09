

# Class SR\_SCRIPTING\_NS::EvoBehaviour



[**ClassList**](annotated.md) **>** [**SR\_SCRIPTING\_NS**](namespaceSR__SCRIPTING__NS.md) **>** [**EvoBehaviour**](classSR__SCRIPTING__NS_1_1EvoBehaviour.md)








Inherits the following classes: SR_SCRIPTING_NS::IRawBehaviour


































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**EvoBehaviour**](#function-evobehaviour) () <br> |
|  Properties | [**GetProperties**](#function-getproperties) () override const<br> |
|  std::any | [**GetProperty**](#function-getproperty) (const std::string & id) override const<br> |
|  void | [**SetComponent**](#function-setcomponent) ([**Behaviour**](classSR__SCRIPTING__NS_1_1Behaviour.md) \* pBehaviour) override<br> |
|  void | [**SetProperty**](#function-setproperty) (const std::string & id, const std::any & val) override<br> |
























## Protected Functions

| Type | Name |
| ---: | :--- |
|  void | [**Awake**](#function-awake) () override<br> |
|  void | [**FixedUpdate**](#function-fixedupdate) () override<br> |
|  SR\_NODISCARD uint64\_t | [**GetFileHash**](#function-getfilehash) () override const<br> |
|  bool | [**Load**](#function-load) () override<br> |
|  void | [**OnAttached**](#function-onattached) () override<br> |
|  void | [**OnCollisionEnter**](#function-oncollisionenter) (const [**SR\_UTILS\_NS::CollisionData**](structSR__UTILS__NS_1_1CollisionData.md) & data) override<br> |
|  void | [**OnCollisionExit**](#function-oncollisionexit) (const [**SR\_UTILS\_NS::CollisionData**](structSR__UTILS__NS_1_1CollisionData.md) & data) override<br> |
|  void | [**OnCollisionStay**](#function-oncollisionstay) (const [**SR\_UTILS\_NS::CollisionData**](structSR__UTILS__NS_1_1CollisionData.md) & data) override<br> |
|  void | [**OnDestroy**](#function-ondestroy) () override<br> |
|  void | [**OnDetached**](#function-ondetached) () override<br> |
|  void | [**OnDisable**](#function-ondisable) () override<br> |
|  void | [**OnEnable**](#function-onenable) () override<br> |
|  void | [**OnTransformSet**](#function-ontransformset) () override<br> |
|  void | [**OnTriggerEnter**](#function-ontriggerenter) (const [**SR\_UTILS\_NS::CollisionData**](structSR__UTILS__NS_1_1CollisionData.md) & data) override<br> |
|  void | [**OnTriggerExit**](#function-ontriggerexit) (const [**SR\_UTILS\_NS::CollisionData**](structSR__UTILS__NS_1_1CollisionData.md) & data) override<br> |
|  void | [**OnTriggerStay**](#function-ontriggerstay) (const [**SR\_UTILS\_NS::CollisionData**](structSR__UTILS__NS_1_1CollisionData.md) & data) override<br> |
|  void | [**Start**](#function-start) () override<br> |
|  bool | [**Unload**](#function-unload) () override<br> |
|  void | [**Update**](#function-update) (float\_t dt) override<br> |




## Public Functions Documentation




### function EvoBehaviour 

```C++
inline SR_SCRIPTING_NS::EvoBehaviour::EvoBehaviour () 
```




<hr>



### function GetProperties 

```C++
Properties SR_SCRIPTING_NS::EvoBehaviour::GetProperties () override const
```




<hr>



### function GetProperty 

```C++
std::any SR_SCRIPTING_NS::EvoBehaviour::GetProperty (
    const std::string & id
) override const
```




<hr>



### function SetComponent 

```C++
inline void SR_SCRIPTING_NS::EvoBehaviour::SetComponent (
    Behaviour * pBehaviour
) override
```




<hr>



### function SetProperty 

```C++
void SR_SCRIPTING_NS::EvoBehaviour::SetProperty (
    const std::string & id,
    const std::any & val
) override
```




<hr>
## Protected Functions Documentation




### function Awake 

```C++
void SR_SCRIPTING_NS::EvoBehaviour::Awake () override
```




<hr>



### function FixedUpdate 

```C++
void SR_SCRIPTING_NS::EvoBehaviour::FixedUpdate () override
```




<hr>



### function GetFileHash 

```C++
SR_NODISCARD uint64_t SR_SCRIPTING_NS::EvoBehaviour::GetFileHash () override const
```




<hr>



### function Load 

```C++
bool SR_SCRIPTING_NS::EvoBehaviour::Load () override
```




<hr>



### function OnAttached 

```C++
void SR_SCRIPTING_NS::EvoBehaviour::OnAttached () override
```




<hr>



### function OnCollisionEnter 

```C++
void SR_SCRIPTING_NS::EvoBehaviour::OnCollisionEnter (
    const SR_UTILS_NS::CollisionData & data
) override
```




<hr>



### function OnCollisionExit 

```C++
void SR_SCRIPTING_NS::EvoBehaviour::OnCollisionExit (
    const SR_UTILS_NS::CollisionData & data
) override
```




<hr>



### function OnCollisionStay 

```C++
void SR_SCRIPTING_NS::EvoBehaviour::OnCollisionStay (
    const SR_UTILS_NS::CollisionData & data
) override
```




<hr>



### function OnDestroy 

```C++
void SR_SCRIPTING_NS::EvoBehaviour::OnDestroy () override
```




<hr>



### function OnDetached 

```C++
void SR_SCRIPTING_NS::EvoBehaviour::OnDetached () override
```




<hr>



### function OnDisable 

```C++
void SR_SCRIPTING_NS::EvoBehaviour::OnDisable () override
```




<hr>



### function OnEnable 

```C++
void SR_SCRIPTING_NS::EvoBehaviour::OnEnable () override
```




<hr>



### function OnTransformSet 

```C++
void SR_SCRIPTING_NS::EvoBehaviour::OnTransformSet () override
```




<hr>



### function OnTriggerEnter 

```C++
void SR_SCRIPTING_NS::EvoBehaviour::OnTriggerEnter (
    const SR_UTILS_NS::CollisionData & data
) override
```




<hr>



### function OnTriggerExit 

```C++
void SR_SCRIPTING_NS::EvoBehaviour::OnTriggerExit (
    const SR_UTILS_NS::CollisionData & data
) override
```




<hr>



### function OnTriggerStay 

```C++
void SR_SCRIPTING_NS::EvoBehaviour::OnTriggerStay (
    const SR_UTILS_NS::CollisionData & data
) override
```




<hr>



### function Start 

```C++
void SR_SCRIPTING_NS::EvoBehaviour::Start () override
```




<hr>



### function Unload 

```C++
bool SR_SCRIPTING_NS::EvoBehaviour::Unload () override
```




<hr>



### function Update 

```C++
void SR_SCRIPTING_NS::EvoBehaviour::Update (
    float_t dt
) override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Scripting/inc/Scripting/Old/Impl/EvoBehaviour.h`

