

# Struct ObjectDataAccessor&lt; SR\_HTYPES\_NS::SharedPtr&lt; T &gt;, std::enable\_if\_t&lt;!SerializationTraits&lt; T &gt;::HasOriginType &gt; &gt;

**template &lt;typename T&gt;**



[**ClassList**](annotated.md) **>** [**ObjectDataAccessor&lt; SR\_HTYPES\_NS::SharedPtr&lt; T &gt;, std::enable\_if\_t&lt;!SerializationTraits&lt; T &gt;::HasOriginType &gt; &gt;**](structObjectDataAccessor_3_01SR__HTYPES__NS_1_1SharedPtr_3_01T_01_4_00_01std_1_1enable__if__t_3_bb92e27d691c2f87c93122b3b271db79.md)












































## Public Static Functions

| Type | Name |
| ---: | :--- |
|  void | [**Load**](#function-load) (ISerializer &, [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; &, const SerializationId &) <br> |
|  void | [**Save**](#function-save) (IDeserializer &, const [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; &, const SerializationId &) <br> |


























## Public Static Functions Documentation




### function Load 

```C++
static inline void ObjectDataAccessor< SR_HTYPES_NS::SharedPtr< T >, std::enable_if_t<!SerializationTraits< T >::HasOriginType > >::Load (
    ISerializer &,
    SR_HTYPES_NS::SharedPtr < T > &,
    const SerializationId &
) 
```




<hr>



### function Save 

```C++
static inline void ObjectDataAccessor< SR_HTYPES_NS::SharedPtr< T >, std::enable_if_t<!SerializationTraits< T >::HasOriginType > >::Save (
    IDeserializer &,
    const SR_HTYPES_NS::SharedPtr < T > &,
    const SerializationId &
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Serialization/ObjectDataAccessors.inl.h`

