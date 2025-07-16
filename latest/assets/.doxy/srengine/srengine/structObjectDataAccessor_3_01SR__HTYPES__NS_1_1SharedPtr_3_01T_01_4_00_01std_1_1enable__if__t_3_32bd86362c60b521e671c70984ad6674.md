

# Struct ObjectDataAccessor&lt; SR\_HTYPES\_NS::SharedPtr&lt; T &gt;, std::enable\_if\_t&lt; SerializationTraits&lt; T &gt;::IsSerializable &gt; &gt;

**template &lt;typename T&gt;**



[**ClassList**](annotated.md) **>** [**ObjectDataAccessor&lt; SR\_HTYPES\_NS::SharedPtr&lt; T &gt;, std::enable\_if\_t&lt; SerializationTraits&lt; T &gt;::IsSerializable &gt; &gt;**](structObjectDataAccessor_3_01SR__HTYPES__NS_1_1SharedPtr_3_01T_01_4_00_01std_1_1enable__if__t_3_32bd86362c60b521e671c70984ad6674.md)




























## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  constexpr SerializationId | [**PTR\_ID**](#variable-ptr_id)   = `SerializationId::Create("ptr")`<br> |
|  constexpr SerializationId | [**TYPE\_ID**](#variable-type_id)   = `SerializationId::Create("type")`<br> |
















## Public Static Functions

| Type | Name |
| ---: | :--- |
|  void | [**Load**](#function-load) (IDeserializer & deserializer, [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & value, const SerializationId & id) <br> |
|  void | [**Save**](#function-save) (ISerializer & serializer, const [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & value, const SerializationId & id) <br> |


























## Public Static Attributes Documentation




### variable PTR\_ID 

```C++
constexpr SerializationId ObjectDataAccessor< SR_HTYPES_NS::SharedPtr< T >, std::enable_if_t< SerializationTraits< T >::IsSerializable > >::PTR_ID;
```




<hr>



### variable TYPE\_ID 

```C++
constexpr SerializationId ObjectDataAccessor< SR_HTYPES_NS::SharedPtr< T >, std::enable_if_t< SerializationTraits< T >::IsSerializable > >::TYPE_ID;
```




<hr>
## Public Static Functions Documentation




### function Load 

```C++
static inline void ObjectDataAccessor< SR_HTYPES_NS::SharedPtr< T >, std::enable_if_t< SerializationTraits< T >::IsSerializable > >::Load (
    IDeserializer & deserializer,
    SR_HTYPES_NS::SharedPtr < T > & value,
    const SerializationId & id
) 
```




<hr>



### function Save 

```C++
static inline void ObjectDataAccessor< SR_HTYPES_NS::SharedPtr< T >, std::enable_if_t< SerializationTraits< T >::IsSerializable > >::Save (
    ISerializer & serializer,
    const SR_HTYPES_NS::SharedPtr < T > & value,
    const SerializationId & id
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Serialization/ObjectDataAccessors.inl.h`

