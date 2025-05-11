

# File Allocator.h



[**FileList**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Memory**](dir_6c2eca2af3b09130c469ec03e9c2b107.md) **>** [**Allocator.h**](Allocator_8h.md)

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
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Memory/Allocator.h`

