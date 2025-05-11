

# Class SR\_UTILS\_NS::MouseInputData



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**MouseInputData**](classSR__UTILS__NS_1_1MouseInputData.md)








Inherits the following classes: [SR\_UTILS\_NS::InputDeviceData](classSR__UTILS__NS_1_1InputDeviceData.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  MouseCode | [**m\_code**](#variable-m_code)  <br> |
|  SR\_MATH\_NS::FVector2 | [**m\_position**](#variable-m_position)  <br> |
|  SR\_MATH\_NS::FVector2 | [**m\_prevPos**](#variable-m_prevpos)  <br> |
|  KeyState | [**m\_state**](#variable-m_state)  <br> |
|  SR\_MATH\_NS::FVector2 | [**m\_wheel**](#variable-m_wheel)  <br> |
















































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD SR\_MATH\_NS::FVector2 | [**GetDrag**](#function-getdrag) () const<br> |
| virtual InputDeviceType | [**GetType**](#function-gettype) () override const<br> |
|  SR\_NODISCARD bool | [**IsDrag**](#function-isdrag) () const<br> |
|   | [**MouseInputData**](#function-mouseinputdata-12) (MouseCode code, KeyState state, const SR\_MATH\_NS::FVector2 & pos, const SR\_MATH\_NS::FVector2 & prevPos, const SR\_MATH\_NS::FVector2 & wheel) <br> |
|   | [**MouseInputData**](#function-mouseinputdata-22) () <br> |
|   | [**~MouseInputData**](#function-mouseinputdata) () override<br> |


## Public Functions inherited from SR_UTILS_NS::InputDeviceData

See [SR\_UTILS\_NS::InputDeviceData](classSR__UTILS__NS_1_1InputDeviceData.md)

| Type | Name |
| ---: | :--- |
| virtual InputDeviceType | [**GetType**](classSR__UTILS__NS_1_1InputDeviceData.md#function-gettype) () const = 0<br> |
|   | [**~InputDeviceData**](classSR__UTILS__NS_1_1InputDeviceData.md#function-inputdevicedata) () override<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |








































































## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |








## Public Attributes Documentation




### variable m\_code 

```C++
MouseCode SR_UTILS_NS::MouseInputData::m_code;
```




<hr>



### variable m\_position 

```C++
SR_MATH_NS::FVector2 SR_UTILS_NS::MouseInputData::m_position;
```




<hr>



### variable m\_prevPos 

```C++
SR_MATH_NS::FVector2 SR_UTILS_NS::MouseInputData::m_prevPos;
```




<hr>



### variable m\_state 

```C++
KeyState SR_UTILS_NS::MouseInputData::m_state;
```




<hr>



### variable m\_wheel 

```C++
SR_MATH_NS::FVector2 SR_UTILS_NS::MouseInputData::m_wheel;
```




<hr>
## Public Functions Documentation




### function GetDrag 

```C++
SR_NODISCARD SR_MATH_NS::FVector2 SR_UTILS_NS::MouseInputData::GetDrag () const
```




<hr>



### function GetType 

```C++
virtual InputDeviceType SR_UTILS_NS::MouseInputData::GetType () override const
```



Implements [*SR\_UTILS\_NS::InputDeviceData::GetType*](classSR__UTILS__NS_1_1InputDeviceData.md#function-gettype)


<hr>



### function IsDrag 

```C++
SR_NODISCARD bool SR_UTILS_NS::MouseInputData::IsDrag () const
```




<hr>



### function MouseInputData [1/2]

```C++
inline SR_UTILS_NS::MouseInputData::MouseInputData (
    MouseCode code,
    KeyState state,
    const SR_MATH_NS::FVector2 & pos,
    const SR_MATH_NS::FVector2 & prevPos,
    const SR_MATH_NS::FVector2 & wheel
) 
```




<hr>



### function MouseInputData [2/2]

```C++
inline SR_UTILS_NS::MouseInputData::MouseInputData () 
```




<hr>



### function ~MouseInputData 

```C++
SR_UTILS_NS::MouseInputData::~MouseInputData () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Input/InputDevice.h`

