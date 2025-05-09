

# Class SR\_UTILS\_NS::Singleton

**template &lt;typename T&gt;**



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**Singleton**](classSR__UTILS__NS_1_1Singleton.md)








Inherits the following classes: [SR\_UTILS\_NS::SingletonBase](classSR__UTILS__NS_1_1SingletonBase.md)


Inherited by the following classes: [SR\_UTILS\_NS::GlobalSettings](classSR__UTILS__NS_1_1GlobalSettings.md),  [SR\_UTILS\_NS::GlobalSettings](classSR__UTILS__NS_1_1GlobalSettings.md),  [SR\_UTILS\_NS::GlobalSettings](classSR__UTILS__NS_1_1GlobalSettings.md),  [SR\_AUDIO\_NS::SoundManager](classSR__AUDIO__NS_1_1SoundManager.md),  [SR\_CORE\_NS::CLIManager](classSR__CORE__NS_1_1CLIManager.md),  [SR\_CORE\_NS::TestManager](classSR__CORE__NS_1_1TestManager.md),  [SR\_GRAPH\_NS::DescriptorManager](classSR__GRAPH__NS_1_1DescriptorManager.md),  [SR\_GRAPH\_NS::GUI::GlobalWidgetManager](classSR__GRAPH__NS_1_1GUI_1_1GlobalWidgetManager.md),  [SR\_GRAPH\_NS::GUI::MessageBoxWidget](classSR__GRAPH__NS_1_1GUI_1_1MessageBoxWidget.md),  [SR\_GRAPH\_NS::GUI::NodeManager](classSR__GRAPH__NS_1_1GUI_1_1NodeManager.md),  [SR\_GRAPH\_NS::GUI::ViewportsTableManager](classSR__GRAPH__NS_1_1GUI_1_1ViewportsTableManager.md),  [SR\_GRAPH\_NS::Memory::CameraManager](classSR__GRAPH__NS_1_1Memory_1_1CameraManager.md),  [SR\_GRAPH\_NS::Memory::MeshManager](classSR__GRAPH__NS_1_1Memory_1_1MeshManager.md),  [SR\_GRAPH\_NS::Memory::ShaderProgramManager](classSR__GRAPH__NS_1_1Memory_1_1ShaderProgramManager.md),  [SR\_GRAPH\_NS::Memory::TextureConfigs](classSR__GRAPH__NS_1_1Memory_1_1TextureConfigs.md),  [SR\_GRAPH\_NS::Memory::UBOManager](classSR__GRAPH__NS_1_1Memory_1_1UBOManager.md),  [SR\_GRAPH\_NS::SRSL::SRSLLoader](classSR__GRAPH__NS_1_1SRSL_1_1SRSLLoader.md),  [SR\_GRAPH\_NS::SSBOManager](classSR__GRAPH__NS_1_1SSBOManager.md),  [SR\_NETWORK\_NS::FileDownloader](classSR__NETWORK__NS_1_1FileDownloader.md),  [SR\_PHYSICS\_NS::PhysicsLibrary](classSR__PHYSICS__NS_1_1PhysicsLibrary.md),  [SR\_PHYSICS\_NS::Raycast3D](classSR__PHYSICS__NS_1_1Raycast3D.md),  [SR\_SCRIPTING\_NS::EvoScriptManager](classSR__SCRIPTING__NS_1_1EvoScriptManager.md),  [SR\_SCRIPTING\_NS::GlobalEvoCompiler](classSR__SCRIPTING__NS_1_1GlobalEvoCompiler.md),  [SR\_SCRIPTING\_NS::ScriptSystem](classSR__SCRIPTING__NS_1_1ScriptSystem.md),  [SR\_SRLM\_NS::DataTypeAllocator](classSR__SRLM__NS_1_1DataTypeAllocator.md),  [SR\_SRLM\_NS::DataTypeManager](classSR__SRLM__NS_1_1DataTypeManager.md),  [SR\_SRLM\_NS::LogicalNodeManager](classSR__SRLM__NS_1_1LogicalNodeManager.md),  [SR\_SRSL\_NS::GLSLCodeGenerator](classSR__SRSL__NS_1_1GLSLCodeGenerator.md),  [SR\_SRSL\_NS::SRSLAssignExpander](classSR__SRSL__NS_1_1SRSLAssignExpander.md),  [SR\_SRSL\_NS::SRSLEvaluator](classSR__SRSL__NS_1_1SRSLEvaluator.md),  [SR\_SRSL\_NS::SRSLLexer](classSR__SRSL__NS_1_1SRSLLexer.md),  [SR\_SRSL\_NS::SRSLLexicalAnalyzer](classSR__SRSL__NS_1_1SRSLLexicalAnalyzer.md),  [SR\_SRSL\_NS::SRSLMathExpression](classSR__SRSL__NS_1_1SRSLMathExpression.md),  [SR\_SRSL\_NS::SRSLPreProcessor](classSR__SRSL__NS_1_1SRSLPreProcessor.md),  [SR\_SRSL\_NS::SRSLPseudoCodeGenerator](classSR__SRSL__NS_1_1SRSLPseudoCodeGenerator.md),  [SR\_SRSL\_NS::SRSLRefAnalyzer](classSR__SRSL__NS_1_1SRSLRefAnalyzer.md),  [SR\_SRSL\_NS::SRSLTypeInfo](classSR__SRSL__NS_1_1SRSLTypeInfo.md),  [SR\_UTILS\_NS::Broadcaster](classSR__UTILS__NS_1_1Broadcaster.md),  [SR\_UTILS\_NS::ComponentManager](classSR__UTILS__NS_1_1ComponentManager.md),  [SR\_UTILS\_NS::Debug](classSR__UTILS__NS_1_1Debug.md),  [SR\_UTILS\_NS::DebugDraw](classSR__UTILS__NS_1_1DebugDraw.md),  [SR\_UTILS\_NS::EnumReflectorManager](classSR__UTILS__NS_1_1EnumReflectorManager.md),  [SR\_UTILS\_NS::EventManager](classSR__UTILS__NS_1_1EventManager.md),  [SR\_UTILS\_NS::Features](classSR__UTILS__NS_1_1Features.md),  [SR\_UTILS\_NS::FileDialog](classSR__UTILS__NS_1_1FileDialog.md),  [SR\_UTILS\_NS::GlobalSettings](classSR__UTILS__NS_1_1GlobalSettings.md),  [SR\_UTILS\_NS::Input](classSR__UTILS__NS_1_1Input.md),  [SR\_UTILS\_NS::MigrationManager](classSR__UTILS__NS_1_1MigrationManager.md),  [SR\_UTILS\_NS::PropertyManager](classSR__UTILS__NS_1_1PropertyManager.md),  [SR\_UTILS\_NS::Random](classSR__UTILS__NS_1_1Random.md),  [SR\_UTILS\_NS::ResourceManager](classSR__UTILS__NS_1_1ResourceManager.md),  [SR\_UTILS\_NS::StoreUtils::Storage](classSR__UTILS__NS_1_1StoreUtils_1_1Storage.md),  [SR\_UTILS\_NS::TaskManager](classSR__UTILS__NS_1_1TaskManager.md),  [SR\_UTILS\_NS::ThreadWorkerStateRegistration](classSR__UTILS__NS_1_1ThreadWorkerStateRegistration.md),  [SR\_UTILS\_NS::Web::CSSParser](classSR__UTILS__NS_1_1Web_1_1CSSParser.md),  [SR\_WORLD\_NS::SceneAllocator](classSR__WORLD__NS_1_1SceneAllocator.md)










































































