

# Class EvoScript::CastingGen



[**ClassList**](annotated.md) **>** [**EvoScript**](namespaceEvoScript.md) **>** [**CastingGen**](classEvoScript_1_1CastingGen.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**CastingGen**](#function-castinggen) ([**AddressTableGen**](classEvoScript_1_1AddressTableGen.md) \* addressTableGen) <br> |
|  bool | [**RegisterCast**](#function-registercast) (const std::function&lt; void([**EvoScript::IState**](classEvoScript_1_1IState.md) \*)&gt; & setter, const std::string & from, const std::string & to, CastingType type) <br> |
|  bool | [**Save**](#function-save) (const std::string & folder) <br> |




























## Public Functions Documentation




### function CastingGen 

```C++
inline explicit EvoScript::CastingGen::CastingGen (
    AddressTableGen * addressTableGen
) 
```




<hr>



### function RegisterCast 

```C++
bool EvoScript::CastingGen::RegisterCast (
    const std::function< void( EvoScript::IState *)> & setter,
    const std::string & from,
    const std::string & to,
    CastingType type
) 
```




<hr>



### function Save 

```C++
bool EvoScript::CastingGen::Save (
    const std::string & folder
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Scripting/inc/Scripting/Old/Compilation/Casting.h`

