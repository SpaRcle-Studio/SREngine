

# Struct SR\_UTILS\_NS::ObjectDataAccessor

**template &lt;typename T, typename Enable&gt;**



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**ObjectDataAccessor**](structSR__UTILS__NS_1_1ObjectDataAccessor.md)



_Specialization for serializable types._ 

* `#include <ObjectDataAccessor.h>`







































## Public Static Functions

| Type | Name |
| ---: | :--- |
|  void | [**Load**](#function-load) ([**IDeserializer**](classSR__UTILS__NS_1_1IDeserializer.md) &, T &, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) &) <br> |
|  void | [**Save**](#function-save) ([**ISerializer**](classSR__UTILS__NS_1_1ISerializer.md) &, const T &, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) &) <br> |


























## Public Static Functions Documentation




### function Load 

```C++
static inline void SR_UTILS_NS::ObjectDataAccessor::Load (
    IDeserializer &,
    T &,
    const SerializationId &
) 
```




<hr>



### function Save 

```C++
static inline void SR_UTILS_NS::ObjectDataAccessor::Save (
    ISerializer &,
    const T &,
    const SerializationId &
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Serialization/ObjectDataAccessor.h`

