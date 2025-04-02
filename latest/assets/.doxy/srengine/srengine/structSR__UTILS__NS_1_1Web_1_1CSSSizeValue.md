

# Struct SR\_UTILS\_NS::Web::CSSSizeValue



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**Web**](namespaceSR__UTILS__NS_1_1Web.md) **>** [**CSSSizeValue**](structSR__UTILS__NS_1_1Web_1_1CSSSizeValue.md)










Inherited by the following classes: [SR\_UTILS\_NS::Web::CSSOptional](classSR__UTILS__NS_1_1Web_1_1CSSOptional.md)












## Public Types

| Type | Name |
| ---: | :--- |
| enum uint8\_t | [**Unit**](#enum-unit)  <br> |




## Public Attributes

| Type | Name |
| ---: | :--- |
|  union [**SR\_UTILS\_NS::Web::CSSSizeValue**](structSR__UTILS__NS_1_1Web_1_1CSSSizeValue.md) | [**CSSSizeValue**](#variable-csssizevalue)  <br> |
|  bool | [**autoValue**](#variable-autovalue)   = `false`<br> |
|  float\_t | [**deg**](#variable-deg)  <br> |
|  int16\_t | [**dpi**](#variable-dpi)  <br> |
|  float\_t | [**percent**](#variable-percent)  <br> |
|  int16\_t | [**px**](#variable-px)   = `0`<br> |
|  enum SR\_UTILS\_NS::Web::CSSSizeValue::Unit | [**unit**](#variable-unit)   = `Unit::Px`<br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**CSSSizeValue**](#function-csssizevalue-15) () = default<br> |
|   | [**CSSSizeValue**](#function-csssizevalue-25) (const int32\_t px) <br> |
|   | [**CSSSizeValue**](#function-csssizevalue-35) (const int16\_t px) <br> |
|   | [**CSSSizeValue**](#function-csssizevalue-45) (const float\_t percent) <br> |
|   | [**CSSSizeValue**](#function-csssizevalue-55) (const float\_t v, const Unit unit) <br> |
|  SR\_NODISCARD SR\_MATH\_NS::Unit | [**CalculateValue**](#function-calculatevalue) (const SR\_MATH\_NS::Unit & parentPx) const<br> |
|  SR\_NODISCARD float\_t | [**GetDeg**](#function-getdeg) () const<br> |
|  SR\_NODISCARD uint16\_t | [**GetDpi**](#function-getdpi) () const<br> |
|  SR\_NODISCARD float\_t | [**GetPercent**](#function-getpercent) () const<br> |
|  SR\_NODISCARD uint16\_t | [**GetPx**](#function-getpx) () const<br> |
|  SR\_NODISCARD Unit | [**GetUnit**](#function-getunit) () const<br> |
|  void | [**SetDeg**](#function-setdeg) (const float\_t deg) <br> |
|  void | [**SetDpi**](#function-setdpi) (const int16\_t dpi) <br> |
|  void | [**SetPercent**](#function-setpercent) (const float\_t percent) <br> |
|  void | [**SetPx**](#function-setpx) (const int16\_t px) <br> |
|  SR\_NODISCARD std::string | [**ToString**](#function-tostring) () const<br> |
| virtual  | [**~CSSSizeValue**](#function-csssizevalue) () = default<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  std::optional&lt; [**CSSSizeValue**](structSR__UTILS__NS_1_1Web_1_1CSSSizeValue.md) &gt; | [**Parse**](#function-parse-12) (std::string\_view value) <br> |
|  void | [**Parse**](#function-parse-22) ([**CSSSizeValue**](structSR__UTILS__NS_1_1Web_1_1CSSSizeValue.md) & result, std::string\_view value) <br> |






















## Protected Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**OnChanged**](#function-onchanged) () <br> |




## Public Types Documentation




### enum Unit 

```C++
enum SR_UTILS_NS::Web::CSSSizeValue::Unit {
    Px,
    Percent,
    Dpi,
    Deg
};
```




<hr>
## Public Attributes Documentation




### variable CSSSizeValue 

```C++
union SR_UTILS_NS::Web::CSSSizeValue SR_UTILS_NS::Web::CSSSizeValue;
```




<hr>



### variable autoValue 

```C++
bool SR_UTILS_NS::Web::CSSSizeValue::autoValue;
```




<hr>



### variable deg 

```C++
float_t SR_UTILS_NS::Web::CSSSizeValue::deg;
```




<hr>



### variable dpi 

```C++
int16_t SR_UTILS_NS::Web::CSSSizeValue::dpi;
```




<hr>



### variable percent 

```C++
float_t SR_UTILS_NS::Web::CSSSizeValue::percent;
```




<hr>



### variable px 

```C++
int16_t SR_UTILS_NS::Web::CSSSizeValue::px;
```




<hr>



### variable unit 

```C++
enum SR_UTILS_NS::Web::CSSSizeValue::Unit SR_UTILS_NS::Web::CSSSizeValue::unit;
```




<hr>
## Public Functions Documentation




### function CSSSizeValue [1/5]

```C++
SR_UTILS_NS::Web::CSSSizeValue::CSSSizeValue () = default
```




<hr>



### function CSSSizeValue [2/5]

```C++
inline SR_UTILS_NS::Web::CSSSizeValue::CSSSizeValue (
    const int32_t px
) 
```




<hr>



### function CSSSizeValue [3/5]

```C++
inline SR_UTILS_NS::Web::CSSSizeValue::CSSSizeValue (
    const int16_t px
) 
```



NOLINT(google-explicit-constructor) 


        

<hr>



### function CSSSizeValue [4/5]

```C++
inline SR_UTILS_NS::Web::CSSSizeValue::CSSSizeValue (
    const float_t percent
) 
```



NOLINT(google-explicit-constructor) 


        

<hr>



### function CSSSizeValue [5/5]

```C++
inline SR_UTILS_NS::Web::CSSSizeValue::CSSSizeValue (
    const float_t v,
    const Unit unit
) 
```



NOLINT(google-explicit-constructor) 


        

<hr>



### function CalculateValue 

```C++
inline SR_NODISCARD SR_MATH_NS::Unit SR_UTILS_NS::Web::CSSSizeValue::CalculateValue (
    const SR_MATH_NS::Unit & parentPx
) const
```




<hr>



### function GetDeg 

```C++
inline SR_NODISCARD float_t SR_UTILS_NS::Web::CSSSizeValue::GetDeg () const
```




<hr>



### function GetDpi 

```C++
inline SR_NODISCARD uint16_t SR_UTILS_NS::Web::CSSSizeValue::GetDpi () const
```




<hr>



### function GetPercent 

```C++
inline SR_NODISCARD float_t SR_UTILS_NS::Web::CSSSizeValue::GetPercent () const
```




<hr>



### function GetPx 

```C++
inline SR_NODISCARD uint16_t SR_UTILS_NS::Web::CSSSizeValue::GetPx () const
```




<hr>



### function GetUnit 

```C++
inline SR_NODISCARD Unit SR_UTILS_NS::Web::CSSSizeValue::GetUnit () const
```




<hr>



### function SetDeg 

```C++
inline void SR_UTILS_NS::Web::CSSSizeValue::SetDeg (
    const float_t deg
) 
```




<hr>



### function SetDpi 

```C++
inline void SR_UTILS_NS::Web::CSSSizeValue::SetDpi (
    const int16_t dpi
) 
```




<hr>



### function SetPercent 

```C++
inline void SR_UTILS_NS::Web::CSSSizeValue::SetPercent (
    const float_t percent
) 
```




<hr>



### function SetPx 

```C++
inline void SR_UTILS_NS::Web::CSSSizeValue::SetPx (
    const int16_t px
) 
```




<hr>



### function ToString 

```C++
inline SR_NODISCARD std::string SR_UTILS_NS::Web::CSSSizeValue::ToString () const
```




<hr>



### function ~CSSSizeValue 

```C++
virtual SR_UTILS_NS::Web::CSSSizeValue::~CSSSizeValue () = default
```




<hr>
## Public Static Functions Documentation




### function Parse [1/2]

```C++
static inline std::optional< CSSSizeValue > SR_UTILS_NS::Web::CSSSizeValue::Parse (
    std::string_view value
) 
```




<hr>



### function Parse [2/2]

```C++
static inline void SR_UTILS_NS::Web::CSSSizeValue::Parse (
    CSSSizeValue & result,
    std::string_view value
) 
```




<hr>
## Protected Functions Documentation




### function OnChanged 

```C++
inline virtual void SR_UTILS_NS::Web::CSSSizeValue::OnChanged () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Web/CSS/CSSSizeValue.h`

