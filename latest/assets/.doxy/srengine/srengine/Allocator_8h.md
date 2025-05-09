

# File Allocator.h



[**FileList**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Memory**](dir_a7ee2ebe23408af25e9b8f5a8e783a39.md) **>** [**Allocator.h**](Allocator_8h.md)

[Go to the source code of this file](Allocator_8h_source.md)








































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**SRDelete**](#function-srdelete) (T \* pObject) <br> |
|  void | [**SRFree**](#function-srfree) (void \* pMemory) <br> |
|  void \* | [**SRMalloc**](#function-srmalloc) (SR\_UTILS\_NS::SizeType size) <br> |
|  T \* | [**SRNew**](#function-srnew) (Args &&... args) <br> |
|  void \* | [**SRReAlloc**](#function-srrealloc) (void \* pMemory, SR\_UTILS\_NS::SizeType size) <br> |
|  void | [**operator delete**](#function-operator-delete) (void \* pMemory) noexcept<br> |
|  void | [**operator delete[]**](#function-operator-delete[]) (void \* pMemory) noexcept<br> |
|  void \* | [**operator new**](#function-operator-new) (SR\_UTILS\_NS::SizeType size) <br> |
|  void \* | [**operator new[]**](#function-operator-new[]) (SR\_UTILS\_NS::SizeType size) <br> |




























## Public Functions Documentation




### function SRDelete 

```C++
template<typename T>
void SRDelete (
    T * pObject
) 
```




<hr>



### function SRFree 

```C++
void SRFree (
    void * pMemory
) 
```




<hr>



### function SRMalloc 

```C++
void * SRMalloc (
    SR_UTILS_NS::SizeType size
) 
```




<hr>



### function SRNew 

```C++
template<typename T, typename... Args>
T * SRNew (
    Args &&... args
) 
```




<hr>



### function SRReAlloc 

```C++
void * SRReAlloc (
    void * pMemory,
    SR_UTILS_NS::SizeType size
) 
```




<hr>



### function operator delete 

```C++
void operator delete (
    void * pMemory
) noexcept
```




<hr>



### function operator delete[] 

```C++
void operator delete[] (
    void * pMemory
) noexcept
```




<hr>



### function operator new 

```C++
void * operator new (
    SR_UTILS_NS::SizeType size
) 
```




<hr>



### function operator new[] 

```C++
void * operator new[] (
    SR_UTILS_NS::SizeType size
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Memory/Allocator.h`

