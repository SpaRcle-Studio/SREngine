

# Class SR\_SRSL\_NS::SRSLTypeInfo



[**ClassList**](annotated.md) **>** [**SR\_SRSL\_NS**](namespaceSR__SRSL__NS.md) **>** [**SRSLTypeInfo**](classSR__SRSL__NS_1_1SRSLTypeInfo.md)








Inherits the following classes: [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md)






























































































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD uint64\_t | [**GetAlignedTypeSize**](#function-getalignedtypesize-12) (const std::string & code, const SRSLAnalyzedTree::Ptr & pAnalyzedTree) <br> |
|  SR\_NODISCARD uint64\_t | [**GetAlignedTypeSize**](#function-getalignedtypesize-22) (const [**SRSLExpr**](classSR__SRSL__NS_1_1SRSLExpr.md) \* pExpr, const SRSLAnalyzedTree::Ptr & pAnalyzedTree) <br> |
|  SR\_NODISCARD std::vector&lt; uint64\_t &gt; | [**GetDimension**](#function-getdimension-12) (const std::string & code, const SRSLAnalyzedTree::Ptr & pAnalyzedTree) <br> |
|  SR\_NODISCARD std::vector&lt; uint64\_t &gt; | [**GetDimension**](#function-getdimension-22) (const [**SRSLExpr**](classSR__SRSL__NS_1_1SRSLExpr.md) \* pExpr, const SRSLAnalyzedTree::Ptr & pAnalyzedTree) <br> |
|  SR\_NODISCARD uint64\_t | [**GetStructSize**](#function-getstructsize) (const std::string & name, const SRSLAnalyzedTree::Ptr & pAnalyzedTree) <br> |
|  SR\_NODISCARD std::string | [**GetTypeName**](#function-gettypename-12) (const std::string & code) <br> |
|  SR\_NODISCARD std::string | [**GetTypeName**](#function-gettypename-22) (const [**SRSLExpr**](classSR__SRSL__NS_1_1SRSLExpr.md) \* pExpr) <br> |
|  SR\_NODISCARD uint64\_t | [**GetTypeSize**](#function-gettypesize-12) (const std::string & code, const SRSLAnalyzedTree::Ptr & pAnalyzedTree) <br> |
|  SR\_NODISCARD uint64\_t | [**GetTypeSize**](#function-gettypesize-22) (const [**SRSLExpr**](classSR__SRSL__NS_1_1SRSLExpr.md) \* pExpr, const SRSLAnalyzedTree::Ptr & pAnalyzedTree) <br> |
|  SR\_NODISCARD ShaderVarType | [**StringToType**](#function-stringtotype) (const std::string & str) <br> |




## Public Functions inherited from SR_UTILS_NS::SingletonBase

See [SR\_UTILS\_NS::SingletonBase](classSR__UTILS__NS_1_1SingletonBase.md)

| Type | Name |
| ---: | :--- |
|   | [**~SingletonBase**](classSR__UTILS__NS_1_1SingletonBase.md#function-singletonbase) () override<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |




## Public Static Functions inherited from SR_UTILS_NS::Singleton

See [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md)

| Type | Name |
| ---: | :--- |
|  SR\_MAYBE\_UNUSED void | [**DestroySingleton**](classSR__UTILS__NS_1_1Singleton.md#function-destroysingleton) () <br> |
|  SR\_MAYBE\_UNUSED std::recursive\_mutex & | [**GetMutex**](classSR__UTILS__NS_1_1Singleton.md#function-getmutex) () noexcept<br> |
|  SR\_MAYBE\_UNUSED T & | [**Instance**](classSR__UTILS__NS_1_1Singleton.md#function-instance) () noexcept<br> |
|  SR\_MAYBE\_UNUSED bool | [**IsSingletonInitialized**](classSR__UTILS__NS_1_1Singleton.md#function-issingletoninitialized) () noexcept<br> |
|  SR\_MAYBE\_UNUSED void | [**LockSingleton**](classSR__UTILS__NS_1_1Singleton.md#function-locksingleton) () noexcept<br> |
|  SR\_MAYBE\_UNUSED static SR\_NODISCARD [**SR\_HTYPES\_NS::SingletonRecursiveLockGuard**](classSR__HTYPES__NS_1_1SingletonRecursiveLockGuard.md)&lt; [**Singleton**](classSR__UTILS__NS_1_1Singleton.md)&lt; T &gt; \* &gt; | [**ScopeLockSingleton**](classSR__UTILS__NS_1_1Singleton.md#function-scopelocksingleton) () <br> |
|  SR\_MAYBE\_UNUSED void | [**UnlockSingleton**](classSR__UTILS__NS_1_1Singleton.md#function-unlocksingleton) () noexcept<br> |


























## Protected Attributes inherited from SR_UTILS_NS::SingletonBase

See [SR\_UTILS\_NS::SingletonBase](classSR__UTILS__NS_1_1SingletonBase.md)

| Type | Name |
| ---: | :--- |
|  std::recursive\_mutex | [**m\_mutex**](classSR__UTILS__NS_1_1SingletonBase.md#variable-m_mutex)  <br> |






























































## Protected Functions inherited from SR_UTILS_NS::Singleton

See [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md)

| Type | Name |
| ---: | :--- |
|   | [**Singleton**](classSR__UTILS__NS_1_1Singleton.md#function-singleton) () <br> |
|   | [**~Singleton**](classSR__UTILS__NS_1_1Singleton.md#function-singleton) () override<br> |


## Protected Functions inherited from SR_UTILS_NS::SingletonBase

See [SR\_UTILS\_NS::SingletonBase](classSR__UTILS__NS_1_1SingletonBase.md)

| Type | Name |
| ---: | :--- |
| virtual [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetSingletonName**](classSR__UTILS__NS_1_1SingletonBase.md#function-getsingletonname) () noexcept const = 0<br> |
| virtual void | [**InitSingleton**](classSR__UTILS__NS_1_1SingletonBase.md#function-initsingleton) () <br> |
| virtual bool | [**IsSingletonCanBeDestroyed**](classSR__UTILS__NS_1_1SingletonBase.md#function-issingletoncanbedestroyed) () const<br> |
| virtual void | [**OnSingletonDestroy**](classSR__UTILS__NS_1_1SingletonBase.md#function-onsingletondestroy) () <br> |
|   | [**SingletonBase**](classSR__UTILS__NS_1_1SingletonBase.md#function-singletonbase) () <br> |


## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |










## Public Functions Documentation




### function GetAlignedTypeSize [1/2]

```C++
SR_NODISCARD uint64_t SR_SRSL_NS::SRSLTypeInfo::GetAlignedTypeSize (
    const std::string & code,
    const SRSLAnalyzedTree::Ptr & pAnalyzedTree
) 
```




<hr>



### function GetAlignedTypeSize [2/2]

```C++
SR_NODISCARD uint64_t SR_SRSL_NS::SRSLTypeInfo::GetAlignedTypeSize (
    const SRSLExpr * pExpr,
    const SRSLAnalyzedTree::Ptr & pAnalyzedTree
) 
```




<hr>



### function GetDimension [1/2]

```C++
SR_NODISCARD std::vector< uint64_t > SR_SRSL_NS::SRSLTypeInfo::GetDimension (
    const std::string & code,
    const SRSLAnalyzedTree::Ptr & pAnalyzedTree
) 
```




<hr>



### function GetDimension [2/2]

```C++
SR_NODISCARD std::vector< uint64_t > SR_SRSL_NS::SRSLTypeInfo::GetDimension (
    const SRSLExpr * pExpr,
    const SRSLAnalyzedTree::Ptr & pAnalyzedTree
) 
```




<hr>



### function GetStructSize 

```C++
SR_NODISCARD uint64_t SR_SRSL_NS::SRSLTypeInfo::GetStructSize (
    const std::string & name,
    const SRSLAnalyzedTree::Ptr & pAnalyzedTree
) 
```




<hr>



### function GetTypeName [1/2]

```C++
SR_NODISCARD std::string SR_SRSL_NS::SRSLTypeInfo::GetTypeName (
    const std::string & code
) 
```




<hr>



### function GetTypeName [2/2]

```C++
SR_NODISCARD std::string SR_SRSL_NS::SRSLTypeInfo::GetTypeName (
    const SRSLExpr * pExpr
) 
```




<hr>



### function GetTypeSize [1/2]

```C++
SR_NODISCARD uint64_t SR_SRSL_NS::SRSLTypeInfo::GetTypeSize (
    const std::string & code,
    const SRSLAnalyzedTree::Ptr & pAnalyzedTree
) 
```




<hr>



### function GetTypeSize [2/2]

```C++
SR_NODISCARD uint64_t SR_SRSL_NS::SRSLTypeInfo::GetTypeSize (
    const SRSLExpr * pExpr,
    const SRSLAnalyzedTree::Ptr & pAnalyzedTree
) 
```




<hr>



### function StringToType 

```C++
SR_NODISCARD ShaderVarType SR_SRSL_NS::SRSLTypeInfo::StringToType (
    const std::string & str
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/SRSL/TypeInfo.h`

