

# File ReversibleCommand.h



[**FileList**](files.md) **>** [**CommandManager**](dir_24ef48620107e14c766ff883ed46f46c.md) **>** [**ReversibleCommand.h**](ReversibleCommand_8h.md)

[Go to the source code of this file](ReversibleCommand_8h_source.md)



* `#include <Utils/CommandManager/ICommand.h>`
* `#include <Utils/Resources/Xml.h>`













## Namespaces

| Type | Name |
| ---: | :--- |
| namespace | [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) <br> |


## Classes

| Type | Name |
| ---: | :--- |
| class | [**GroupCommand**](classSR__UTILS__NS_1_1GroupCommand.md) <br> |
| class | [**ReversibleCommand**](classSR__UTILS__NS_1_1ReversibleCommand.md) <br> |

















































## Macros

| Type | Name |
| ---: | :--- |
| define  | [**SR\_MAKE\_REVERSIBLE\_CMD\_ALLOCATOR**](ReversibleCommand_8h.md#define-sr_make_reversible_cmd_allocator) (type, pEngine) `[pEngine]() -&gt; [**SR\_UTILS\_NS::ReversibleCommand**](classSR__UTILS__NS_1_1ReversibleCommand.md)\* { return dynamic\_cast&lt;[**SR\_UTILS\_NS::ReversibleCommand**](classSR__UTILS__NS_1_1ReversibleCommand.md)\*&gt;(new type(pEngine)); }`<br> |
| define  | [**SR\_REGISTER\_REVERSIBLE\_CMD**](ReversibleCommand_8h.md#define-sr_register_reversible_cmd) (manager, type, pEngine) `manager-&gt;RegisterCommand(#type, SR\_MAKE\_REVERSIBLE\_CMD\_ALLOCATOR(type, pEngine))`<br> |

## Macro Definition Documentation





### define SR\_MAKE\_REVERSIBLE\_CMD\_ALLOCATOR 

```C++
#define SR_MAKE_REVERSIBLE_CMD_ALLOCATOR (
    type,
    pEngine
) `[pEngine]() -> SR_UTILS_NS::ReversibleCommand * { return dynamic_cast< SR_UTILS_NS::ReversibleCommand *>(new type(pEngine)); }`
```




<hr>



### define SR\_REGISTER\_REVERSIBLE\_CMD 

```C++
#define SR_REGISTER_REVERSIBLE_CMD (
    manager,
    type,
    pEngine
) `manager->RegisterCommand(#type, SR_MAKE_REVERSIBLE_CMD_ALLOCATOR(type, pEngine))`
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/CommandManager/ReversibleCommand.h`

