

# Struct ObjectDataAccessor&lt; T, typename std::enable\_if&lt; IsSREnumV&lt; T &gt; &gt;::type &gt;

**template &lt;typename T&gt;**



[**ClassList**](annotated.md) **>** [**ObjectDataAccessor&lt; T, typename std::enable\_if&lt; IsSREnumV&lt; T &gt; &gt;::type &gt;**](structObjectDataAccessor_3_01T_00_01typename_01std_1_1enable__if_3_01IsSREnumV_3_01T_01_4_01_4_1_1type_01_4.md)












































## Public Static Functions

| Type | Name |
| ---: | :--- |
|  void | [**Load**](#function-load) (IDeserializer & deserializer, T & value, const SerializationId & id) <br> |
|  void | [**Save**](#function-save) (ISerializer & serializer, T value, const SerializationId & id) <br> |


























## Public Static Functions Documentation




### function Load 

```C++
static inline void ObjectDataAccessor< T, typename std::enable_if< IsSREnumV< T > >::type >::Load (
    IDeserializer & deserializer,
    T & value,
    const SerializationId & id
) 
```




<hr>



### function Save 

```C++
static inline void ObjectDataAccessor< T, typename std::enable_if< IsSREnumV< T > >::type >::Save (
    ISerializer & serializer,
    T value,
    const SerializationId & id
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Serialization/ObjectDataAccessors.inl.h`