## Public Functions inherited from SR_UTILS_NS::SingletonBase

See [SR\_UTILS\_NS::SingletonBase](classSR__UTILS__NS_1_1SingletonBase.md)

| Type | Name |
| ---: | :--- |
|   | [**~SingletonBase**](classSR__UTILS__NS_1_1SingletonBase.md#function-singletonbase) () override<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  SR\_MAYBE\_UNUSED void | [**DestroySingleton**](#function-destroysingleton) () <br> |
|  SR\_MAYBE\_UNUSED std::recursive\_mutex & | [**GetMutex**](#function-getmutex) () noexcept<br> |
|  SR\_MAYBE\_UNUSED T & | [**Instance**](#function-instance) () noexcept<br> |
|  SR\_MAYBE\_UNUSED bool | [**IsSingletonInitialized**](#function-issingletoninitialized) () noexcept<br> |
|  SR\_MAYBE\_UNUSED void | [**LockSingleton**](#function-locksingleton) () noexcept<br> |
|  SR\_MAYBE\_UNUSED static SR\_NODISCARD [**SR\_HTYPES\_NS::SingletonRecursiveLockGuard**](classSR__HTYPES__NS_1_1SingletonRecursiveLockGuard.md)&lt; [**Singleton**](classSR__UTILS__NS_1_1Singleton.md)&lt; T &gt; \* &gt; | [**ScopeLockSingleton**](#function-scopelocksingleton) () <br> |
|  SR\_MAYBE\_UNUSED void | [**UnlockSingleton**](#function-unlocksingleton) () noexcept<br> |




















## Protected Attributes inherited from SR_UTILS_NS::SingletonBase

See [SR\_UTILS\_NS::SingletonBase](classSR__UTILS__NS_1_1SingletonBase.md)

| Type | Name |
| ---: | :--- |
|  std::recursive\_mutex | [**m\_mutex**](classSR__UTILS__NS_1_1SingletonBase.md#variable-m_mutex)  <br> |














































## Protected Functions

| Type | Name |
| ---: | :--- |
|   | [**Singleton**](#function-singleton) () <br> |
|   | [**~Singleton**](#function-singleton) () override<br> |


## Protected Functions inherited from SR_UTILS_NS::SingletonBase

See [SR\_UTILS\_NS::SingletonBase](classSR__UTILS__NS_1_1SingletonBase.md)

| Type | Name |
| ---: | :--- |
| virtual [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetSingletonName**](classSR__UTILS__NS_1_1SingletonBase.md#function-getsingletonname) () noexcept const = 0<br> |
| virtual void | [**InitSingleton**](classSR__UTILS__NS_1_1SingletonBase.md#function-initsingleton) () <br> |
| virtual bool | [**IsSingletonCanBeDestroyed**](classSR__UTILS__NS_1_1SingletonBase.md#function-issingletoncanbedestroyed) () const<br> |
| virtual void | [**OnSingletonDestroy**](classSR__UTILS__NS_1_1SingletonBase.md#function-onsingletondestroy) () <br> |
|   | [**SingletonBase**](classSR__UTILS__NS_1_1SingletonBase.md#function-singletonbase) () <br> |


## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |








## Public Static Functions Documentation




### function DestroySingleton 

```C++
static SR_MAYBE_UNUSED void SR_UTILS_NS::Singleton::DestroySingleton () 
```




<hr>



### function GetMutex 

```C++
static SR_MAYBE_UNUSED std::recursive_mutex & SR_UTILS_NS::Singleton::GetMutex () noexcept
```




<hr>



### function Instance 

```C++
static SR_MAYBE_UNUSED T & SR_UTILS_NS::Singleton::Instance () noexcept
```




<hr>



### function IsSingletonInitialized 

```C++
static SR_MAYBE_UNUSED bool SR_UTILS_NS::Singleton::IsSingletonInitialized () noexcept
```




<hr>



### function LockSingleton 

```C++
static SR_MAYBE_UNUSED void SR_UTILS_NS::Singleton::LockSingleton () noexcept
```




<hr>



### function ScopeLockSingleton 

```C++
static SR_MAYBE_UNUSED static SR_NODISCARD SR_HTYPES_NS::SingletonRecursiveLockGuard < Singleton < T > * > SR_UTILS_NS::Singleton::ScopeLockSingleton () 
```




<hr>



### function UnlockSingleton 

```C++
static SR_MAYBE_UNUSED void SR_UTILS_NS::Singleton::UnlockSingleton () noexcept
```




<hr>
## Protected Functions Documentation




### function Singleton 

```C++
SR_UTILS_NS::Singleton::Singleton () 
```




<hr>



### function ~Singleton 

```C++
SR_UTILS_NS::Singleton::~Singleton () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Common/Singleton.h`

