

# Namespace SR\_SCRIPTING\_NS



[**Namespace List**](namespaces.md) **>** [**SR\_SCRIPTING\_NS**](namespaceSR__SCRIPTING__NS.md)




















## Classes

| Type | Name |
| ---: | :--- |
| class | [**Behaviour**](classSR__SCRIPTING__NS_1_1Behaviour.md) <br> |
| class | [**Compiler**](classSR__SCRIPTING__NS_1_1Compiler.md) <br> |
| class | [**EvoBehaviour**](classSR__SCRIPTING__NS_1_1EvoBehaviour.md) <br> |
| class | [**EvoCompiler**](classSR__SCRIPTING__NS_1_1EvoCompiler.md) <br> |
| class | [**EvoScriptImpl**](classSR__SCRIPTING__NS_1_1EvoScriptImpl.md) <br> |
| class | [**EvoScriptManager**](classSR__SCRIPTING__NS_1_1EvoScriptManager.md) <br> |
| class | [**EvoScriptResourceReloader**](classSR__SCRIPTING__NS_1_1EvoScriptResourceReloader.md) <br> |
| class | [**GlobalEvoCompiler**](classSR__SCRIPTING__NS_1_1GlobalEvoCompiler.md) <br> |
| class | [**IRawBehaviour**](classSR__SCRIPTING__NS_1_1IRawBehaviour.md) <br> |
| class | [**ScriptHolder**](classSR__SCRIPTING__NS_1_1ScriptHolder.md) <br> |


## Public Types

| Type | Name |
| ---: | :--- |
| typedef void(\* | [**CollisionFnPtr**](#typedef-collisionfnptr)  <br> |
| enum  | [**ScriptType**](#enum-scripttype)  <br> |
| typedef std::chrono::high\_resolution\_clock::time\_point | [**Time**](#typedef-time)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**RunMonoTest**](#function-runmonotest) () <br> |




























## Public Types Documentation




### typedef CollisionFnPtr 

```C++
typedef void(* SR_SCRIPTING_NS::CollisionFnPtr) (const SR_UTILS_NS::CollisionData &data);
```




<hr>



### enum ScriptType 

```C++
enum SR_SCRIPTING_NS::ScriptType {
    EvoScript,
    Lua
};
```




<hr>



### typedef Time 

```C++
typedef std::chrono::high_resolution_clock::time_point SR_SCRIPTING_NS::Time;
```




<hr>
## Public Functions Documentation




### function RunMonoTest 

```C++
void SR_SCRIPTING_NS::RunMonoTest () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Scripting/inc/Scripting/Base/Behaviour.h`

