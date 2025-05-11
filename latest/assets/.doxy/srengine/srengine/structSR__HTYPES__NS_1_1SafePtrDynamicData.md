

# Struct SR\_HTYPES\_NS::SafePtrDynamicData



[**ClassList**](annotated.md) **>** [**SR\_HTYPES\_NS**](namespaceSR__HTYPES__NS.md) **>** [**SafePtrDynamicData**](structSR__HTYPES__NS_1_1SafePtrDynamicData.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  std::atomic&lt; bool &gt; | [**m\_lock**](#variable-m_lock)  <br> |
|  std::atomic&lt; uint32\_t &gt; | [**m\_lockCount**](#variable-m_lockcount)  <br> |
|  std::atomic&lt; std::thread::id &gt; | [**m\_owner**](#variable-m_owner)  <br> |
|  std::atomic&lt; uint32\_t &gt; | [**m\_useCount**](#variable-m_usecount)  <br> |
|  bool | [**m\_valid**](#variable-m_valid)   = `false`<br> |












































## Public Attributes Documentation




### variable m\_lock 

```C++
std::atomic<bool> SR_HTYPES_NS::SafePtrDynamicData::m_lock;
```




<hr>



### variable m\_lockCount 

```C++
std::atomic<uint32_t> SR_HTYPES_NS::SafePtrDynamicData::m_lockCount;
```




<hr>



### variable m\_owner 

```C++
std::atomic<std::thread::id> SR_HTYPES_NS::SafePtrDynamicData::m_owner;
```




<hr>



### variable m\_useCount 

```C++
std::atomic<uint32_t> SR_HTYPES_NS::SafePtrDynamicData::m_useCount;
```




<hr>



### variable m\_valid 

```C++
bool SR_HTYPES_NS::SafePtrDynamicData::m_valid;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Types/SafePointer.h`

