//
// Created by Monika on 23.07.2026.
//

#ifndef SR_ENGINE_CORE_CONTAINER_TESTS_H
#define SR_ENGINE_CORE_CONTAINER_TESTS_H

#include <Engine/stdInclude.h>

#include <Utils/Tests/TestManager.h>
#include <Utils/Memory/Allocator.h>
#include <Utils/Types/Map.h>
#include <Utils/Types/Set.h>

namespace SR_CORE_NS::Tests {
    // =========================================================================
    // MapTest
    // =========================================================================
    class MapTest : public SR_UTILS_NS::ITestController {
        SR_CLASS()
    public:
        SR_UTILS_NS::TestExecutionResult Run() override {
            SR_TRACY_ZONE;

            if (!TestBasicInsertAndFind())  { return SR_UTILS_NS::TestExecutionResult::Error; }
            if (!TestDuplicateInsert())     { return SR_UTILS_NS::TestExecutionResult::Error; }
            if (!TestOperatorBracket())     { return SR_UTILS_NS::TestExecutionResult::Error; }
            if (!TestErase())               { return SR_UTILS_NS::TestExecutionResult::Error; }
            if (!TestClear())               { return SR_UTILS_NS::TestExecutionResult::Error; }
            if (!TestCopyAndMove())         { return SR_UTILS_NS::TestExecutionResult::Error; }
            if (!TestInitializerList())     { return SR_UTILS_NS::TestExecutionResult::Error; }
            if (!TestOrdering())            { return SR_UTILS_NS::TestExecutionResult::Error; }
            if (!TestIterator())            { return SR_UTILS_NS::TestExecutionResult::Error; }
            if (!TestLowerUpperBound())     { return SR_UTILS_NS::TestExecutionResult::Error; }
            if (!TestWithAllocator())       { return SR_UTILS_NS::TestExecutionResult::Error; }
            if (!TestDetachAllocator())     { return SR_UTILS_NS::TestExecutionResult::Error; }
            if (!TestEmplace())             { return SR_UTILS_NS::TestExecutionResult::Error; }
            if (!TestLargeInsert())         { return SR_UTILS_NS::TestExecutionResult::Error; }

            return SR_UTILS_NS::TestExecutionResult::Success;
        }

    private:
        bool TestBasicInsertAndFind() {
            SR_UTILS_NS::Map<int, int> map;

            auto [it1, ok1] = map.insert(1, 100);
            if (!ok1 || it1->second != 100) {
                SR_ERROR("MapTest::TestBasicInsertAndFind() : insert failed!");
                return false;
            }
            map.insert(2, 200);

            auto it = map.find(1);
            if (it == map.end() || it->second != 100) {
                SR_ERROR("MapTest::TestBasicInsertAndFind() : find failed!");
                return false;
            }
            if (map.find(999) != map.end()) {
                SR_ERROR("MapTest::TestBasicInsertAndFind() : find of missing key should return end()!");
                return false;
            }
            if (map.size() != 2) {
                SR_ERROR("MapTest::TestBasicInsertAndFind() : size mismatch!");
                return false;
            }
            if (!map.contains(1) || !map.contains(2) || map.contains(999)) {
                SR_ERROR("MapTest::TestBasicInsertAndFind() : contains check failed!");
                return false;
            }
            return true;
        }

        bool TestDuplicateInsert() {
            SR_UTILS_NS::Map<int, int> map;
            map.insert(42, 1);
            auto [it, ok] = map.insert(42, 2);
            if (ok) {
                SR_ERROR("MapTest::TestDuplicateInsert() : duplicate insert should return false!");
                return false;
            }
            if (it->second != 1) {
                SR_ERROR("MapTest::TestDuplicateInsert() : existing value must not be overwritten!");
                return false;
            }
            if (map.size() != 1) {
                SR_ERROR("MapTest::TestDuplicateInsert() : size should remain 1!");
                return false;
            }
            return true;
        }

