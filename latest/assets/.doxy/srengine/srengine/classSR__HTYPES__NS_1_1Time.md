

# Class SR\_HTYPES\_NS::Time



[**ClassList**](annotated.md) **>** [**SR\_HTYPES\_NS**](namespaceSR__HTYPES__NS.md) **>** [**Time**](classSR__HTYPES__NS_1_1Time.md)








Inherits the following classes: Singleton< Time >














## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::chrono::high\_resolution\_clock | [**ClockT**](#typedef-clockt)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD uint64\_t | [**Clock**](#function-clock) () noexcept const<br> |
|  SR\_NODISCARD uint64\_t | [**Count**](#function-count) () noexcept const<br> |
|  SR\_NODISCARD float\_t | [**FClock**](#function-fclock) () noexcept const<br> |
|  SR\_NODISCARD TimePointType | [**Now**](#function-now) () noexcept const<br> |
|  void | [**Update**](#function-update) () <br> |




























## Public Types Documentation




### typedef ClockT 

```C++
using SR_HTYPES_NS::Time::ClockT =  std::chrono::high_resolution_clock;
```




<hr>
## Public Functions Documentation




### function Clock 

```C++
inline SR_NODISCARD uint64_t SR_HTYPES_NS::Time::Clock () noexcept const
```




<hr>



### function Count 

```C++
inline SR_NODISCARD uint64_t SR_HTYPES_NS::Time::Count () noexcept const
```




<hr>



### function FClock 

```C++
inline SR_NODISCARD float_t SR_HTYPES_NS::Time::FClock () noexcept const
```




<hr>



### function Now 

```C++
inline SR_NODISCARD TimePointType SR_HTYPES_NS::Time::Now () noexcept const
```




<hr>



### function Update 

```C++
inline void SR_HTYPES_NS::Time::Update () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Types/Time.h`

