

# Class SR\_CORE\_NS::Commands::ComponentsChange



[**ClassList**](annotated.md) **>** [**SR\_CORE\_NS**](namespaceSR__CORE__NS.md) **>** [**Commands**](namespaceSR__CORE__NS_1_1Commands.md) **>** [**ComponentsChange**](classSR__CORE__NS_1_1Commands_1_1ComponentsChange.md)



[More...](#detailed-description)

* `#include <EngineCommands.h>`



Inherits the following classes: [SR\_CORE\_NS::Commands::IEngineReversibleCommand](classSR__CORE__NS_1_1Commands_1_1IEngineReversibleCommand.md)
















## Public Types inherited from SR_CORE_NS::Commands::IEngineReversibleCommand

See [SR\_CORE\_NS::Commands::IEngineReversibleCommand](classSR__CORE__NS_1_1Commands_1_1IEngineReversibleCommand.md)

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Engine**](classSR__CORE__NS_1_1Engine.md) &gt; | [**EnginePtr**](classSR__CORE__NS_1_1Commands_1_1IEngineReversibleCommand.md#typedef-engineptr)  <br> |




























## Public Static Attributes inherited from SR_UTILS_NS::ICommand

See [SR\_UTILS\_NS::ICommand](classSR__UTILS__NS_1_1ICommand.md)

| Type | Name |
| ---: | :--- |
|  auto | [**DATA\_ID**](classSR__UTILS__NS_1_1ICommand.md#variable-data_id)   = `SR\_UTILS\_NS::SerializationId::Create("command")`<br> |


















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ComponentsChange**](#function-componentschange) (const EnginePtr & pEngine, const SR\_UTILS\_NS::IComponentable::Ptr & pComponentable, SR\_UTILS\_NS::ISerializer::UniquePtr pOld) <br> |
| virtual bool | [**Redo**](#function-redo) () override<br> |
| virtual bool | [**Undo**](#function-undo) () override<br> |


## Public Functions inherited from SR_CORE_NS::Commands::IEngineReversibleCommand

See [SR\_CORE\_NS::Commands::IEngineReversibleCommand](classSR__CORE__NS_1_1Commands_1_1IEngineReversibleCommand.md)

| Type | Name |
| ---: | :--- |
|   | [**IEngineReversibleCommand**](classSR__CORE__NS_1_1Commands_1_1IEngineReversibleCommand.md#function-ienginereversiblecommand) (EnginePtr pEngine) <br> |


## Public Functions inherited from SR_UTILS_NS::ReversibleCommand

See [SR\_UTILS\_NS::ReversibleCommand](classSR__UTILS__NS_1_1ReversibleCommand.md)

| Type | Name |
| ---: | :--- |
| virtual std::string | [**GetName**](classSR__UTILS__NS_1_1ReversibleCommand.md#function-getname) () <br> |
| virtual bool | [**Load**](classSR__UTILS__NS_1_1ReversibleCommand.md#function-load) (const [**Xml::Node**](classSR__UTILS__NS_1_1Xml_1_1Node.md) & node) <br> |
| virtual bool | [**Redo**](classSR__UTILS__NS_1_1ReversibleCommand.md#function-redo) () = 0<br> |
|   | [**ReversibleCommand**](classSR__UTILS__NS_1_1ReversibleCommand.md#function-reversiblecommand) () = default<br> |
| virtual SR\_NODISCARD [**Xml::Node**](classSR__UTILS__NS_1_1Xml_1_1Node.md) | [**Save**](classSR__UTILS__NS_1_1ReversibleCommand.md#function-save) () const<br> |
| virtual bool | [**Undo**](classSR__UTILS__NS_1_1ReversibleCommand.md#function-undo) () = 0<br> |
|   | [**~ReversibleCommand**](classSR__UTILS__NS_1_1ReversibleCommand.md#function-reversiblecommand) () override<br> |


## Public Functions inherited from SR_UTILS_NS::ICommand

See [SR\_UTILS\_NS::ICommand](classSR__UTILS__NS_1_1ICommand.md)

| Type | Name |
| ---: | :--- |
|   | [**ICommand**](classSR__UTILS__NS_1_1ICommand.md#function-icommand) () = default<br> |
| virtual  | [**~ICommand**](classSR__UTILS__NS_1_1ICommand.md#function-icommand) () = default<br> |




























## Protected Attributes inherited from SR_CORE_NS::Commands::IEngineReversibleCommand

See [SR\_CORE\_NS::Commands::IEngineReversibleCommand](classSR__CORE__NS_1_1Commands_1_1IEngineReversibleCommand.md)

| Type | Name |
| ---: | :--- |
|  [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Engine**](classSR__CORE__NS_1_1Engine.md) &gt; | [**m\_engine**](classSR__CORE__NS_1_1Commands_1_1IEngineReversibleCommand.md#variable-m_engine)  <br> |
|  [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**SR\_WORLD\_NS::Scene**](classSR__WORLD__NS_1_1Scene.md) &gt; | [**m\_scene**](classSR__CORE__NS_1_1Commands_1_1IEngineReversibleCommand.md#variable-m_scene)  <br> |














































































## Detailed Description



 


    
## Public Functions Documentation




### function ComponentsChange 

```C++
inline SR_CORE_NS::Commands::ComponentsChange::ComponentsChange (
    const EnginePtr & pEngine,
    const SR_UTILS_NS::IComponentable::Ptr & pComponentable,
    SR_UTILS_NS::ISerializer::UniquePtr pOld
) 
```




<hr>



### function Redo 

```C++
virtual bool SR_CORE_NS::Commands::ComponentsChange::Redo () override
```



Implements [*SR\_UTILS\_NS::ReversibleCommand::Redo*](classSR__UTILS__NS_1_1ReversibleCommand.md#function-redo)


<hr>



### function Undo 

```C++
virtual bool SR_CORE_NS::Commands::ComponentsChange::Undo () override
```



Implements [*SR\_UTILS\_NS::ReversibleCommand::Undo*](classSR__UTILS__NS_1_1ReversibleCommand.md#function-undo)


<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/inc/Core/EngineCommands.h`