        bool TestOperatorBracket() {
            SR_UTILS_NS::Map<int, int> map;
            map[1] = 10;
            map[2] = 20;
            map[1] = 15;

            if (map[1] != 15) {
                SR_ERROR("MapTest::TestOperatorBracket() : assignment via [] failed!");
                return false;
            }
            if (map[2] != 20) {
                SR_ERROR("MapTest::TestOperatorBracket() : read via [] failed!");
                return false;
            }
            map[3] = 30;
            if (map[3] != 30 || map.size() != 3) {
                SR_ERROR("MapTest::TestOperatorBracket() : new key via [] failed!");
                return false;
            }
            return true;
        }

        bool TestErase() {
            SR_UTILS_NS::Map<int, int> map;
            map.insert(1, 10);
            map.insert(2, 20);
            map.insert(3, 30);

            if (!map.erase(2)) {
                SR_ERROR("MapTest::TestErase() : erase should return true!");
                return false;
            }
            if (map.size() != 2 || map.contains(2)) {
                SR_ERROR("MapTest::TestErase() : element should be gone!");
                return false;
            }
            if (map.erase(999)) {
                SR_ERROR("MapTest::TestErase() : erase of missing key should return false!");
                return false;
            }
            if (!map.contains(1) || !map.contains(3)) {
                SR_ERROR("MapTest::TestErase() : remaining elements must stay!");
                return false;
            }
            return true;
        }

        bool TestClear() {
            SR_UTILS_NS::Map<int, int> map;
            for (int i = 0; i < 10; ++i) map.insert(i, i * 10);

            map.clear();
            if (!map.empty() || map.size() != 0) {
                SR_ERROR("MapTest::TestClear() : map should be empty after clear!");
                return false;
            }
            map.insert(100, 1000);
            if (!map.contains(100) || map.size() != 1) {
                SR_ERROR("MapTest::TestClear() : insert after clear failed!");
                return false;
            }
            return true;
        }

        bool TestCopyAndMove() {
            SR_UTILS_NS::Map<int, int> original;
            original.insert(1, 10);
            original.insert(2, 20);
            original.insert(3, 30);

            SR_UTILS_NS::Map<int, int> copy(original);
            if (copy.size() != 3 || !copy.contains(1) || !copy.contains(2) || !copy.contains(3)) {
                SR_ERROR("MapTest::TestCopyAndMove() : copy constructor failed!");
                return false;
            }

            copy[1] = 999;
            if (original[1] != 10) {
                SR_ERROR("MapTest::TestCopyAndMove() : copy must be independent!");
                return false;
            }

            SR_UTILS_NS::Map<int, int> moved(std::move(copy));
            if (moved.size() != 3 || moved[1] != 999) {
                SR_ERROR("MapTest::TestCopyAndMove() : move constructor failed!");
                return false;
            }
            if (!copy.empty()) {
                SR_ERROR("MapTest::TestCopyAndMove() : moved-from map must be empty!");
                return false;
            }

            SR_UTILS_NS::Map<int, int> assigned;
            assigned = original;
            if (assigned.size() != 3 || assigned[2] != 20) {
                SR_ERROR("MapTest::TestCopyAndMove() : copy assignment failed!");
                return false;
            }

            SR_UTILS_NS::Map<int, int> moveAssigned;
            moveAssigned = std::move(assigned);
            if (moveAssigned.size() != 3 || !assigned.empty()) {
                SR_ERROR("MapTest::TestCopyAndMove() : move assignment failed!");
                return false;
            }
            return true;
        }

        bool TestInitializerList() {
            SR_UTILS_NS::Map<int, int> map = { {1, 10}, {2, 20}, {3, 30} };
            if (map.size() != 3 || !map.contains(1) || !map.contains(2) || !map.contains(3)) {
                SR_ERROR("MapTest::TestInitializerList() : initializer_list ctor failed!");
                return false;
            }
            map = { {10, 100}, {20, 200} };
            if (map.size() != 2 || !map.contains(10) || map.contains(1)) {
                SR_ERROR("MapTest::TestInitializerList() : initializer_list assignment failed!");
                return false;
            }
            return true;
        }

