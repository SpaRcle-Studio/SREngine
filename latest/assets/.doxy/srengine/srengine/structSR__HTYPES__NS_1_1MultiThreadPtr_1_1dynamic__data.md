

# Struct SR\_HTYPES\_NS::MultiThreadPtr::dynamic\_data



[**ClassList**](annotated.md) **>** [**dynamic\_data**](structSR__HTYPES__NS_1_1MultiThreadPtr_1_1dynamic__data.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  std::recursive\_mutex | [**m\_mutex**](#variable-m_mutex)  <br> |
|  std::atomic&lt; uint32\_t &gt; | [**m\_useCount**](#variable-m_usecount)  <br> |
|  bool | [**m\_valid**](#variable-m_valid)   = `{}`<br> |












































## Public Attributes Documentation




### variable m\_mutex 

```C++
std::recursive_mutex SR_HTYPES_NS::MultiThreadPtr< T >::dynamic_data::m_mutex;
```




<hr>



### variable m\_useCount 

```C++
std::atomic<uint32_t> SR_HTYPES_NS::MultiThreadPtr< T >::dynamic_data::m_useCount;
```




<hr>



### variable m\_valid 

```C++
bool SR_HTYPES_NS::MultiThreadPtr< T >::dynamic_data::m_valid;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Types/MultiThreadPtr.h`

