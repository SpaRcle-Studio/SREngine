

# Class SR\_UTILS\_NS::GroupCommand



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**GroupCommand**](classSR__UTILS__NS_1_1GroupCommand.md)








Inherits the following classes: [SR\_UTILS\_NS::ReversibleCommand](classSR__UTILS__NS_1_1ReversibleCommand.md)




































## Public Static Attributes inherited from SR_UTILS_NS::ICommand

See [SR\_UTILS\_NS::ICommand](classSR__UTILS__NS_1_1ICommand.md)

| Type | Name |
| ---: | :--- |
|  auto | [**DATA\_ID**](classSR__UTILS__NS_1_1ICommand.md#variable-data_id)   = `SR\_UTILS\_NS::SerializationId::Create("command")`<br> |






































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**GroupCommand**](#function-groupcommand) (std::vector&lt; [**ReversibleCommand**](classSR__UTILS__NS_1_1ReversibleCommand.md) \* &gt; && commands) <br> |
| virtual bool | [**Load**](#function-load) (const [**Xml::Node**](classSR__UTILS__NS_1_1Xml_1_1Node.md) & node) override<br> |
| virtual SR\_NODISCARD [**Xml::Node**](classSR__UTILS__NS_1_1Xml_1_1Node.md) | [**Save**](#function-save) () override const<br> |
|   | [**~GroupCommand**](#function-groupcommand) () override<br> |


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
















































































## Public Functions Documentation




### function GroupCommand 

```C++
SR_UTILS_NS::GroupCommand::GroupCommand (
    std::vector< ReversibleCommand * > && commands
) 
```




<hr>



### function Load 

```C++
inline virtual bool SR_UTILS_NS::GroupCommand::Load (
    const Xml::Node & node
) override
```



Implements [*SR\_UTILS\_NS::ReversibleCommand::Load*](classSR__UTILS__NS_1_1ReversibleCommand.md#function-load)


<hr>



### function Save 

```C++
inline virtual SR_NODISCARD Xml::Node SR_UTILS_NS::GroupCommand::Save () override const
```



Implements [*SR\_UTILS\_NS::ReversibleCommand::Save*](classSR__UTILS__NS_1_1ReversibleCommand.md#function-save)


<hr>



### function ~GroupCommand 

```C++
SR_UTILS_NS::GroupCommand::~GroupCommand () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/CommandManager/ReversibleCommand.h`

