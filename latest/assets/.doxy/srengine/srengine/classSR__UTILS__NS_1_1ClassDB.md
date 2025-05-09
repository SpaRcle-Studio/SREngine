

# Class SR\_UTILS\_NS::ClassDB



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**ClassDB**](classSR__UTILS__NS_1_1ClassDB.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md),  [SR\_UTILS\_NS::NonMovable](classSR__UTILS__NS_1_1NonMovable.md)










































































## Public Functions

| Type | Name |
| ---: | :--- |
|  bool | [**RegisterInheritance**](#function-registerinheritance) ([**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) className, [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) inherits) <br> |
|  bool | [**RegisterNewClass**](#function-registernewclass) ([**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) className) <br>_RegisterClass conflicts with fucking WinAPI macroses._  |
|  bool | [**RegisterProperty**](#function-registerproperty) ([**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) className, [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) propertyType, [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) propertyName) <br> |
|  void | [**ResolveInheritance**](#function-resolveinheritance) () <br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |


## Public Functions inherited from SR_UTILS_NS::NonMovable

See [SR\_UTILS\_NS::NonMovable](classSR__UTILS__NS_1_1NonMovable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonMovable**](classSR__UTILS__NS_1_1NonMovable.md#function-nonmovable-22) ([**NonMovable**](classSR__UTILS__NS_1_1NonMovable.md) &&) = delete<br> |
| virtual [**NonMovable**](classSR__UTILS__NS_1_1NonMovable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonMovable.md#function-operator) ([**NonMovable**](classSR__UTILS__NS_1_1NonMovable.md) &&) = delete<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**ClassDB**](classSR__UTILS__NS_1_1ClassDB.md) & | [**Instance**](#function-instance) () <br> |




































































## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |


## Protected Functions inherited from SR_UTILS_NS::NonMovable

See [SR\_UTILS\_NS::NonMovable](classSR__UTILS__NS_1_1NonMovable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonMovable**](classSR__UTILS__NS_1_1NonMovable.md#function-nonmovable-12) () <br> |
| virtual  | [**~NonMovable**](classSR__UTILS__NS_1_1NonMovable.md#function-nonmovable) () <br> |








## Public Functions Documentation




### function RegisterInheritance 

```C++
bool SR_UTILS_NS::ClassDB::RegisterInheritance (
    StringAtom className,
    StringAtom inherits
) 
```




<hr>



### function RegisterNewClass 

_RegisterClass conflicts with fucking WinAPI macroses._ 
```C++
bool SR_UTILS_NS::ClassDB::RegisterNewClass (
    StringAtom className
) 
```




<hr>



### function RegisterProperty 

```C++
bool SR_UTILS_NS::ClassDB::RegisterProperty (
    StringAtom className,
    StringAtom propertyType,
    StringAtom propertyName
) 
```




<hr>



### function ResolveInheritance 

```C++
void SR_UTILS_NS::ClassDB::ResolveInheritance () 
```




<hr>
## Public Static Functions Documentation




### function Instance 

```C++
static ClassDB & SR_UTILS_NS::ClassDB::Instance () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/TypeTraits/ClassDB.h`