        bool TestOrdering() {
            SR_UTILS_NS::Map<int, int> map;
            // Insert in random order
            for (int v : { 5, 3, 8, 1, 4, 7, 9, 2, 6 }) {
                map.insert(v, v * 10);
            }

            // In-order traversal must be ascending
            int prev = std::numeric_limits<int>::min();
            for (auto& [k, v] : map) {
                if (k <= prev) {
                    SR_ERROR("MapTest::TestOrdering() : keys are not in ascending order (prev={}, cur={})!", prev, k);
                    return false;
                }
                if (v != k * 10) {
                    SR_ERROR("MapTest::TestOrdering() : value mismatch for key {}!", k);
                    return false;
                }
                prev = k;
            }
            if (map.size() != 9) {
                SR_ERROR("MapTest::TestOrdering() : wrong size after insert!");
                return false;
            }
            return true;
        }

        bool TestIterator() {
            SR_UTILS_NS::Map<int, int> map;
            map.insert(1, 10);
            map.insert(2, 20);
            map.insert(3, 30);

            // Forward iteration
            int sum = 0, count = 0;
            for (auto it = map.begin(); it != map.end(); ++it) {
                sum += it->second;
                ++count;
            }
            if (count != 3 || sum != 60) {
                SR_ERROR("MapTest::TestIterator() : forward iteration failed (count={}, sum={})!", count, sum);
                return false;
            }

            // Reverse iteration via --
            auto it = map.end();
            --it;
            if (it->first != 3) {
                SR_ERROR("MapTest::TestIterator() : --end() must point to maximum key!");
                return false;
            }
            --it;
            if (it->first != 2) {
                SR_ERROR("MapTest::TestIterator() : reverse step failed!");
                return false;
            }

            // const iterator
            const auto& cmap = map;
            count = 0;
            for (auto it2 = cmap.cbegin(); it2 != cmap.cend(); ++it2) ++count;
            if (count != 3) {
                SR_ERROR("MapTest::TestIterator() : const iterator count mismatch!");
                return false;
            }

            // erase via iterator
            auto it3 = map.find(2);
            auto it4 = map.erase(it3);
            if (it4->first != 3) {
                SR_ERROR("MapTest::TestIterator() : erase(iterator) must return next iterator!");
                return false;
            }
            if (map.size() != 2) {
                SR_ERROR("MapTest::TestIterator() : size after erase(iterator) wrong!");
                return false;
            }
            return true;
        }

        bool TestLowerUpperBound() {
            SR_UTILS_NS::Map<int, int> map;
            for (int i = 0; i < 10; i += 2) map.insert(i, i); // 0,2,4,6,8

            // lower_bound(3) → first key >= 3 → key 4
            auto lb = map.lower_bound(3);
            if (lb == map.end() || lb->first != 4) {
                SR_ERROR("MapTest::TestLowerUpperBound() : lower_bound(3) should give key 4!");
                return false;
            }

            // lower_bound(4) → exact match → key 4
            lb = map.lower_bound(4);
            if (lb == map.end() || lb->first != 4) {
                SR_ERROR("MapTest::TestLowerUpperBound() : lower_bound(4) should give key 4!");
                return false;
            }

            // upper_bound(4) → first key > 4 → key 6
            auto ub = map.upper_bound(4);
            if (ub == map.end() || ub->first != 6) {
                SR_ERROR("MapTest::TestLowerUpperBound() : upper_bound(4) should give key 6!");
                return false;
            }

            // upper_bound(8) → past last → end()
            ub = map.upper_bound(8);
            if (ub != map.end()) {
                SR_ERROR("MapTest::TestLowerUpperBound() : upper_bound(max) should give end()!");
                return false;
            }

            // lower_bound past all keys → end()
            lb = map.lower_bound(100);
            if (lb != map.end()) {
                SR_ERROR("MapTest::TestLowerUpperBound() : lower_bound past all keys should give end()!");
                return false;
            }

            // Count elements in range [3, 7) using lower_bound + upper_bound
            int cnt = 0;
            for (auto it = map.lower_bound(3); it != map.upper_bound(6); ++it) ++cnt;
            if (cnt != 2) { // keys 4, 6
                SR_ERROR("MapTest::TestLowerUpperBound() : range count [3,7) should be 2, got {}!", cnt);
                return false;
            }
            return true;
        }

