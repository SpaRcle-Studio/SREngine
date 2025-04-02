

# Struct SR\_UTILS\_NS::ObjectDataAccessor&lt; SR\_HTYPES\_NS::SharedPtr&lt; T &gt;, std::enable\_if\_t&lt; SerializationTraits&lt; T &gt;::IsSerializable &gt; &gt;

**template &lt;typename T&gt;**



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**ObjectDataAccessor&lt; SR\_HTYPES\_NS::SharedPtr&lt; T &gt;, std::enable\_if\_t&lt; SerializationTraits&lt; T &gt;::IsSerializable &gt; &gt;**](structSR__UTILS__NS_1_1ObjectDataAccessor_3_01SR__HTYPES__NS_1_1SharedPtr_3_01T_01_4_00_01std_1_bcc0cde7fe2a1b6a6c918edb68e74246.md)












































## Public Static Functions

| Type | Name |
| ---: | :--- |
|  void | [**Load**](#function-load-12) ([**IDeserializer**](classSR__UTILS__NS_1_1IDeserializer.md) & deserializer, [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & id) <br> |
|  void | [**Load**](#function-load-22) ([**IDeserializer**](classSR__UTILS__NS_1_1IDeserializer.md) &, T &, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) &) <br> |
|  void | [**Save**](#function-save-12) ([**ISerializer**](classSR__UTILS__NS_1_1ISerializer.md) & serializer, const [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & id) <br> |
|  void | [**Save**](#function-save-22) ([**ISerializer**](classSR__UTILS__NS_1_1ISerializer.md) &, const T &, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) &) <br> |


























## Public Static Functions Documentation




### function Load [1/2]

```C++
static inline void SR_UTILS_NS::ObjectDataAccessor< SR_HTYPES_NS::SharedPtr< T >, std::enable_if_t< SerializationTraits< T >::IsSerializable > >::Load (
    IDeserializer & deserializer,
    SR_HTYPES_NS::SharedPtr < T > & value,
    const SerializationId & id
) 
```




<hr>



### function Load [2/2]

```C++
static inline void SR_UTILS_NS::ObjectDataAccessor< SR_HTYPES_NS::SharedPtr< T >, std::enable_if_t< SerializationTraits< T >::IsSerializable > >::Load (
    IDeserializer &,
    T &,
    const SerializationId &
) 
```




<hr>



### function Save [1/2]

```C++
static inline void SR_UTILS_NS::ObjectDataAccessor< SR_HTYPES_NS::SharedPtr< T >, std::enable_if_t< SerializationTraits< T >::IsSerializable > >::Save (
    ISerializer & serializer,
    const SR_HTYPES_NS::SharedPtr < T > & value,
    const SerializationId & id
) 
```




<hr>



### function Save [2/2]

```C++
static inline void SR_UTILS_NS::ObjectDataAccessor< SR_HTYPES_NS::SharedPtr< T >, std::enable_if_t< SerializationTraits< T >::IsSerializable > >::Save (
    ISerializer &,
    const T &,
    const SerializationId &
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Serialization/ObjectDataAccessors.inl.h`

