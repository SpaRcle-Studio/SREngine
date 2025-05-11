

# Class SR\_HTYPES\_NS::NodeDictionary

**template &lt;typename T&gt;**



[**ClassList**](annotated.md) **>** [**SR\_HTYPES\_NS**](namespaceSR__HTYPES__NS.md) **>** [**NodeDictionary**](classSR__HTYPES__NS_1_1NodeDictionary.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**Insert**](#function-insert) (T \* pKey, uint64\_t keySize, T \* pValue, uint64\_t valueSize) <br> |
|  SR\_NODISCARD T \* | [**Search**](#function-search) (T \* pKey, uint64\_t keySize) const<br> |


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




### function Insert 

```C++
void SR_HTYPES_NS::NodeDictionary::Insert (
    T * pKey,
    uint64_t keySize,
    T * pValue,
    uint64_t valueSize
) 
```




<hr>



### function Search 

```C++
SR_NODISCARD T * SR_HTYPES_NS::NodeDictionary::Search (
    T * pKey,
    uint64_t keySize
) const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Types/NodeDictionary.h`

