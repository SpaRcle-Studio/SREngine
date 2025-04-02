

# Class SR\_UTILS\_NS::ReversibleCommand



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**ReversibleCommand**](classSR__UTILS__NS_1_1ReversibleCommand.md)








Inherits the following classes: [SR\_UTILS\_NS::ICommand](classSR__UTILS__NS_1_1ICommand.md)


Inherited by the following classes: [SR\_CORE\_NS::Commands::IEngineReversibleCommand](classSR__CORE__NS_1_1Commands_1_1IEngineReversibleCommand.md),  [SR\_UTILS\_NS::GroupCommand](classSR__UTILS__NS_1_1GroupCommand.md)


























## Public Static Attributes inherited from SR_UTILS_NS::ICommand

See [SR\_UTILS\_NS::ICommand](classSR__UTILS__NS_1_1ICommand.md)

| Type | Name |
| ---: | :--- |
|  auto | [**DATA\_ID**](classSR__UTILS__NS_1_1ICommand.md#variable-data_id)   = `SR\_UTILS\_NS::SerializationId::Create("command")`<br> |


























## Public Functions

| Type | Name |
| ---: | :--- |
| virtual std::string | [**GetName**](#function-getname) () <br> |
| virtual bool | [**Load**](#function-load) (const [**Xml::Node**](classSR__UTILS__NS_1_1Xml_1_1Node.md) & node) <br> |
| virtual bool | [**Redo**](#function-redo) () = 0<br> |
|   | [**ReversibleCommand**](#function-reversiblecommand) () = default<br> |
| virtual SR\_NODISCARD [**Xml::Node**](classSR__UTILS__NS_1_1Xml_1_1Node.md) | [**Save**](#function-save) () const<br> |
| virtual bool | [**Undo**](#function-undo) () = 0<br> |
|   | [**~ReversibleCommand**](#function-reversiblecommand) () override<br> |


## Public Functions inherited from SR_UTILS_NS::ICommand

See [SR\_UTILS\_NS::ICommand](classSR__UTILS__NS_1_1ICommand.md)

| Type | Name |
| ---: | :--- |
|   | [**ICommand**](classSR__UTILS__NS_1_1ICommand.md#function-icommand) () = default<br> |
| virtual  | [**~ICommand**](classSR__UTILS__NS_1_1ICommand.md#function-icommand) () = default<br> |






















































## Public Functions Documentation




### function GetName 

```C++
inline virtual std::string SR_UTILS_NS::ReversibleCommand::GetName () 
```




<hr>



### function Load 

```C++
inline virtual bool SR_UTILS_NS::ReversibleCommand::Load (
    const Xml::Node & node
) 
```




<hr>



### function Redo 

```C++
virtual bool SR_UTILS_NS::ReversibleCommand::Redo () = 0
```




<hr>



### function ReversibleCommand 

```C++
SR_UTILS_NS::ReversibleCommand::ReversibleCommand () = default
```




<hr>



### function Save 

```C++
inline virtual SR_NODISCARD Xml::Node SR_UTILS_NS::ReversibleCommand::Save () const
```




<hr>



### function Undo 

```C++
virtual bool SR_UTILS_NS::ReversibleCommand::Undo () = 0
```




<hr>



### function ~ReversibleCommand 

```C++
SR_UTILS_NS::ReversibleCommand::~ReversibleCommand () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/CommandManager/ReversibleCommand.h`

