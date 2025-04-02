

# Class SR\_UTILS\_NS::InputDeviceData



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**InputDeviceData**](classSR__UTILS__NS_1_1InputDeviceData.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)


Inherited by the following classes: [SR\_UTILS\_NS::KeyboardInputData](classSR__UTILS__NS_1_1KeyboardInputData.md),  [SR\_UTILS\_NS::MouseInputData](classSR__UTILS__NS_1_1MouseInputData.md)




















































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual InputDeviceType | [**GetType**](#function-gettype) () const = 0<br> |
|   | [**~InputDeviceData**](#function-inputdevicedata) () override<br> |


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
|  constexpr | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () = default<br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () = default<br> |






## Public Functions Documentation




### function GetType 

```C++
virtual InputDeviceType SR_UTILS_NS::InputDeviceData::GetType () const = 0
```




<hr>



### function ~InputDeviceData 

```C++
SR_UTILS_NS::InputDeviceData::~InputDeviceData () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Input/InputDevice.h`

