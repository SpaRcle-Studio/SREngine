

# Struct SR\_GRAPH\_NS::SDF::Grid



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**SDF**](namespaceSR__GRAPH__NS_1_1SDF.md) **>** [**Grid**](structSR__GRAPH__NS_1_1SDF_1_1Grid.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  [**Point**](structSR__GRAPH__NS_1_1SDF_1_1Point.md) \* | [**grid**](#variable-grid)  <br> |
|  int32\_t | [**h**](#variable-h)  <br> |
|  int32\_t | [**w**](#variable-w)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**GenerateSDF**](#function-generatesdf) () const<br> |
|  SR\_NODISCARD [**Point**](structSR__GRAPH__NS_1_1SDF_1_1Point.md) | [**Get**](#function-get) (int32\_t x, int32\_t y) const<br> |
|   | [**Grid**](#function-grid) (int32\_t width, int32\_t height) <br> |
|  void | [**Put**](#function-put) (int32\_t x, int32\_t y, const [**Point**](structSR__GRAPH__NS_1_1SDF_1_1Point.md) & p) const<br> |
|   | [**~Grid**](#function-grid) () <br> |




























## Public Attributes Documentation




### variable grid 

```C++
Point* SR_GRAPH_NS::SDF::Grid::grid;
```




<hr>



### variable h 

```C++
int32_t SR_GRAPH_NS::SDF::Grid::h;
```




<hr>



### variable w 

```C++
int32_t SR_GRAPH_NS::SDF::Grid::w;
```




<hr>
## Public Functions Documentation




### function GenerateSDF 

```C++
inline void SR_GRAPH_NS::SDF::Grid::GenerateSDF () const
```




<hr>



### function Get 

```C++
inline SR_NODISCARD Point SR_GRAPH_NS::SDF::Grid::Get (
    int32_t x,
    int32_t y
) const
```




<hr>



### function Grid 

```C++
inline SR_GRAPH_NS::SDF::Grid::Grid (
    int32_t width,
    int32_t height
) 
```




<hr>



### function Put 

```C++
inline void SR_GRAPH_NS::SDF::Grid::Put (
    int32_t x,
    int32_t y,
    const Point & p
) const
```




<hr>



### function ~Grid 

```C++
inline SR_GRAPH_NS::SDF::Grid::~Grid () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/Font/SDF.h`