        bool TestWithAllocator() {
            SR_UTILS_NS::MonotonicAllocator allocator(16 * 1024);
            SR_UTILS_NS::Map<int, int> map(&allocator);

            for (int i = 0; i < 50; ++i) map.insert(i, i * 2);

            if (map.size() != 50) {
                SR_ERROR("MapTest::TestWithAllocator() : size mismatch with custom allocator!");
                return false;
            }
            if (map.GetAllocator() != &allocator) {
                SR_ERROR("MapTest::TestWithAllocator() : allocator pointer mismatch!");
                return false;
            }

            // Verify ordering still holds
            int prev = std::numeric_limits<int>::min();
            for (auto& [k, v] : map) {
                if (k <= prev) {
                    SR_ERROR("MapTest::TestWithAllocator() : ordering broken with custom allocator!");
                    return false;
                }
                prev = k;
            }
            return true;
        }

        bool TestDetachAllocator() {
            SR_UTILS_NS::MonotonicAllocator allocator(8 * 1024);
            SR_UTILS_NS::Map<int, int> src(&allocator);
            src.insert(1, 10);
            src.insert(2, 20);

            SR_UTILS_NS::Map<int, int> det = src.DetachAllocator();
            if (det.GetAllocator() != nullptr) {
                SR_ERROR("MapTest::TestDetachAllocator() : detached map must have no allocator!");
                return false;
            }
            if (det.size() != 2 || det[1] != 10 || det[2] != 20) {
                SR_ERROR("MapTest::TestDetachAllocator() : detached map has wrong content!");
                return false;
            }
            return true;
        }

        bool TestEmplace() {
            SR_UTILS_NS::Map<int, std::string> map;

            auto [it1, ok1] = map.emplace(1, "hello");
            if (!ok1 || it1->second != "hello") {
                SR_ERROR("MapTest::TestEmplace() : emplace failed!");
                return false;
            }
            auto [it2, ok2] = map.emplace(1, "world");
            if (ok2 || it2->second != "hello") {
                SR_ERROR("MapTest::TestEmplace() : emplace must not overwrite existing key!");
                return false;
            }
            if (map.size() != 1) {
                SR_ERROR("MapTest::TestEmplace() : size after duplicate emplace should be 1!");
                return false;
            }
            return true;
        }

        bool TestLargeInsert() {
            SR_UTILS_NS::Map<int, int> map;
            const int N = 500;

            // Insert in descending order to stress the tree
            for (int i = N - 1; i >= 0; --i) map.insert(i, i);

            if (static_cast<int>(map.size()) != N) {
                SR_ERROR("MapTest::TestLargeInsert() : size mismatch after {} inserts!", N);
                return false;
            }

            // Verify all present and in order
            int expected = 0;
            for (auto& [k, v] : map) {
                if (k != expected || v != expected) {
                    SR_ERROR("MapTest::TestLargeInsert() : wrong element at position {}!", expected);
                    return false;
                }
                ++expected;
            }

            // Erase every even key
            for (int i = 0; i < N; i += 2) map.erase(i);
            if (static_cast<int>(map.size()) != N / 2) {
                SR_ERROR("MapTest::TestLargeInsert() : size mismatch after mass erase!");
                return false;
            }

            // Remaining keys are all odd and in order
            int prevKey = -1;
            for (auto& [k, v] : map) {
                if (k % 2 == 0 || k <= prevKey) {
                    SR_ERROR("MapTest::TestLargeInsert() : ordering or parity wrong after mass erase!");
                    return false;
                }
                prevKey = k;
            }
            return true;
        }
    };

