

# Class SR\_UTILS\_NS::VectorUtils



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**VectorUtils**](classSR__UTILS__NS_1_1VectorUtils.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|  bool | [**Contains**](#function-contains) (const std::vector&lt; T &gt; & v, const T & value) <br> |
|  void | [**InsertSorted**](#function-insertsorted) (std::vector&lt; T &gt; & v, const T & value) <br> |
|   | [**VectorUtils**](#function-vectorutils-12) () = delete<br> |
|   | [**VectorUtils**](#function-vectorutils-22) ([**VectorUtils**](classSR__UTILS__NS_1_1VectorUtils.md) &) = delete<br> |
|  [**VectorUtils**](classSR__UTILS__NS_1_1VectorUtils.md) | [**operator=**](#function-operator) ([**VectorUtils**](classSR__UTILS__NS_1_1VectorUtils.md) &) = delete<br> |
|   | [**~VectorUtils**](#function-vectorutils) () = delete<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  std::vector&lt; B &gt; | [**Cast**](#function-cast) (const std::vector&lt; A &gt; & source) <br> |
|  std::vector&lt; T &gt; | [**Combine**](#function-combine) (const std::vector&lt; T &gt; & A, const std::vector&lt; T &gt; & B) <br> |
|  std::string | [**Merge**](#function-merge) (const std::vector&lt; std::string &gt; & lines) <br> |


























## Public Functions Documentation




### function Contains 

```C++
template<typename T>
inline bool SR_UTILS_NS::VectorUtils::Contains (
    const std::vector< T > & v,
    const T & value
) 
```




<hr>



### function InsertSorted 

```C++
template<typename T>
inline void SR_UTILS_NS::VectorUtils::InsertSorted (
    std::vector< T > & v,
    const T & value
) 
```




<hr>



### function VectorUtils [1/2]

```C++
SR_UTILS_NS::VectorUtils::VectorUtils () = delete
```




<hr>



### function VectorUtils [2/2]

```C++
SR_UTILS_NS::VectorUtils::VectorUtils (
    VectorUtils &
) = delete
```




<hr>



### function operator= 

```C++
VectorUtils SR_UTILS_NS::VectorUtils::operator= (
    VectorUtils &
) = delete
```




<hr>



### function ~VectorUtils 

```C++
SR_UTILS_NS::VectorUtils::~VectorUtils () = delete
```




<hr>
## Public Static Functions Documentation




### function Cast 

```C++
template<typename A, typename B>
static inline std::vector< B > SR_UTILS_NS::VectorUtils::Cast (
    const std::vector< A > & source
) 
```




<hr>



### function Combine 

```C++
template<typename T>
static inline std::vector< T > SR_UTILS_NS::VectorUtils::Combine (
    const std::vector< T > & A,
    const std::vector< T > & B
) 
```




<hr>



### function Merge 

```C++
static inline std::string SR_UTILS_NS::VectorUtils::Merge (
    const std::vector< std::string > & lines
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Common/VectorUtils.h`

