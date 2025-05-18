

# Class SR\_CORE\_NS::Commands::IEngineReversibleCommand



[**ClassList**](annotated.md) **>** [**SR\_CORE\_NS**](namespaceSR__CORE__NS.md) **>** [**Commands**](namespaceSR__CORE__NS_1_1Commands.md) **>** [**IEngineReversibleCommand**](classSR__CORE__NS_1_1Commands_1_1IEngineReversibleCommand.md)








Inherits the following classes: [SR\_UTILS\_NS::ReversibleCommand](classSR__UTILS__NS_1_1ReversibleCommand.md)


Inherited by the following classes: [SR\_CORE\_NS::Commands::ChangeHierarchySelected](classSR__CORE__NS_1_1Commands_1_1ChangeHierarchySelected.md),  [SR\_CORE\_NS::Commands::ComponentChange](classSR__CORE__NS_1_1Commands_1_1ComponentChange.md),  [SR\_CORE\_NS::Commands::ComponentsChange](classSR__CORE__NS_1_1Commands_1_1ComponentsChange.md),  [SR\_CORE\_NS::Commands::EntityEnable](classSR__CORE__NS_1_1Commands_1_1EntityEnable.md),  [SR\_CORE\_NS::Commands::GameObjectMove](classSR__CORE__NS_1_1Commands_1_1GameObjectMove.md),  [SR\_CORE\_NS::Commands::GameObjectTransform](classSR__CORE__NS_1_1Commands_1_1GameObjectTransform.md),  [SR\_CORE\_NS::Commands::SceneObjectChangeProperties](classSR__CORE__NS_1_1Commands_1_1SceneObjectChangeProperties.md),  [SR\_CORE\_NS::Commands::SceneObjectDelete](classSR__CORE__NS_1_1Commands_1_1SceneObjectDelete.md),  [SR\_CORE\_NS::Commands::SceneObjectInstance](classSR__CORE__NS_1_1Commands_1_1SceneObjectInstance.md),  [SR\_CORE\_NS::Commands::SceneObjectLayer](classSR__CORE__NS_1_1Commands_1_1SceneObjectLayer.md),  [SR\_CORE\_NS::Commands::SceneObjectRename](classSR__CORE__NS_1_1Commands_1_1SceneObjectRename.md),  [SR\_CORE\_NS::Commands::SceneObjectTag](classSR__CORE__NS_1_1Commands_1_1SceneObjectTag.md)












## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Engine**](classSR__CORE__NS_1_1Engine.md) &gt; | [**EnginePtr**](#typedef-engineptr)  <br> |






















## Public Static Attributes inherited from SR_UTILS_NS::ICommand

See [SR\_UTILS\_NS::ICommand](classSR__UTILS__NS_1_1ICommand.md)

| Type | Name |
| ---: | :--- |
|  auto | [**DATA\_ID**](classSR__UTILS__NS_1_1ICommand.md#variable-data_id)   = `SR\_UTILS\_NS::SerializationId::Create("command")`<br> |






































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**IEngineReversibleCommand**](#function-ienginereversiblecommand) (EnginePtr pEngine) <br> |


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




















## Protected Attributes

| Type | Name |
| ---: | :--- |
|  [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Engine**](classSR__CORE__NS_1_1Engine.md) &gt; | [**m\_engine**](#variable-m_engine)  <br> |
|  [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**SR\_WORLD\_NS::Scene**](classSR__WORLD__NS_1_1Scene.md) &gt; | [**m\_scene**](#variable-m_scene)  <br> |




























































## Public Types Documentation




### typedef EnginePtr 

```C++
using SR_CORE_NS::Commands::IEngineReversibleCommand::EnginePtr =  SR_HTYPES_NS::SharedPtr<Engine>;
```




<hr>
## Public Functions Documentation




### function IEngineReversibleCommand 

```C++
inline explicit SR_CORE_NS::Commands::IEngineReversibleCommand::IEngineReversibleCommand (
    EnginePtr pEngine
) 
```




<hr>
## Protected Attributes Documentation




### variable m\_engine 

```C++
SR_HTYPES_NS::SharedPtr<Engine> SR_CORE_NS::Commands::IEngineReversibleCommand::m_engine;
```




<hr>



### variable m\_scene 

```C++
SR_HTYPES_NS::SharedPtr<SR_WORLD_NS::Scene> SR_CORE_NS::Commands::IEngineReversibleCommand::m_scene;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/inc/Engine/EngineCommands.h`