    // =========================================================================
    // SetTest
    // =========================================================================
    class SetTest : public SR_UTILS_NS::ITestController {
        SR_CLASS()
    public:
        SR_UTILS_NS::TestExecutionResult Run() override {
            SR_TRACY_ZONE;

            if (!TestBasicInsertAndFind()) { return SR_UTILS_NS::TestExecutionResult::Error; }
            if (!TestDuplicateInsert())    { return SR_UTILS_NS::TestExecutionResult::Error; }
            if (!TestErase())              { return SR_UTILS_NS::TestExecutionResult::Error; }
            if (!TestClear())              { return SR_UTILS_NS::TestExecutionResult::Error; }
            if (!TestCopyAndMove())        { return SR_UTILS_NS::TestExecutionResult::Error; }
            if (!TestInitializerList())    { return SR_UTILS_NS::TestExecutionResult::Error; }
            if (!TestOrdering())           { return SR_UTILS_NS::TestExecutionResult::Error; }
            if (!TestIterator())           { return SR_UTILS_NS::TestExecutionResult::Error; }
            if (!TestLowerUpperBound())    { return SR_UTILS_NS::TestExecutionResult::Error; }
            if (!TestWithAllocator())      { return SR_UTILS_NS::TestExecutionResult::Error; }
            if (!TestDetachAllocator())    { return SR_UTILS_NS::TestExecutionResult::Error; }
            if (!TestEmplace())            { return SR_UTILS_NS::TestExecutionResult::Error; }
            if (!TestLargeInsert())        { return SR_UTILS_NS::TestExecutionResult::Error; }

            return SR_UTILS_NS::TestExecutionResult::Success;
        }

    private:
        bool TestBasicInsertAndFind() {
            SR_UTILS_NS::Set<int> set;

            auto [it1, ok1] = set.insert(1);
            if (!ok1 || *it1 != 1) {
                SR_ERROR("SetTest::TestBasicInsertAndFind() : insert failed!");
                return false;
            }
            set.insert(2);

            if (set.find(1) == set.end() || *set.find(1) != 1) {
                SR_ERROR("SetTest::TestBasicInsertAndFind() : find failed!");
                return false;
            }
            if (set.find(999) != set.end()) {
                SR_ERROR("SetTest::TestBasicInsertAndFind() : find of missing value should return end()!");
                return false;
            }
            if (set.size() != 2) {
                SR_ERROR("SetTest::TestBasicInsertAndFind() : size mismatch!");
                return false;
            }
            if (!set.contains(1) || !set.contains(2) || set.contains(999)) {
                SR_ERROR("SetTest::TestBasicInsertAndFind() : contains check failed!");
                return false;
            }
            return true;
        }

        bool TestDuplicateInsert() {
            SR_UTILS_NS::Set<int> set;
            set.insert(42);
            auto [it, ok] = set.insert(42);
            if (ok) {
                SR_ERROR("SetTest::TestDuplicateInsert() : duplicate insert should return false!");
                return false;
            }
            if (*it != 42 || set.size() != 1) {
                SR_ERROR("SetTest::TestDuplicateInsert() : wrong state after duplicate insert!");
                return false;
            }
            return true;
        }

        bool TestErase() {
            SR_UTILS_NS::Set<int> set;
            set.insert(1); set.insert(2); set.insert(3);

            if (!set.erase(2) || set.contains(2) || set.size() != 2) {
                SR_ERROR("SetTest::TestErase() : erase failed!");
                return false;
            }
            if (set.erase(999)) {
                SR_ERROR("SetTest::TestErase() : erase of missing value should return false!");
                return false;
            }
            if (!set.contains(1) || !set.contains(3)) {
                SR_ERROR("SetTest::TestErase() : remaining elements must stay!");
                return false;
            }
            return true;
        }

        bool TestClear() {
            SR_UTILS_NS::Set<int> set;
            for (int i = 0; i < 10; ++i) set.insert(i);

            set.clear();
            if (!set.empty() || set.size() != 0) {
                SR_ERROR("SetTest::TestClear() : set should be empty after clear!");
                return false;
            }
            set.insert(100);
            if (!set.contains(100) || set.size() != 1) {
                SR_ERROR("SetTest::TestClear() : insert after clear failed!");
                return false;
            }
            return true;
        }

