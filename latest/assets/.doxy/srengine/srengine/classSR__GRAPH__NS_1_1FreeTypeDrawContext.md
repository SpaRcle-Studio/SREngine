

# Class SR\_GRAPH\_NS::FreeTypeDrawContext



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**FreeTypeDrawContext**](classSR__GRAPH__NS_1_1FreeTypeDrawContext.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**Align**](#function-align) (int align) <br> |
|  SR\_NODISCARD uint8\_t \* | [**Bitmap**](#function-bitmap) () noexcept<br> |
|   | [**FreeTypeDrawContext**](#function-freetypedrawcontext-12) () = default<br> |
|   | [**FreeTypeDrawContext**](#function-freetypedrawcontext-22) (const [**FreeTypeDrawContext**](classSR__GRAPH__NS_1_1FreeTypeDrawContext.md) &) = delete<br> |
|  SR\_NODISCARD uint32\_t | [**Height**](#function-height) () noexcept const<br> |
|  void | [**NextLine**](#function-nextline) (int valign) <br> |
|  SR\_NODISCARD uint32\_t | [**Width**](#function-width) () noexcept const<br> |
|  [**FreeTypeDrawContext**](classSR__GRAPH__NS_1_1FreeTypeDrawContext.md) & | [**operator=**](#function-operator) (const [**FreeTypeDrawContext**](classSR__GRAPH__NS_1_1FreeTypeDrawContext.md) &) = delete<br> |
|   | [**~FreeTypeDrawContext**](#function-freetypedrawcontext) () override<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
















































## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |






## Public Functions Documentation




### function Align 

```C++
inline void SR_GRAPH_NS::FreeTypeDrawContext::Align (
    int align
) 
```




<hr>



### function Bitmap 

```C++
inline SR_NODISCARD uint8_t * SR_GRAPH_NS::FreeTypeDrawContext::Bitmap () noexcept
```




<hr>



### function FreeTypeDrawContext [1/2]

```C++
SR_GRAPH_NS::FreeTypeDrawContext::FreeTypeDrawContext () = default
```




<hr>



### function FreeTypeDrawContext [2/2]

```C++
SR_GRAPH_NS::FreeTypeDrawContext::FreeTypeDrawContext (
    const FreeTypeDrawContext &
) = delete
```




<hr>



### function Height 

```C++
inline SR_NODISCARD uint32_t SR_GRAPH_NS::FreeTypeDrawContext::Height () noexcept const
```




<hr>



### function NextLine 

```C++
inline void SR_GRAPH_NS::FreeTypeDrawContext::NextLine (
    int valign
) 
```




<hr>



### function Width 

```C++
inline SR_NODISCARD uint32_t SR_GRAPH_NS::FreeTypeDrawContext::Width () noexcept const
```




<hr>



### function operator= 

```C++
FreeTypeDrawContext & SR_GRAPH_NS::FreeTypeDrawContext::operator= (
    const FreeTypeDrawContext &
) = delete
```




<hr>



### function ~FreeTypeDrawContext 

```C++
SR_GRAPH_NS::FreeTypeDrawContext::~FreeTypeDrawContext () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Font/FreeTypeDrawContext.h`

