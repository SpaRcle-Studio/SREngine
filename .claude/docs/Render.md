# Рендер

## Меши, буферы, очередь

- `RenderQueue` фиксирует VBO при регистрации. Изменение меша ставит объект в перерегистрацию (`RenderStrategy::Prepare`); пока `IsWaitReRegister`, объект не рисуется.
- `IndexedMesh::Calculate` при каждом пересчёте освобождает всё (`FreeVideoMemory`: VBO, IBO, UBO, дескриптор) и выделяет заново. `ProceduralMesh` выделяет с запасом (×1.5) и пишет помещающиеся данные на месте через `Pipeline::UpdateVBO/UpdateIBO` — VBO не меняется, перерегистрация (`CreateRegistrationInfo`) не нужна, кроме смены layout или перевыделения.
  - Vulkan `UpdateVBO/UpdateIBO` не пишет в старый буфер (его может читать GPU): новый буфер той же ёмкости под тем же ID, старый удаляется отложенно. WebGPU — `queue.WriteBuffer`, упорядочен с командами, ждать не нужно.
- Vulkan: VBO/IBO удаляются отложенно (`VulkanTools::MemoryManager::RetireBuffer`) через `swapchainImages + maxFramesInFlight + 1` кадров (`OnFrameEnd` из `VulkanPipeline::DrawFrame`) — покрывает кадры в полёте и закешированные командные буферы. Поэтому `FreeVBO/FreeIBO` и пересоздание в `AllocateVBO` не ждут GPU (`WaitAllFences` был самым дорогим местом). `MemoryManager::Free` ждёт простоя устройства перед удалением очереди.
  - `AllocateVBO` с существующим VBO того же размера пишет прямо в живой буфер (`ParticleEmitter`, `TextMesh`; у частиц свой буфер на кадр).
- `VertexDataBuffer::GetVertex` под `#ifdef SR_UTILS_ASSIMP` (`Vertices.cpp`), без assimp отсутствует — работай с `data` по `layout`.
- `ComputeShader::EndCompute()` вызывает `WaitComputeIdle()` — проход синхронный, SSBO можно читать сразу. Исключение — между `Pipeline::BeginAsyncCompute` и `SubmitAsyncCompute`: команды копятся в отдельном буфере (Vulkan: свой пул семейства compute, фенс на задачу), готовность — `IsAsyncComputeComplete`, затем `ReleaseAsyncCompute`. Ресурсы задачи (SSBO, дескрипторы экземпляра `ComputeShader`) до завершения не трогать; между зависимыми диспатчами — `WriteMemoryBarrier(ComputeToCompute)`. `BeginAsyncCompute` вернул `SR_ID_INVALID` — API не поддерживает, вычисления синхронные.
- `SSBOInstance::ResetCounter()` на незамапленном буфере сам мапит, флашит и анмапит. `FlushCounter()` после этого без `Map` → ассерт `SSBO is not mapped`.
- `Pipeline::GetPixelRangeResult` возвращает каналы байтовых форматов в **0..255**, даже в `FColor`. `IColorBufferPass::GetMeshByColor` декодирует ID целочисленно — нормализация readback ломает picking (нормализуется только цвет в шейдер, `GetMeshColor`).

## Пайплайн (srptech)

- Основная техника — `Resources/Engine/Render/Render.srptech` (`FileRenderTechniquePresetResource`). Собирается кодом из интеграций `RenderTechniquePresetIntegration*` (`RenderTechniquePreset.cpp`) в порядке файла. `MainView` создаёт `Offscreen` FBO и `PostProcessPass`; остальные (AutoExposure, Bloom, SSAO, облака, туман) вставляют `FrameBufferPass` через `pMainGroup->InsertPass(..., IndexOfPass(offscreenControllerName) + 1)` и добавляют сэмплер в `PostProcessPass`. Новый эффект = новая интеграция + запись в `Render.srptech`.
- Техника клонируется рефлексией (`CloneTo`) — параметры прохода, задаваемые интеграцией, должны быть `@property`, иначе теряются.
- Пресеты качества: `Quality` (None..Extreme) в `ActiveGraphicsSettings`, пользовательский файл `User/GraphicsSettings.sra`. Пресеты — `RenderSettings` (`Resources/Engine/Configs/RenderSettings.sras`), выбор `FindSuitableQuality`. Макросы `SR_SSAO`, `SR_BLOOM` и т.п. — в `RenderContext::SetGraphicsSettings` (`SwitchMacro`). Переопределения камеры — `CameraRenderParameters`.
- `PostProcessPass` + `SetShader(path)` — база полноэкранных проходов. Свои uniform'ы — в `UseSharedUniforms` (`[[uniform(SHARED)]]`), дефайны — `GetMaterial()->GetMaterialData()->AddShaderDefine` в `Init()` до `Super::Init()`. SSBO экспозиции — `AddSSBOUsageFromPass(AutoExposurePass::GetClassStaticName())` и `[[ssbo(exposure)]] float[] exposure;`.
- `FrameBufferController`: размер = окно/камера × `preScale`, минимум 1 px. FBO без глубины: `SetDepthEnabled(false)` у контроллера и `SetClearDepth(Optional<float_t>())` у `FrameBufferPassData` (глубина по умолчанию включена; включена без clear depth → `RenderFrameBuffer` падает с «depth is not set»).
- Все сэмплеры кадровых буферов — **NEAREST** + clamp (Vulkan и WebGPU). Билинейки нет: апсемпл/размытие вручную выборками в центры текселей (`sampleLowRes` в `post-process.srsl`, `Bloom/bloom.srsl`).
- Блендинг (`BlendEnabled`) в Vulkan применяется ко всем color-attachment'ам с `SRC_ALPHA / ONE_MINUS_SRC_ALPHA`, `SRC_ALPHA` — из записываемого выхода. Выход с `a = 1` перезаписывает пиксель целиком.

