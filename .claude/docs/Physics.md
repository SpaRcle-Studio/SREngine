# Физика (PhysX)

- `PhysicsScene::Flush` сначала добавляет тела, потом удаляет. `Register` убирает тело из очереди удаления, чтобы выключение+включение в одном кадре не выкидывало его.
- `AddRigidbody/RemoveRigidbody` проверяют `pActor->getScene()`: удаление может прийти дважды (`OnDisable`, затем `OnDestroy`).
- `PhysicsScene::Remove` не ставит дубли: `Flush` освобождает уничтоженное тело (`AutoFree`) на первой записи, вторая становится nullptr (ассерт в `Flush`). В редакторе физика на паузе и `Flush` не зовётся до запуска/выгрузки сцены, поэтому очереди копятся.
- `PhysXPhysicsWorld::SynchronizeStatic` кукает ≤ `maxCookPerFrame` треугольных мешей за кадр. Позиция статических тел обновляется до проверки лимита — иначе тело из пула остаётся на старом месте и сквозь него проваливаются.
- Кукинг (`PhysXCollisionShape::CreateTriangleMesh`): `createTriangleMesh` с insertion callback без сериализации, BVH34 при `PX_SSE2`, `suppressTriangleMeshRemapTable`.