        bool TestCopyAndMove() {
            SR_UTILS_NS::Set<int> original;
            original.insert(1); original.insert(2); original.insert(3);

            SR_UTILS_NS::Set<int> copy(original);
            if (copy.size() != 3 || !copy.contains(1) || !copy.contains(2) || !copy.contains(3)) {
                SR_ERROR("SetTest::TestCopyAndMove() : copy constructor failed!");
                return false;
            }

            SR_UTILS_NS::Set<int> moved(std::move(copy));
            if (moved.size() != 3 || !moved.contains(1)) {
                SR_ERROR("SetTest::TestCopyAndMove() : move constructor failed!");
                return false;
            }
            if (!copy.empty()) {
                SR_ERROR("SetTest::TestCopyAndMove() : moved-from set must be empty!");
                return false;
            }

            SR_UTILS_NS::Set<int> assigned;
            assigned = original;
            if (assigned.size() != 3 || !assigned.contains(2)) {
                SR_ERROR("SetTest::TestCopyAndMove() : copy assignment failed!");
                return false;
            }

            SR_UTILS_NS::Set<int> moveAssigned;
            moveAssigned = std::move(assigned);
            if (moveAssigned.size() != 3 || !assigned.empty()) {
                SR_ERROR("SetTest::TestCopyAndMove() : move assignment failed!");
                return false;
            }
            return true;
        }

        bool TestInitializerList() {
            SR_UTILS_NS::Set<int> set = { 1, 2, 3 };
            if (set.size() != 3 || !set.contains(1) || !set.contains(2) || !set.contains(3)) {
                SR_ERROR("SetTest::TestInitializerList() : initializer_list ctor failed!");
                return false;
            }
            set = { 10, 20 };
            if (set.size() != 2 || !set.contains(10) || set.contains(1)) {
                SR_ERROR("SetTest::TestInitializerList() : initializer_list assignment failed!");
                return false;
            }
            return true;
        }

        bool TestOrdering() {
            SR_UTILS_NS::Set<int> set;
            for (int v : { 5, 3, 8, 1, 4, 7, 9, 2, 6 }) set.insert(v);

            int prev = std::numeric_limits<int>::min();
            for (int v : set) {
                if (v <= prev) {
                    SR_ERROR("SetTest::TestOrdering() : values not in ascending order (prev={}, cur={})!", prev, v);
                    return false;
                }
                prev = v;
            }
            if (set.size() != 9) {
                SR_ERROR("SetTest::TestOrdering() : wrong size!");
                return false;
            }
            return true;
        }

        bool TestIterator() {
            SR_UTILS_NS::Set<int> set;
            set.insert(1); set.insert(2); set.insert(3);

            int sum = 0, count = 0;
            for (auto it = set.begin(); it != set.end(); ++it) { sum += *it; ++count; }
            if (count != 3 || sum != 6) {
                SR_ERROR("SetTest::TestIterator() : forward iteration failed!");
                return false;
            }

            // Reverse via --
            auto it = set.end();
            --it;
            if (*it != 3) {
                SR_ERROR("SetTest::TestIterator() : --end() must point to maximum element!");
                return false;
            }
            --it;
            if (*it != 2) {
                SR_ERROR("SetTest::TestIterator() : reverse step failed!");
                return false;
            }

            // erase via iterator
            auto it2 = set.find(2);
            auto it3 = set.erase(it2);
            if (*it3 != 3) {
                SR_ERROR("SetTest::TestIterator() : erase(iterator) must return next iterator!");
                return false;
            }
            if (set.size() != 2) {
                SR_ERROR("SetTest::TestIterator() : size after erase(iterator) wrong!");
                return false;
            }
            return true;
        }

        bool TestLowerUpperBound() {
            SR_UTILS_NS::Set<int> set;
            for (int i = 0; i < 10; i += 2) set.insert(i); // 0,2,4,6,8

            // lower_bound(3) → first element >= 3 → 4
            auto lb = set.lower_bound(3);
            if (lb == set.end() || *lb != 4) {
                SR_ERROR("SetTest::TestLowerUpperBound() : lower_bound(3) should give 4!");
                return false;
            }

            // lower_bound(4) → exact match → 4
            lb = set.lower_bound(4);
            if (lb == set.end() || *lb != 4) {
                SR_ERROR("SetTest::TestLowerUpperBound() : lower_bound(4) should give 4!");
                return false;
            }

            // upper_bound(4) → first element > 4 → 6
            auto ub = set.upper_bound(4);
            if (ub == set.end() || *ub != 6) {
                SR_ERROR("SetTest::TestLowerUpperBound() : upper_bound(4) should give 6!");
                return false;
            }

            // upper_bound(8) → past last → end()
            ub = set.upper_bound(8);
            if (ub != set.end()) {
                SR_ERROR("SetTest::TestLowerUpperBound() : upper_bound(max) should give end()!");
                return false;
            }

            // Count elements in [3, 7)
            int cnt = 0;
            for (auto it = set.lower_bound(3); it != set.upper_bound(6); ++it) ++cnt;
            if (cnt != 2) { // elements 4, 6
                SR_ERROR("SetTest::TestLowerUpperBound() : range count [3,7) should be 2, got {}!", cnt);
                return false;
            }
            return true;
        }