## G-buffer

- Слои `Offscreen` (число — `mainRenderColorLayers`), описание и декодирование — `Shaders/Common/gbuffer.srsl`: 0 — HDR-цвет (`B10G11R11_UFLOAT` при `hdr`); 1 — coverage (RGBA8: r покрытие, g metallic, b roughness); 2 — позиция (RGBA16F, xyz); 3 — нормаль (RGBA8, rgb в `[0, 1]`).
- Всё, кроме покрытия, хранится умноженным на покрытие и при чтении делится на него (`gbufferPosition/Normal/Metallic/Roughness`). «Есть геометрия» — `gbufferHasGeometry(coverage)` (`coverage > 0.02`), не `a > 0.5`. Причина: MSAA resolve и блендинг усредняют слои, на силуэтах получается `покрытие × значение`; порог 0.5 выкидывал полупрозрачные объекты.
- Запись: `COLOR_INDEX_1 = vec4(1.0, metallic, roughness, alpha); COLOR_INDEX_2 = vec4(position, alpha); COLOR_INDEX_3 = vec4(normal * 0.5 + 0.5, alpha);` (`alpha` — непрозрачность фрагмента). Покрытие в r, а не a, т.к. блендинг даёт `a²`. Шейдер основного прохода без записи G-buffer невидим для волюметриков и SSR. Пишут: `standard`, `hair`, `bubble`, `gizmo`, `wire-mesh`, `line`, `terrain-grass`, `image-on-mesh`, `MarchingCubes/MeshShader`; skybox и UI — нули.
- Сэмплеры G-buffer (`coverageMap`, `positionMap`, `normalMap`) добавляй через `AddGBufferSamplers` (`RenderTechniquePreset.cpp`) — пропускает уже добавленные.
- Производительность: 4 слоя на пиксель + MSAA resolve — не поднимай форматы без нужды (RGBA16F нормалей заметно стоил FPS). В циклах с десятками выборок (SSAO) не вызывай `gbufferPosition` с отдельным чтением покрытия — удваивает чтения.

## Пониженное разрешение (облака, туман, SSR)

- Дистанция до сцены считается один раз: `SceneDistancePass` (`Common/scene-distance.srsl`, ½ разрешения, R32F) хранит ближайшую поверхность в блоке 2×2 (`gbufferLowResDistance`), 1e6 — небо. Создаётся `EnsureSceneDistancePass` при первой нуждающейся интеграции. Проходы читают через `gbufferSceneDistance(sceneDistanceMap, ...)` — не читай G-buffer сам (было 8 выборок на пиксель, дорого).
- Эти проходы пишут во второй слой (R32F) дистанцию пикселя (1e6 — небо); апсемпл `sampleLowRes` в `post-process.srsl` читает её как `*DepthMap`. Если 4 ближайшие выборки совпадают по глубине — билинейка; только на силуэтах joint bilateral 4×4 (полный 4×4 везде стоил ~½ FPS). На силуэте объект и небо смешиваются по покрытию.
- Размер буфера прохода — `TARGET_RESOLUTION`, размер камеры — `RESOLUTION`.

## Эффекты

- Bloom (`RenderTechniquePresetIntegrationBloom` + `BloomPass`): prefilter (мягкий порог по экспонированной яркости, Karis average, tent 4×4) → downsample → upsample (`mix(mip, up, scatter)`) → `bloomMap` в `post-process.srsl` до тонмаппинга. Качество — `BloomPreset` (preScale, mipCount, HQ, RGBA16F); пустой `bloomQualityPresets` → дефолты `RenderSettings::GetBloomPreset`. Нужен `hdr`.
- SSR (`RenderTechniquePresetIntegrationSSR` + `SSRPass`, `SSR/ssr.srsl`): Trace (экранная трассировка с перспективно-корректной интерполяцией и бинарным уточнением; premultiplied: rgb × достоверность, a — достоверность) → Resolve (bilateral, радиус от roughness) → `ssrMap`. Смешивается по Френелю (F0 = mix(0.04, 1, metallic)) после SSAO, до облаков, тумана и bloom. Качество — `SSRPreset` (preScale, maxSteps, refineSteps, maxDistance, resolve), дефолты `RenderSettings::GetSSRPreset`.
