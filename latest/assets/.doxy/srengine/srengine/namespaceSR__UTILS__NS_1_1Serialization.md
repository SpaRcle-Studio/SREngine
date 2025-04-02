

# Namespace SR\_UTILS\_NS::Serialization



[**Namespace List**](namespaces.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**Serialization**](namespaceSR__UTILS__NS_1_1Serialization.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|  bool | [**CanBeSaved**](#function-canbesaved) (const T & value) <br> |
|  bool | [**IsValidValue**](#function-isvalidvalue) (const T & value) <br> |
|  bool | [**Load**](#function-load) ([**IDeserializer**](classSR__UTILS__NS_1_1IDeserializer.md) & deserializer, T & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & key) <br> |
|  void | [**Save**](#function-save) ([**ISerializer**](classSR__UTILS__NS_1_1ISerializer.md) & serializer, const T & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & key) <br> |
|  void | [**SaveCheckDefault**](#function-savecheckdefault) ([**ISerializer**](classSR__UTILS__NS_1_1ISerializer.md) & serializer, const T & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & key) <br> |




























## Public Functions Documentation




### function CanBeSaved 

```C++
template<typename T>
bool SR_UTILS_NS::Serialization::CanBeSaved (
    const T & value
) 
```




<hr>



### function IsValidValue 

```C++
template<typename T>
bool SR_UTILS_NS::Serialization::IsValidValue (
    const T & value
) 
```




<hr>



### function Load 

```C++
template<typename T>
bool SR_UTILS_NS::Serialization::Load (
    IDeserializer & deserializer,
    T & value,
    const SerializationId & key
) 
```




<hr>



### function Save 

```C++
template<typename T>
void SR_UTILS_NS::Serialization::Save (
    ISerializer & serializer,
    const T & value,
    const SerializationId & key
) 
```




<hr>



### function SaveCheckDefault 

```C++
template<typename T>
void SR_UTILS_NS::Serialization::SaveCheckDefault (
    ISerializer & serializer,
    const T & value,
    const SerializationId & key
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Serialization/Serialization.h`