        bool TestWithAllocator() {
            SR_UTILS_NS::MonotonicAllocator allocator(16 * 1024);
            SR_UTILS_NS::Set<int> set(&allocator);

            for (int i = 0; i < 50; ++i) set.insert(i);

            if (set.size() != 50) {
                SR_ERROR("SetTest::TestWithAllocator() : size mismatch with custom allocator!");
                return false;
            }
            if (set.GetAllocator() != &allocator) {
                SR_ERROR("SetTest::TestWithAllocator() : allocator pointer mismatch!");
                return false;
            }

            int prev = std::numeric_limits<int>::min();
            for (int v : set) {
                if (v <= prev) {
                    SR_ERROR("SetTest::TestWithAllocator() : ordering broken with custom allocator!");
                    return false;
                }
                prev = v;
            }
            return true;
        }

        bool TestDetachAllocator() {
            SR_UTILS_NS::MonotonicAllocator allocator(8 * 1024);
            SR_UTILS_NS::Set<int> src(&allocator);
            src.insert(1); src.insert(2);

            SR_UTILS_NS::Set<int> det = src.DetachAllocator();
            if (det.GetAllocator() != nullptr) {
                SR_ERROR("SetTest::TestDetachAllocator() : detached set must have no allocator!");
                return false;
            }
            if (det.size() != 2 || !det.contains(1) || !det.contains(2)) {
                SR_ERROR("SetTest::TestDetachAllocator() : detached set has wrong content!");
                return false;
            }
            return true;
        }

        bool TestEmplace() {
            SR_UTILS_NS::Set<std::string> set;

            auto [it1, ok1] = set.emplace("hello");
            if (!ok1 || *it1 != "hello") {
                SR_ERROR("SetTest::TestEmplace() : emplace failed!");
                return false;
            }
            auto [it2, ok2] = set.emplace("hello");
            if (ok2 || *it2 != "hello") {
                SR_ERROR("SetTest::TestEmplace() : emplace must not insert duplicate!");
                return false;
            }
            if (set.size() != 1) {
                SR_ERROR("SetTest::TestEmplace() : size after duplicate emplace should be 1!");
                return false;
            }
            return true;
        }

        bool TestLargeInsert() {
            SR_UTILS_NS::Set<int> set;
            const int N = 500;

            // Insert in random-ish order
            for (int i = N - 1; i >= 0; --i) set.insert(i);

            if (static_cast<int>(set.size()) != N) {
                SR_ERROR("SetTest::TestLargeInsert() : size mismatch after {} inserts!", N);
                return false;
            }

            int expected = 0;
            for (int v : set) {
                if (v != expected) {
                    SR_ERROR("SetTest::TestLargeInsert() : wrong element at position {}!", expected);
                    return false;
                }
                ++expected;
            }

            for (int i = 0; i < N; i += 2) set.erase(i);
            if (static_cast<int>(set.size()) != N / 2) {
                SR_ERROR("SetTest::TestLargeInsert() : size mismatch after mass erase!");
                return false;
            }

            int prevVal = -1;
            for (int v : set) {
                if (v % 2 == 0 || v <= prevVal) {
                    SR_ERROR("SetTest::TestLargeInsert() : ordering or parity wrong after mass erase!");
                    return false;
                }
                prevVal = v;
            }
            return true;
        }
    };
}

#endif //SR_ENGINE_CORE_CONTAINER_TESTS_H
