

# Struct ObjectDataAccessor&lt; std::set&lt; T, Less, Allocator &gt; &gt;

**template &lt;typename T, typename Less, typename Allocator&gt;**



[**ClassList**](annotated.md) **>** [**ObjectDataAccessor&lt; std::set&lt; T, Less, Allocator &gt; &gt;**](structObjectDataAccessor_3_01std_1_1set_3_01T_00_01Less_00_01Allocator_01_4_01_4.md)






















## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::set&lt; T, Less, Allocator &gt; | [**SetType**](#typedef-settype)  <br> |
| typedef typename SetType::value\_type | [**ValueType**](#typedef-valuetype)  <br> |






















## Public Static Functions

| Type | Name |
| ---: | :--- |
|  void | [**Load**](#function-load) (IDeserializer & deserializer, SetT & value, const SerializationId & id) <br> |
|  void | [**Save**](#function-save) (ISerializer & serializer, const SetType & value, const SerializationId & id) <br> |


























## Public Types Documentation




### typedef SetType 

```C++
using ObjectDataAccessor< std::set< T, Less, Allocator > >::SetType =  std::set<T, Less, Allocator>;
```




<hr>



### typedef ValueType 

```C++
using ObjectDataAccessor< std::set< T, Less, Allocator > >::ValueType =  typename SetType::value_type;
```




<hr>
## Public Static Functions Documentation




### function Load 

```C++
template<typename SetT>
static inline void ObjectDataAccessor< std::set< T, Less, Allocator > >::Load (
    IDeserializer & deserializer,
    SetT & value,
    const SerializationId & id
) 
```




<hr>



### function Save 

```C++
static inline void ObjectDataAccessor< std::set< T, Less, Allocator > >::Save (
    ISerializer & serializer,
    const SetType & value,
    const SerializationId & id
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Serialization/ObjectDataAccessors.inl.h`

