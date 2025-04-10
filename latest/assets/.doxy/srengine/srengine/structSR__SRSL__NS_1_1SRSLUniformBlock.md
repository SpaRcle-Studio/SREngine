

# Struct SR\_SRSL\_NS::SRSLUniformBlock



[**ClassList**](annotated.md) **>** [**SR\_SRSL\_NS**](namespaceSR__SRSL__NS.md) **>** [**SRSLUniformBlock**](structSR__SRSL__NS_1_1SRSLUniformBlock.md)




















## Classes

| Type | Name |
| ---: | :--- |
| struct | [**Field**](structSR__SRSL__NS_1_1SRSLUniformBlock_1_1Field.md) <br> |






## Public Attributes

| Type | Name |
| ---: | :--- |
|  uint64\_t | [**binding**](#variable-binding)   = `0`<br> |
|  std::vector&lt; [**Field**](structSR__SRSL__NS_1_1SRSLUniformBlock_1_1Field.md) &gt; | [**fields**](#variable-fields)  <br> |
|  bool | [**isCoherent**](#variable-iscoherent)   = `false`<br> |
|  std::optional&lt; bool &gt; | [**isReadOnly**](#variable-isreadonly)  <br> |
|  bool | [**isRestrict**](#variable-isrestrict)   = `false`<br> |
|  bool | [**isVolatile**](#variable-isvolatile)   = `false`<br>_true - read only, false - write only, nullopt - read/write_  |
|  uint64\_t | [**size**](#variable-size)   = `0`<br> |
|  std::set&lt; ShaderStage &gt; | [**stages**](#variable-stages)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**Align**](#function-align) (const SRSLAnalyzedTree::Ptr & pAnalyzedTree) <br> |




























## Public Attributes Documentation




### variable binding 

```C++
uint64_t SR_SRSL_NS::SRSLUniformBlock::binding;
```




<hr>



### variable fields 

```C++
std::vector<Field> SR_SRSL_NS::SRSLUniformBlock::fields;
```




<hr>



### variable isCoherent 

```C++
bool SR_SRSL_NS::SRSLUniformBlock::isCoherent;
```




<hr>



### variable isReadOnly 

```C++
std::optional<bool> SR_SRSL_NS::SRSLUniformBlock::isReadOnly;
```




<hr>



### variable isRestrict 

```C++
bool SR_SRSL_NS::SRSLUniformBlock::isRestrict;
```




<hr>



### variable isVolatile 

_true - read only, false - write only, nullopt - read/write_ 
```C++
bool SR_SRSL_NS::SRSLUniformBlock::isVolatile;
```




<hr>



### variable size 

```C++
uint64_t SR_SRSL_NS::SRSLUniformBlock::size;
```




<hr>



### variable stages 

```C++
std::set<ShaderStage> SR_SRSL_NS::SRSLUniformBlock::stages;
```




<hr>
## Public Functions Documentation




### function Align 

```C++
void SR_SRSL_NS::SRSLUniformBlock::Align (
    const SRSLAnalyzedTree::Ptr & pAnalyzedTree
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/SRSL/Shader.h`

