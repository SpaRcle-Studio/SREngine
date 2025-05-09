

# Class SR\_HTYPES\_NS::DictionaryEntry

**template &lt;typename T&gt;**



[**ClassList**](annotated.md) **>** [**SR\_HTYPES\_NS**](namespaceSR__HTYPES__NS.md) **>** [**DictionaryEntry**](classSR__HTYPES__NS_1_1DictionaryEntry.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**DictionaryEntry**](#function-dictionaryentry) (T \* pKey, uint64\_t keySize, T \* pValue, uint64\_t valueSize) <br> |
|  SR\_NODISCARD T \* | [**GetKey**](#function-getkey) () const<br> |
|  SR\_NODISCARD uint64\_t | [**GetKeySize**](#function-getkeysize) () const<br> |
|  SR\_NODISCARD T \* | [**GetValue**](#function-getvalue) () const<br> |
|  SR\_NODISCARD uint64\_t | [**GetValueSize**](#function-getvaluesize) () const<br> |
|   | [**~DictionaryEntry**](#function-dictionaryentry) () override<br> |


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




### function DictionaryEntry 

```C++
inline SR_HTYPES_NS::DictionaryEntry::DictionaryEntry (
    T * pKey,
    uint64_t keySize,
    T * pValue,
    uint64_t valueSize
) 
```




<hr>



### function GetKey 

```C++
inline SR_NODISCARD T * SR_HTYPES_NS::DictionaryEntry::GetKey () const
```




<hr>



### function GetKeySize 

```C++
inline SR_NODISCARD uint64_t SR_HTYPES_NS::DictionaryEntry::GetKeySize () const
```




<hr>



### function GetValue 

```C++
inline SR_NODISCARD T * SR_HTYPES_NS::DictionaryEntry::GetValue () const
```




<hr>



### function GetValueSize 

```C++
inline SR_NODISCARD uint64_t SR_HTYPES_NS::DictionaryEntry::GetValueSize () const
```




<hr>



### function ~DictionaryEntry 

```C++
inline SR_HTYPES_NS::DictionaryEntry::~DictionaryEntry () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Types/NodeDictionary.h`

