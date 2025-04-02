

# Class SR\_ANIMATIONS\_NS::AnimationChannel



[**ClassList**](annotated.md) **>** [**SR\_ANIMATIONS\_NS**](namespaceSR__ANIMATIONS__NS.md) **>** [**AnimationChannel**](classSR__ANIMATIONS__NS_1_1AnimationChannel.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**AddKey**](#function-addkey) (double\_t timePoint, T key) <br> |
|  SR\_NODISCARD [**AnimationChannel**](classSR__ANIMATIONS__NS_1_1AnimationChannel.md) \* | [**Copy**](#function-copy) () noexcept const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE uint16\_t | [**GetBoneIndex**](#function-getboneindex) () noexcept const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetGameObjectName**](#function-getgameobjectname) () noexcept const<br> |
|  SR\_NODISCARD const Keys & | [**GetKeys**](#function-getkeys) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE bool | [**HasBoneIndex**](#function-hasboneindex) () noexcept const<br> |
|  void | [**SetBoneIndex**](#function-setboneindex) (uint16\_t index) <br> |
|  void | [**SetName**](#function-setname) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name) <br> |
|  SR\_NODISCARD uint32\_t | [**UpdateChannel**](#function-updatechannel) (uint32\_t keyIndex, float\_t time, [**UpdateContext**](structSR__ANIMATIONS__NS_1_1UpdateContext.md) & context, [**ChannelUpdateContext**](structSR__ANIMATIONS__NS_1_1ChannelUpdateContext.md) & channelContext) const<br> |
|  SR\_NODISCARD uint32\_t | [**UpdateChannelWithWeight**](#function-updatechannelwithweight) (uint32\_t keyIndex, float\_t time, [**UpdateContext**](structSR__ANIMATIONS__NS_1_1UpdateContext.md) & context, [**ChannelUpdateContext**](structSR__ANIMATIONS__NS_1_1ChannelUpdateContext.md) & channelContext) const<br> |
|   | [**~AnimationChannel**](#function-animationchannel) () override<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  void | [**Load**](#function-load) ([**SR\_HTYPES\_NS::RawMesh**](classSR__HTYPES__NS_1_1RawMesh.md) \* pRawMesh, aiNodeAnim \* pChannel, float\_t ticksPerSecond, std::vector&lt; [**AnimationChannel**](classSR__ANIMATIONS__NS_1_1AnimationChannel.md) \* &gt; & channels) <br> |














































## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|  constexpr | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () = default<br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () = default<br> |






## Public Functions Documentation




### function AddKey 

```C++
template<class T>
inline void SR_ANIMATIONS_NS::AnimationChannel::AddKey (
    double_t timePoint,
    T key
) 
```




<hr>



### function Copy 

```C++
inline SR_NODISCARD AnimationChannel * SR_ANIMATIONS_NS::AnimationChannel::Copy () noexcept const
```




<hr>



### function GetBoneIndex 

```C++
inline SR_NODISCARD SR_FORCE_INLINE uint16_t SR_ANIMATIONS_NS::AnimationChannel::GetBoneIndex () noexcept const
```




<hr>



### function GetGameObjectName 

```C++
inline SR_NODISCARD SR_FORCE_INLINE SR_UTILS_NS::StringAtom SR_ANIMATIONS_NS::AnimationChannel::GetGameObjectName () noexcept const
```




<hr>



### function GetKeys 

```C++
inline SR_NODISCARD const Keys & SR_ANIMATIONS_NS::AnimationChannel::GetKeys () const
```




<hr>



### function HasBoneIndex 

```C++
inline SR_NODISCARD SR_FORCE_INLINE bool SR_ANIMATIONS_NS::AnimationChannel::HasBoneIndex () noexcept const
```




<hr>



### function SetBoneIndex 

```C++
inline void SR_ANIMATIONS_NS::AnimationChannel::SetBoneIndex (
    uint16_t index
) 
```




<hr>



### function SetName 

```C++
void SR_ANIMATIONS_NS::AnimationChannel::SetName (
    SR_UTILS_NS::StringAtom name
) 
```




<hr>



### function UpdateChannel 

```C++
SR_NODISCARD uint32_t SR_ANIMATIONS_NS::AnimationChannel::UpdateChannel (
    uint32_t keyIndex,
    float_t time,
    UpdateContext & context,
    ChannelUpdateContext & channelContext
) const
```




<hr>



### function UpdateChannelWithWeight 

```C++
SR_NODISCARD uint32_t SR_ANIMATIONS_NS::AnimationChannel::UpdateChannelWithWeight (
    uint32_t keyIndex,
    float_t time,
    UpdateContext & context,
    ChannelUpdateContext & channelContext
) const
```




<hr>



### function ~AnimationChannel 

```C++
SR_ANIMATIONS_NS::AnimationChannel::~AnimationChannel () override
```




<hr>
## Public Static Functions Documentation




### function Load 

```C++
static void SR_ANIMATIONS_NS::AnimationChannel::Load (
    SR_HTYPES_NS::RawMesh * pRawMesh,
    aiNodeAnim * pChannel,
    float_t ticksPerSecond,
    std::vector< AnimationChannel * > & channels
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/Animations/AnimationChannel.h`

