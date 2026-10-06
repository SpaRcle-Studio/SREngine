# SRSL — SpaRcle Shader Language

SRSL — собственный шейдерный язык SREngine. Синтаксис основан на GLSL (типы, встроенные функции, операторы те же),
но один `.srsl` файл описывает **сразу все стадии** шейдера, настройки пайплайна и свойства материала.
Движок транслирует SRSL в GLSL (Vulkan) и WGSL (WebGPU).

## Где что лежит

| Что | Путь |
|---|---|
| Шейдеры движка | `Resources/Engine/Shaders/` |
| Общие include-файлы | `Resources/Engine/Shaders/Common/` |
| Шейдеры редактора | `Resources/Editor/Shaders/` |
| Реализация компилятора | `Engine/libs/Graphics/src/Graphics/SRSL/`, `Engine/libs/Graphics/inc/Graphics/SRSL/` |
| Точка входа компиляции | `SRSLShader::Load()` — [Shader.cpp](../Engine/libs/Graphics/src/Graphics/SRSL/Shader.cpp) |
| Встроенные переменные (uniform'ы, сэмплеры, push-константы, выходы) | [ShaderVariables.cpp](../Engine/libs/Graphics/src/Graphics/SRSL/ShaderVariables.cpp) |
| Enum'ы `ShaderType` | [ShaderProperties.h](../Engine/libs/Graphics/inc/Graphics/Loaders/ShaderProperties.h) |
| Enum'ы пайплайна, имена макросов движка | [ShaderUtils.h](../Engine/libs/Graphics/inc/Graphics/Pipeline/ShaderUtils.h) |
| Имена вершинных атрибутов | `VertexAttributeToName()` — [Vertices.cpp](../Engine/libs/Utils/src/Utils/Common/Vertices.cpp) |
| Генераторы кода | [GLSLCodeGenerator.cpp](../Engine/libs/Graphics/src/Graphics/SRSL/GLSLCodeGenerator.cpp), [WGSLCodeGenerator.cpp](../Engine/libs/Graphics/src/Graphics/SRSL/WGSLCodeGenerator.cpp) |
| Сгенерированный код (кэш) | `<Cache>/Shaders/<путь шейдера>/<хэш макросов>/shader.{vert,frag,comp}` |

## Конвейер компиляции

```
.srsl → Lexer → PreProcessor (#include, #define, #if...) → LexicalAnalyzer (AST)
      → RefAnalyzer (что реально используется) → SRSLShader::Prepare()
        (настройки, uniform-блоки, сэмплеры, биндинги, стадии)
      → GLSLCodeGenerator / WGSLCodeGenerator → кэш на диске
```

Важные следствия:

- **Неиспользуемое вырезается.** `RefAnalyzer` строит граф использования от точек входа. Uniform'ы, сэмплеры,
  SSBO и `[[shared]]` переменные, недостижимые из `vertex()/fragment()/compute()`, не попадают ни в блоки,
  ни в биндинги, ни в свойства материала. Поэтому в шейдерах встречаются строки вида
  `float unused_var = SUN_INTENSITY;` — это принудительное «использование».
- **Шейдер компилируется отдельно для каждого набора макросов** (`ShaderParams`). Один `.srsl` даёт много вариантов
  (со скелетом/без, проход теней, color-pass и т.д.).
- Биндинги назначаются автоматически: сначала uniform-блоки, затем SSBO-блоки, затем сэмплеры (по алфавиту имён,
  т.к. это `Map`). Вручную биндинги не указываются.

## Структура файла

```glsl
// 1. Настройки пайплайна (глобальные "объявления" вида <Ключ> <Значение>;)
ShaderType Spatial;
PolygonMode Fill;
CullMode Back;
DepthCompare LessOrEqual;
PrimitiveTopology TriangleList;
BlendEnabled false;
DepthWrite true;
DepthTest true;

// 2. Ресурсы: uniform'ы, сэмплеры, SSBO, константы, структуры
[[uniform], [public]] vec4 color = vec4(1.0);
[[uniform], [public]] sampler2D diffuse;

// 3. Переменные, передаваемые между стадиями
[[shared]] vec2 uv;

// 4. Обычные функции (как в GLSL)
float luminance(vec3 c) { return dot(c, vec3(0.2126, 0.7152, 0.0722)); }

// 5. Точки входа
void vertex() {
    uv = UV;
    OUT_POSITION = PROJECTION_MATRIX * VIEW_MATRIX * MODEL_MATRIX * vec4(VERTEX, 1.0);
}

void fragment() {
    COLOR = texture(diffuse, uv) * color;
}
```

Порядок объявлений на верхнем уровне не важен: точки входа, функции и ресурсы могут стоять в любом месте файла.

### Точки входа

| Функция | Стадия | Расширение в кэше |
|---|---|---|
| `void vertex()` | Vertex | `.vert` |
| `void fragment()` | Fragment | `.frag` |
| `[[THREADS(x, y, z)]] void compute()` | Compute | `.comp` |

Стадия существует, только если объявлена соответствующая функция. `compute()` **обязан** иметь декоратор
`[[THREADS(x, y, z)]]` с тремя ненулевыми аргументами — это `local_size` рабочей группы.

## Настройки пайплайна

Записываются на верхнем уровне как `Ключ Значение;`. Парсятся в `SRSLShader::PrepareSettings()`.
Их можно оборачивать в `#ifdef`.

| Ключ | Значения | Обязателен |
|---|---|---|
| `ShaderType` | `Spatial`, `SpatialCustom`, `Skinned`, `PostProcessing`, `Skybox`, `Simple`, `Canvas`, `Particles`, `Compute`, `Line`, `Custom`, `RayTrace` | **да** (иначе ошибка) |
| `PolygonMode` | `Fill`, `Line`, `Point` | нет |
| `CullMode` | `None`, `Front`, `Back`, `FrontAndBack` | нет |
| `DepthCompare` | `Never`, `Less`, `Equal`, `LessOrEqual`, `Greater`, `NotEqual`, `GreaterOrEqual`, `Always` | нет |
| `PrimitiveTopology` | `PointList`, `LineList`, `LineStrip`, `TriangleList`, `TriangleStrip`, `TriangleFan`, `...WithAdjacency`, `PathList` | нет |
| `BlendEnabled` | `true` / `false` | нет |
| `AlphaCoverage` | `true` / `false` | нет |
| `DepthWrite` | `true` / `false` | нет |
| `DepthTest` | `true` / `false` | нет |

Назначение основных `ShaderType`:

- `Spatial` — статические меши; `Skinned` — меши со скелетом; `SpatialCustom` — пространственный, только вершины.
- `PostProcessing` — полноэкранный проход (геометрии нет, вершины генерируются из `VERTEX_INDEX`).
- `Skybox`, `Canvas` (2D UI), `Particles`, `Line` (линия с началом и концом), `Compute`.
- `Custom` — всё настраивается вручную.

## Типы

- Скаляры: `bool`, `int`, `uint`, `float`
- Векторы: `vec2..4`, `ivec2..4`, `uvec2..4`, `bvec2..4`
- Матрицы: `mat2`, `mat3`, `mat4`
- Сэмплеры: `sampler1D`, `sampler2D`, `sampler2DArray`, `sampler2DMS`, `sampler3D`, `samplerCube`,
  `sampler1DShadow`, `sampler2DShadow`
- Массивы: тип с размером записывается **у типа**: `mat4[4] m;`, `float[256] buf;`.
  Массив без размера `T[]` — только для SSBO. Внутри функций допустим и GLSL-стиль: `float a[4] = { ... };`
- Структуры: `struct Name { vec3 a; float b; };` — можно использовать в SSBO и в коде.

`bool` в uniform-блоке хранится как `int`.

## Декораторы

Синтаксис: `[[dec1], [dec2(arg)]]` перед объявлением. Одиночный: `[[dec]]`.

### Переменные верхнего уровня

| Декоратор | Смысл |
|---|---|
| `[[uniform]]` | Поле uniform-блока `BLOCK` (per-object данные). Для сэмплера — текстура. |
| `[[uniform(NAME)]]` | Поле uniform-блока с именем `NAME`. `SHARED` — общий для всех объектов блок (данные кадра/камеры). |
| `[[public]]` | Свойство видно в материале (редактор, `.mat`-файлы). Без него переменная задаётся только из кода движка. |
| `[[const], [uniform]]` | Push-константа (быстрые per-draw данные, общий лимит размера ~128 байт). |
| `[[const]]` | Константа времени компиляции (`const` в GLSL). Значение обязательно. |
| `[[shared]]` | Переменная, передаваемая vertex → fragment (varying). Пишется в `vertex()`, читается в `fragment()`. |
| `[[shared(workgroup)]]` | Разделяемая память рабочей группы в compute (`shared` в GLSL). |
| `[[ssbo(NAME)]]` | Поле storage-буфера `NAME`. Несколько переменных с одним `NAME` образуют один буфер; массив без размера должен быть последним. |
| `[[readonly]]`, `[[writeonly]]`, `[[coherent]]`, `[[volatile]]`, `[[restrict]]` | Модификаторы SSBO-блока. |
| `[[attachment(N)]]` | Сэмплер — аттачмент кадрового буфера (выставляется проходами рендера). |

### Функции

| Декоратор | Смысл |
|---|---|
| `[[THREADS(x, y, z)]]` | Размер рабочей группы для `compute()`. Обязателен. |

### Значения по умолчанию

Uniform'ы с инициализатором получают значение по умолчанию для материала:

```glsl
[[uniform], [public]] float intensity = 1.0;
[[uniform], [public]] vec3 tint = vec3(1.0, 0.5, 0.2);   // vec2/vec3/ivec3/vec4 или скаляр
[[uniform], [public]] vec4 c = vec4(1.0);                  // один аргумент — заполняет все компоненты
[[uniform], [public]] sampler2D tex = "Engine/Textures/white.png"; // путь к текстуре по умолчанию
```

Поддерживаются только литералы (`float`, `int`, `vec2`, `vec3`, `ivec3`, `vec4`, строка для сэмплера) — выражения не вычисляются.

## Встроенные переменные

Их не нужно объявлять — достаточно использовать. Движок сам добавит их в нужный блок и будет заполнять.
Актуальный список — [ShaderVariables.cpp](../Engine/libs/Graphics/src/Graphics/SRSL/ShaderVariables.cpp).

### Uniform-блок `SHARED` (данные кадра)

| Имя | Тип |
|---|---|
| `VIEW_MATRIX`, `INVERSE_VIEW_MATRIX`, `VIEW_NO_TRANSLATE_MATRIX` | `mat4` |
| `PROJECTION_MATRIX`, `INVERSE_PROJECTION_MATRIX`, `PROJECTION_NO_FOV_MATRIX` | `mat4` |
| `ORTHOGONAL_MATRIX`, `PIXEL_ORTHOGONAL_MATRIX`, `LIGHT_SPACE_MATRIX` | `mat4` |
| `TIME`, `CAMERA_NEAR`, `CAMERA_FAR` | `float` |
| `SUN_INTENSITY`, `SHADOW_STRENGTH`, `AMBIENT_INTENSITY` | `float` |
| `RENDER_PASS_TYPE` | `int` |
| `RESOLUTION`, `ASPECT` | `vec2` |
| `CASCADE_LIGHT_SPACE_MATRICES` | `mat4[4]` |
| `CASCADE_RADII`, `CASCADE_SPLITS` | `vec4` |
| `CASCADE_CENTERS` | `vec3[4]` |
| `DIRECTIONAL_LIGHT_DIRECTION`, `VIEW_POSITION`, `VIEW_DIRECTION` | `vec3` |
| `SUN_COLOR`, `SKY_COLOR`, `GROUND_COLOR` | `vec3` |

### Uniform-блок `BLOCK` (данные объекта)

| Имя | Тип |
|---|---|
| `MODEL_MATRIX`, `MODEL_NO_SCALE_MATRIX` | `mat4` |
| `SKELETON_MATRICES_{128,256,384}`, `SKELETON_MATRIX_OFFSETS_{128,256,384}` | `mat4[N]` |
| `HALF_SIZE_NEAR_PLANE`, `TEXT_ATLAS_SIZE`, `UI_SCALE`, `UI_PIVOT` | `vec2` |
| `LINE_START_POINT`, `LINE_END_POINT` | `vec3` |
| `LINE_COLOR`, `RGBA_VALUE`, `SLICED_TEXTURE_BORDER`, `SLICED_WINDOW_BORDER`, `NDC_RECT` | `vec4` |
| `SSAO_SAMPLES` | `vec4[64]` |
| `TEXT_RECT_X`, `TEXT_RECT_Y`, `TEXT_RECT_WIDTH`, `TEXT_RECT_HEIGHT`, `SPRITE_FILL_AMOUNT` | `float` |
| `FILL_CENTER`, `SPRITE_MODE`, `SPRITE_FILL_ORIGIN`, `SPRITE_FILL_METHOD`, `SPRITE_FILL_CLOCKWISE` | `int` |

### Push-константы

| Имя | Тип |
|---|---|
| `PC_SHADOW_CASCADE_INDEX`, `PC_COLOR_BUFFER_MODE`, `COMPUTE_STAGE` | `int` |
| `PC_COLOR_BUFFER_VALUE` | `vec3` |

### Сэмплеры

| Имя | Тип |
|---|---|
| `SKYBOX_DIFFUSE` | `samplerCube` |
| `TEXT_ATLAS_TEXTURE`, `SSAO_NOISE` | `sampler2D` |

### Вершинные атрибуты (вход vertex, по умолчанию доступны и во fragment)

Набор атрибутов задаёт **не шейдер, а меш** (`ShaderParams::VertexLayoutDescriptions`). Имена:

`VERTEX` (позиция), `NORMAL`, `TANGENT` (`vec4`, `w` — знак битангенса), `UV`, `UV1..UV7`, `COLOR0..COLOR7`,
`BLEND_INDICES`, `BLEND_WEIGHTS`, `BLEND_INDICES2`, `BLEND_WEIGHTS2`, `MATERIAL_INDICES`, `MATERIAL_WEIGHTS`,
`MATERIAL_ID0..7`, `BLEND_FACTOR`, `POSITION0`, `POSITION1`, `CUSTOM0..CUSTOM7`.

Атрибуты автоматически передаются из vertex во fragment. Если во `vertex()` присвоить им новое значение
(например, `VERTEX = (MODEL_MATRIX * vec4(VERTEX, 1.0)).xyz;`), во `fragment()` придёт уже изменённое значение —
так `VERTEX` во фрагментном шейдере становится мировой позицией.

### Специальные переменные стадий

| Стадия | Имя | Тип | Описание |
|---|---|---|---|
| vertex | `OUT_POSITION` | `vec4` | Выходная позиция в clip-space (`gl_Position`). Если не задана, используется `vec4(VERTEX, 1.0)`. |
| vertex | `VERTEX_INDEX` | `int` | Индекс вершины (`gl_VertexIndex`). |
| fragment | `COLOR` | `vec4` | Алиас основного выхода `COLOR_INDEX_0`. |
| fragment | `COLOR_INDEX_0..8` | `vec4` | Выходы в аттачменты (MRT). |
| fragment | `FRAG_COORD` | `vec4` | `gl_FragCoord`. |
| compute | `GLOBAL_INVOCATION_ID`, `WORK_GROUP_ID`, `NUM_WORK_GROUPS`, `LOCAL_INVOCATION_ID` | `uvec3` | |
| compute | `LOCAL_INVOCATION_INDEX` | `uint` | |

GLSL-встроенные (`gl_FragCoord`, `gl_InstanceIndex`, `gl_GlobalInvocationID`, `gl_Layer`, `barrier()` ...)
тоже работают, но для переносимости на WebGPU предпочтительнее SRSL-имена.

Выход `COLOR_INDEX_N` становится настоящим `layout(location = N) out`, только если определён макрос
`USE_COLOR_INDEX_N` (его выставляет проход рендера по числу аттачментов фреймбуфера). Иначе запись в него
эмулируется локальной переменной и просто отбрасывается — поэтому шейдер может писать в `COLOR_INDEX_1..3`
безопасно для любого фреймбуфера.

### Хуки специальных проходов

| Функция | Когда вызывается |
|---|---|
| `void fragment_color_buffer_discard()` | В конце `fragment()` в color-buffer проходе (`SR_DEFINE_COLOR_PASS`, выбор объектов мышью). Обычно содержит `discard;`, чтобы объект не выбирался. |
| `void fragment_depth_buffer_discard()` | В конце `fragment()` в проходе каскадных теней (`SR_DEFINE_CASCADED_SHADOW_MAP_PASS`). Например, для alpha-test теней. |

## Препроцессор

| Директива | Описание |
|---|---|
| `#include <Path/To/file.srsl>` | Путь **только в угловых скобках** и относительно `Resources/`: `#include <Engine/Shaders/Common/utils.srsl>`. Текст вставляется на место директивы, поэтому include можно делать и внутри функции (см. `*.inl.srsl`). |
| `#define NAME` | Определить макрос. Значений у макросов нет — только «определён / не определён». |
| `#undef NAME` | Удалить макрос. |
| `#ifdef NAME` / `#ifndef NAME` | |
| `#if <выражение>` | Поддерживаются `defined(NAME)`, `&&`, `\|\|`, `true`, `false`, числа и `+ - * /`. |
| `#else`, `#endif` | `#elif` **нет** — используйте вложенные `#if`. |

Других директив нет (нет `#pragma`, `#version`, макросов с подстановкой значений) — неизвестная директива
в активной ветке является ошибкой.

### Макросы, которые выставляет движок

| Макрос | Источник / смысл |
|---|---|
| `HAS_SKELETON` | Меш со скелетом |
| `HAS_NORMAL`, `HAS_ROUGHNESS`, `HAS_ORM`, `HAS_SSS`, `HAS_EMISSION`, `HAS_DETAIL_WEIGHT`, `HAS_ALPHA_MASK` | Материал: задана соответствующая текстура |
| `HAS_ALPHA` | Материал прозрачный / с альфа-тестом |
| `DISABLE_BLENDING` | Материал |
| `SR_DEFINE_COLOR_PASS` | Проход color-buffer (picking) |
| `SR_DEFINE_CASCADED_SHADOW_MAP_PASS` | Проход рендера каскадных теней |
| `SR_DEFINE_USE_CASCADED_SHADOW_MAP` | Основной проход с тенями |
| `SR_DEFINE_DEBUG_CASCADED_SHADOW_MAP_PASS`, `SR_DEFINE_DEBUG_NORMALS`, `SR_DEFINE_WIREFRAME` | Отладка |
| `CASCADES_INSTANCING`, `CASCADES_FRUSTUM_CULLING` | Варианты прохода теней |
| `USE_COLOR_INDEX_0..8` | Реальное количество выходов фреймбуфера |

Имена макросов движка — константы `SHADER_MACRO_*` в [ShaderUtils.h](../Engine/libs/Graphics/inc/Graphics/Pipeline/ShaderUtils.h).

## Связь с материалами

`[[uniform], [public]]` переменные и сэмплеры становятся свойствами материала (`MaterialData`,
[MaterialData.h](../Engine/libs/Graphics/inc/Graphics/Material/MaterialData.h)). Материалы (`.mat`) хранятся
в формате SRA (`SRASerializer`, [SRASerialization.h](../Engine/libs/Utils/inc/Utils/Serialization/SRASerialization.h))
и сериализуются через рефлексию, вручную их обычно не пишут — материал создаётся и редактируется в редакторе.

Что важно знать со стороны шейдера:

- `defaultShader.shaderPath` — путь к `.srsl` (от `Resources/`).
- `defaultShader.uniforms` / `defaultShader.samplers` — значения свойств: `id` (= имя переменной в шейдере),
  `type` (`ShaderVarType`: `Float`, `Int`, `Vec2`, `Vec3`, `Vec4`, `Sampler2D`, ...) и `value`
  (для сэмплера — путь к текстуре).
- Значение, совпадающее со значением по умолчанию из шейдера, не сохраняется.
- `shaderDefines` — макросы, которые материал передаёт в шейдер (`HAS_NORMAL`, `HAS_ORM`, `HAS_ALPHA`, ...).
  В редакторе они выставляются флагами группы `Params` (`hasNormals`, `hasORM`, `hasAlpha`, ...).
  Изменение макросов пересобирает вариант шейдера.

Фрагмент `.mat` (сокращён):

```
sra format
0-r:Root
	1-o:asset
		2-v:type
			3-s:FileMaterialResource
		2-o:ptr
			3-o:data
				4-v:type
					5-s:MaterialData
				4-o:ptr
					5-a:shaderDefines
						6-k:item
							7-v:first
								8-s:HAS_NORMAL
							7-v:second
								8-s:
					5-o:defaultShader
						6-v:shaderPath
							7-s:Engine/Shaders/standard.srsl
						6-a:uniforms
							7-k:i
								8-o:d
									9-v:id
										10-s:color
									9-v:type
										10-s:Vec4
									9-o:value
										10-v:x
											11-f:1
										...
						6-a:samplers
							7-k:i
								8-o:d
									9-v:id
										10-s:diffuse
									9-v:type
										10-s:Sampler2D
									9-v:value
										10-s:Engine/Textures/default_improved.png
```

Свойство, не используемое ни одной точкой входа в данном варианте шейдера, в материале не появится.

## Примеры

### Стандартный меш с переопределяемыми функциями

`standard.srsl` подключает `Common/standard-header.srsl` (настройки пайплайна, SSBO костей) и
`Common/standard-vertex.srsl` (`vertex()` + `[[shared]] mat3 TBN`). Расширение через макросы-хуки:

- `SR_STANDARD_VERTEX_POSITION_FUNC` — `vertex()` вызовет вашу `vec3 CalculateVertexPosition()` вместо `VERTEX`;
- `STANDARD_SHADER_CUSTOM_FRAGMENT` — нужно самому определить `fragment_uv()`, `fragment_diffuse(vec2)`, `fragment_normal(vec2)`.

Пример (сокращённый `grass.srsl`):

```glsl
[[uniform], [public]] sampler2D windMask;

void fragment_depth_buffer_discard() {
    if ((texture(diffuse, UV) * color).a <= alphaThreshold) {
        discard;
    }
}

#define SR_STANDARD_VERTEX_POSITION_FUNC

vec3 CalculateVertexPosition() {
    return VERTEX + NORMAL * sin(TIME * 0.0005) * 0.1;
}

#include <Engine/Shaders/standard.srsl>

CullMode None;   // настройка после include переопределяет значение из standard-header
```

Функции и переменные можно использовать до их объявления в файле (`diffuse`, `color` объявлены в `standard.srsl`
ниже по тексту). Если настройка пайплайна встречается несколько раз, побеждает последняя.

### Полноэкранный пост-эффект

```glsl
ShaderType PostProcessing;
PolygonMode Fill;
CullMode Back;
DepthCompare LessOrEqual;
PrimitiveTopology TriangleList;
BlendEnabled false;
DepthWrite false;
DepthTest false;

[[uniform]] sampler2D colorMap;
[[public], [uniform(SHARED)]] float vignetteIntensity = 0.5;

[[shared]] vec2 uv;

void vertex() {
    uv = vec2(float((VERTEX_INDEX << 1) & 2), float(VERTEX_INDEX & 2));
    OUT_POSITION = vec4(uv * 2.0 - 1.0, 0.0, 1.0);
}

void fragment() {
    COLOR = texture(colorMap, uv);
}
```

### Compute с SSBO и shared-памятью

```glsl
ShaderType Compute;

[[uniform]] sampler2D hdrTexture;
[[uniform]] vec2 resolution;
[[ssbo(reductionOut)]] float[] reductionOut;
[[shared(workgroup)]] float[256] shSum;

[[THREADS(16, 16, 1)]]
void compute() {
    uint tid = gl_LocalInvocationIndex;
    ...
    barrier();
    ...
}
```

### SSBO со структурами и инстансингом

```glsl
struct SynapseRenderData {
    vec3 from;
    vec3 to;
    vec4 startColor;
    vec4 endColor;
};

[[ssbo(synapses)]] uint synapsesCount;
[[ssbo(synapses)]] SynapseRenderData[] synapses;

[[shared]] vec4 startColor;

void vertex() {
    startColor = synapses[gl_InstanceIndex].startColor;
    ...
}
```

## Тесты

Модульные тесты транслятора — `Resources/ModuleTests/SRSL/*.srsl`. Тест `SRSLTest`
([SRSLTest.h](../Engine/inc/Engine/Tests/SRSLTest.h)) компилирует каждый файл в GLSL, пишет результат в
`ModuleTests/SRSL/Result/` и сравнивает с `ModuleTests/SRSL/Expected/`. Эти файлы — хорошие минимальные примеры
отдельных возможностей языка (массивы, SSBO, циклы, workgroup-память и т.д.).

## Подводные камни

- `ShaderType` обязателен — без него шейдер не загрузится.
- Переменная объявлена, но не используется из точки входа → её нет в сгенерированном коде и в материале.
  Если свойство «пропало» из материала — проверьте, достижимо ли оно из `vertex()/fragment()` при текущих макросах.
- Размер массива пишется у типа (`vec4[64] x`), а не у имени, для объявлений верхнего уровня.
- Только `#include <...>`, кавычки `"..."` не поддерживаются. Путь — от `Resources/`.
- Нет `#elif` и макросов со значениями.
- Uniform-блоки выравниваются по 16 байт, поля внутри сортируются по размеру — не полагайтесь на порядок объявления.
- `[[readonly]]` и `[[writeonly]]` одновременно на SSBO — предупреждение и игнорирование.
- Шейдер должен компилироваться и в GLSL, и в WGSL. Избегайте GLSL-специфики, которой нет в WGSL
  (например, неявных преобразований `int ↔ float` — пишите `float(x)`).
- Не редактируйте файлы в кэше `Shaders/` — они перегенерируются из `.srsl`.
