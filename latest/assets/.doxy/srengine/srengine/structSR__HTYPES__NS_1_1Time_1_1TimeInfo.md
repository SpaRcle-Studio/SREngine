

# Struct SR\_HTYPES\_NS::Time::TimeInfo



[**ClassList**](annotated.md) **>** [**TimeInfo**](structSR__HTYPES__NS_1_1Time_1_1TimeInfo.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  uint64\_t | [**m\_clock**](#variable-m_clock)   = `0`<br> |
|  TimePointType | [**m\_point**](#variable-m_point)   = `TimePointType()`<br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**TimeInfo**](#function-timeinfo-13) () = default<br> |
|   | [**TimeInfo**](#function-timeinfo-23) (TimePointType point, uint64\_t clock) <br> |
|   | [**TimeInfo**](#function-timeinfo-33) (const TimeInfo & other) = default<br> |
|  TimeInfo & | [**operator=**](#function-operator) (const TimeInfo & other) = default<br> |




























## Public Attributes Documentation




### variable m\_clock 

```C++
uint64_t SR_HTYPES_NS::Time::TimeInfo::m_clock;
```




<hr>



### variable m\_point 

```C++
TimePointType SR_HTYPES_NS::Time::TimeInfo::m_point;
```




<hr>
## Public Functions Documentation




### function TimeInfo [1/3]

```C++
TimeInfo::TimeInfo () = default
```




<hr>



### function TimeInfo [2/3]

```C++
inline TimeInfo::TimeInfo (
    TimePointType point,
    uint64_t clock
) 
```




<hr>



### function TimeInfo [3/3]

```C++
TimeInfo::TimeInfo (
    const TimeInfo & other
) = default
```




<hr>



### function operator= 

```C++
TimeInfo & TimeInfo::operator= (
    const TimeInfo & other
) = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Types/Time.h`

