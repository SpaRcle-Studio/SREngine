# Шейдеры SRSL: подводные камни

Синтаксис SRSL — [Documentation/SRSL.md](../../Documentation/SRSL.md).

## Ошибки транслятора

- `>=`/`<=` в инициализации ломаются: `float x = a >= b ? c : d;` → `float x = a; (b ? c : d);` (то же с `bool s = a >= b;`). В `if`/`for` работают. Пиши `float x = (a > b) ? c : d;`.
- Составное присваивание со swizzle от вызова: `a *= texture(t, uv).r` → `(a *= texture(t, uv)).r`. Пиши `a = a * texture(t, uv).r`.
- `int * ivec3` пиши как `ivec3(x) * v` — WGSL не расширяет скаляр неявно.
- Поля uniform-блоков (`[[uniform]]`, включая `[public]`-параметры материала) в GLSL глобальные — не называй так же локальные переменные и параметры функций (напр. `float roughness` при uniform `roughness`), в т.ч. в общих include вроде `pcf-utils.inl.srsl`.
- Выходы `COLOR_INDEX_*` объявляются **после** пользовательских функций, перед `main()` — писать в них только из `fragment()`. Хелперы возвращают значение (`vec4 trace() {...}`, `COLOR_INDEX_0 = trace();`), иначе glslang: «failed to parse shader».
- Сгенерированный код: `Resources/Cache/Shaders/<путь к srsl>/<хеш>/shader.frag`. Проверка — `glslangValidator -V shader.frag` (Vulkan SDK, `C:/VulkanSDK/<версия>/Bin`), номер строки указывает на сгенерированный код. Это компилятор — **только с разрешения пользователя**.

## Текстуры

- Для незаданной/незагруженной текстуры (`!Texture::CanBeUsed()`, включая асинхронную загрузку) `Shader::SetSampler2D` подставляет `RenderContext::GetNoneTexture()` — PNG 1×1 из base64 в `RenderContext::Init`. Должен быть непрозрачный белый (255, 255, 255, 255), иначе объекты с `HAS_ALPHA` становятся прозрачными. `GetDefaultTexture()` (`Engine/Textures/default_improved.png`) подставляет `SamplersPassData`.

## Освещение и тени

- `standard.srsl` — metallic-roughness (glTF 2.0). Скаляры `metallic`/`roughness` умножаются на текстуры (`ORM`: r AO, g roughness, b metallic; либо `roughnessMap` при `HAS_ROUGHNESS`), без текстур — значения. `specular` (0.5) → F0 = 0.08 × specular для диэлектриков. Эмиссия = `emissionColor × emissionIntensity` (× RGB `emission` при `HAS_EMISSION`). Все выборки по `tiledUV`.
- Освещение — `CalculateShadow` в `Common/pcf-utils.inl.srsl`: GGX, height-correlated Smith, Шлик; окружение — полусфера небо/земля с `EnvBRDFApprox`. Солнце нормировано: ламбертовская часть = `baseColor × NdotL × SUN`, зеркальная домножена на π. У `hair.srsl` и `terrain-grass.srsl` свои модели блика.
- `filterPCF`: сначала 4 выборки по краям фильтра (целиком в тени/на свету — выход), иначе `cascadeSamples[i]` выборок по спирали Фогеля со случайным поворотом на пиксель (`FRAG_COORD`) в радиусе `cascadeRange × cascadeScale` текселей. Не возвращать сетку `(2r+1)²` — была главным потребителем кадра. Только из фрагментного шейдера.
- Матрицы каскадов (`CascadedShadowMapPass::UpdateCascades`) пересчитываются в `PostUpdate` по камере кадра. Каскад выбирается по квадрату проекции shadow map; сферический режим — поле `sphericalCascadeSelection` пресета теней → макрос `SR_CASCADE_SPHERICAL_SELECTION` (по аналогии с `SR_SHADOWS_QUALITY_EXTREME`).
