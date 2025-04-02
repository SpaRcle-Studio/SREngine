

# Struct SR\_UTILS\_NS::ObjectDataAccessor&lt; std::string &gt;

**template &lt;&gt;**



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**ObjectDataAccessor&lt; std::string &gt;**](structSR__UTILS__NS_1_1ObjectDataAccessor_3_01std_1_1string_01_4.md)



_Data accessors for objects serialization._ 

* `#include <Serialization.h>`







































## Public Static Functions

| Type | Name |
| ---: | :--- |
|  void | [**Load**](#function-load-12) ([**IDeserializer**](classSR__UTILS__NS_1_1IDeserializer.md) & deserializer, std::string & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & id) <br> |
|  void | [**Load**](#function-load-22) ([**IDeserializer**](classSR__UTILS__NS_1_1IDeserializer.md) &, std::string &, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) &) <br> |
|  void | [**Save**](#function-save-12) ([**ISerializer**](classSR__UTILS__NS_1_1ISerializer.md) & serializer, const std::string & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & id) <br> |
|  void | [**Save**](#function-save-22) ([**ISerializer**](classSR__UTILS__NS_1_1ISerializer.md) &, const std::string &, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) &) <br> |


























## Public Static Functions Documentation




### function Load [1/2]

```C++
static inline void SR_UTILS_NS::ObjectDataAccessor< std::string >::Load (
    IDeserializer & deserializer,
    std::string & value,
    const SerializationId & id
) 
```




<hr>



### function Load [2/2]

```C++
static inline void SR_UTILS_NS::ObjectDataAccessor< std::string >::Load (
    IDeserializer &,
    std::string &,
    const SerializationId &
) 
```




<hr>



### function Save [1/2]

```C++
static inline void SR_UTILS_NS::ObjectDataAccessor< std::string >::Save (
    ISerializer & serializer,
    const std::string & value,
    const SerializationId & id
) 
```




<hr>



### function Save [2/2]

```C++
static inline void SR_UTILS_NS::ObjectDataAccessor< std::string >::Save (
    ISerializer &,
    const std::string &,
    const SerializationId &
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Serialization/ObjectDataAccessors.inl.h`

