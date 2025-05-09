

# Class SR\_UTILS\_NS::KeyboardInputData



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**KeyboardInputData**](classSR__UTILS__NS_1_1KeyboardInputData.md)








Inherits the following classes: [SR\_UTILS\_NS::InputDeviceData](classSR__UTILS__NS_1_1InputDeviceData.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  KeyCode | [**m\_code**](#variable-m_code)  <br> |
|  KeyState | [**m\_state**](#variable-m_state)  <br> |
















































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD KeyCode | [**GetKeyCode**](#function-getkeycode) () const<br> |
| virtual InputDeviceType | [**GetType**](#function-gettype) () override const<br> |
|   | [**KeyboardInputData**](#function-keyboardinputdata-12) (KeyCode code, KeyState state) <br> |
|   | [**KeyboardInputData**](#function-keyboardinputdata-22) () <br> |


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
KeyCode SR_UTILS_NS::KeyboardInputData::m_code;
```




<hr>



### variable m\_state 

```C++
KeyState SR_UTILS_NS::KeyboardInputData::m_state;
```




<hr>
## Public Functions Documentation




### function GetKeyCode 

```C++
SR_NODISCARD KeyCode SR_UTILS_NS::KeyboardInputData::GetKeyCode () const
```




<hr>



### function GetType 

```C++
virtual InputDeviceType SR_UTILS_NS::KeyboardInputData::GetType () override const
```



Implements [*SR\_UTILS\_NS::InputDeviceData::GetType*](classSR__UTILS__NS_1_1InputDeviceData.md#function-gettype)


<hr>



### function KeyboardInputData [1/2]

```C++
inline SR_UTILS_NS::KeyboardInputData::KeyboardInputData (
    KeyCode code,
    KeyState state
) 
```




<hr>



### function KeyboardInputData [2/2]

```C++
inline SR_UTILS_NS::KeyboardInputData::KeyboardInputData () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Input/InputDevice.h`

