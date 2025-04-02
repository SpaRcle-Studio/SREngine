

# Namespace std



[**Namespace List**](namespaces.md) **>** [**std**](namespacestd.md)




















## Classes

| Type | Name |
| ---: | :--- |
| struct | [**hash&lt; SR\_GRAPH\_GUI\_NS::Link &gt;**](structstd_1_1hash_3_01SR__GRAPH__GUI__NS_1_1Link_01_4.md) &lt;&gt;<br> |
| struct | [**hash&lt; SR\_GRAPH\_GUI\_NS::Node &gt;**](structstd_1_1hash_3_01SR__GRAPH__GUI__NS_1_1Node_01_4.md) &lt;&gt;<br> |
| struct | [**hash&lt; SR\_GRAPH\_NS::Vertices::SimpleVertex &gt;**](structstd_1_1hash_3_01SR__GRAPH__NS_1_1Vertices_1_1SimpleVertex_01_4.md) &lt;&gt;<br> |
| struct | [**hash&lt; SR\_GRAPH\_NS::Vertices::StaticMeshVertex &gt;**](structstd_1_1hash_3_01SR__GRAPH__NS_1_1Vertices_1_1StaticMeshVertex_01_4.md) &lt;&gt;<br> |
| struct | [**hash&lt; SR\_GRAPH\_NS::Vertices::UIVertex &gt;**](structstd_1_1hash_3_01SR__GRAPH__NS_1_1Vertices_1_1UIVertex_01_4.md) &lt;&gt;<br> |
| struct | [**hash&lt; SR\_HTYPES\_NS::SafePtr&lt; T &gt; &gt;**](structstd_1_1hash_3_01SR__HTYPES__NS_1_1SafePtr_3_01T_01_4_01_4.md) &lt;typename T&gt;<br> |
| struct | [**hash&lt; SR\_HTYPES\_NS::SharedPtr&lt; T &gt; &gt;**](structstd_1_1hash_3_01SR__HTYPES__NS_1_1SharedPtr_3_01T_01_4_01_4.md) &lt;typename T&gt;<br> |
| struct | [**hash&lt; SR\_MATH\_NS::Vector2&lt; U &gt; &gt;**](structstd_1_1hash_3_01SR__MATH__NS_1_1Vector2_3_01U_01_4_01_4.md) &lt;typename U&gt;<br> |
| struct | [**hash&lt; SR\_MATH\_NS::Vector3&lt; U &gt; &gt;**](structstd_1_1hash_3_01SR__MATH__NS_1_1Vector3_3_01U_01_4_01_4.md) &lt;typename U&gt;<br> |
| struct | [**hash&lt; SR\_UTILS\_NS::StringAtom &gt;**](structstd_1_1hash_3_01SR__UTILS__NS_1_1StringAtom_01_4.md) &lt;&gt;<br> |
| struct | [**hash&lt; SR\_WORLD\_NS::TensorKey &gt;**](structstd_1_1hash_3_01SR__WORLD__NS_1_1TensorKey_01_4.md) &lt;&gt;<br> |
| struct | [**less&lt; SR\_HTYPES\_NS::SafePtr&lt; T &gt; &gt;**](structstd_1_1less_3_01SR__HTYPES__NS_1_1SafePtr_3_01T_01_4_01_4.md) &lt;typename T&gt;<br> |
| struct | [**less&lt; SR\_HTYPES\_NS::SharedPtr&lt; T &gt; &gt;**](structstd_1_1less_3_01SR__HTYPES__NS_1_1SharedPtr_3_01T_01_4_01_4.md) &lt;typename T&gt;<br> |
| struct | [**less&lt; SR\_UTILS\_NS::StringAtom &gt;**](structstd_1_1less_3_01SR__UTILS__NS_1_1StringAtom_01_4.md) &lt;&gt;<br> |






## Public Attributes

| Type | Name |
| ---: | :--- |
|  WIDE\_INTEGER\_NUM\_LIMITS\_CLASS\_TYPE | [**AllocatorType**](#variable-allocatortype)  <br> |
|  WIDE\_INTEGER\_NUM\_LIMITS\_CLASS\_TYPE | [**IsSigned**](#variable-issigned)   = `{ }`<br> |
|  WIDE\_INTEGER\_NUM\_LIMITS\_CLASS\_TYPE | [**LimbType**](#variable-limbtype)  <br> |
|  WIDE\_INTEGER\_NUM\_LIMITS\_CLASS\_TYPE | [**numeric\_limits&lt; SR\_TYPES\_NS::uintwide\_t&lt; Width2, LimbType, AllocatorType, IsSigned &gt; &gt;**](#variable-numeric_limits<-sr_types_ns::uintwide_t<-width2,-limbtype,-allocatortype,-issigned->->)  <br> |


















## Public Static Functions

| Type | Name |
| ---: | :--- |
|  void | [**hash\_combine**](#function-hash_combine) (std::size\_t & s, const T & v) <br> |
|  void | [**hash\_vector2\_combine**](#function-hash_vector2_combine) (std::size\_t & s, const T & v) <br> |
|  void | [**hash\_vector3\_combine**](#function-hash_vector3_combine) (std::size\_t & s, const T & v) <br> |


























## Public Attributes Documentation




### variable AllocatorType 

```C++
WIDE_INTEGER_NUM_LIMITS_CLASS_TYPE std::AllocatorType;
```




<hr>



### variable IsSigned 

```C++
WIDE_INTEGER_NUM_LIMITS_CLASS_TYPE std::IsSigned;
```




<hr>



### variable LimbType 

```C++
WIDE_INTEGER_NUM_LIMITS_CLASS_TYPE std::LimbType;
```




<hr>



### variable numeric\_limits&lt; SR\_TYPES\_NS::uintwide\_t&lt; Width2, LimbType, AllocatorType, IsSigned &gt; &gt; 

```C++
WIDE_INTEGER_NUM_LIMITS_CLASS_TYPE std::numeric_limits< SR_TYPES_NS::uintwide_t< Width2, LimbType, AllocatorType, IsSigned > >;
```




<hr>
## Public Static Functions Documentation




### function hash\_combine 

```C++
template<class T>
static inline void std::hash_combine (
    std::size_t & s,
    const T & v
) 
```




<hr>



### function hash\_vector2\_combine 

```C++
template<class T>
static inline void std::hash_vector2_combine (
    std::size_t & s,
    const T & v
) 
```




<hr>



### function hash\_vector3\_combine 

```C++
template<class T>
static inline void std::hash_vector3_combine (
    std::size_t & s,
    const T & v
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/GUI/Node.h`

