# App — Design Document

## 📘 Overview
`App` is the executable entry point for the BasicBlocks project. It assembles and executes the full test workflow for the math library (`SMathLib`) and the DSA library (`DSALib`). `App` is responsible for selecting test contexts, building tester objects through a factory, and invoking the unified test runner interface.

---

## 🎯 Purpose and Scope
The `App` module is designed to:

- Launch the application and print basic build/version metadata.
- Provide a simple runtime path for conditional selection of test suites.
- Build the appropriate set of test runners using the `STestFactory` abstraction.
- Execute each tester through the common `ITestRunner` interface.
- Link the application against `SMathLib` and `DSALib` and copy their DLL artifacts next to `App.exe`.

It is not responsible for test logic or implementation details of individual test cases.

---

## 🧱 Architecture & Components

### `App/CMakeLists.txt`

- Defines the `App` executable target.
- Adds source files for the application itself, the factory, engine orchestrators, and all concrete tester objects.
- Links `App` privately against `SMathLib` and `DSALib`.
- Adds include directories for the app code and the two library dependencies.
- Registers a `POST_BUILD` custom command to copy `SMathLib` and `DSALib` DLLs into the `App` output directory.

### `App/main.cpp`

- Contains the process entry point `main()`.
- Prints version metadata using `PROJECT_VERSION` when available.
- Calls `helloFromDLL()` from `SMathLib` to verify DLL linkage and runtime availability.
- Sets a default `TestContext` to `All`.
- Constructs tester instances via `STestFactory::CreateTesters(ctx)`.
- Iterates over the returned `std::vector<std::unique_ptr<ITestRunner>>` and calls `RunAllTests()` on each valid tester.
- Includes a defensive null-test check before invocation.

### `App/interface/ITestRunner.h`

- Defines the `ITestRunner` interface.
- Declares a single pure virtual method:
  - `virtual void RunAllTests() = 0;`
- Ensures all concrete testers expose a unified execution contract.

### `App/TestFactory/STestFactory.h` and `STestFactory.cpp`

- Encapsulates tester selection logic.
- Exposes `static std::vector<std::unique_ptr<ITestRunner>> CreateTesters(TestContext ctx)`.
- Supports three contexts:
  - `TestContext::Math`
  - `TestContext::DSA`
  - `TestContext::All`
- Creates either:
  - `sMathTester`
  - `sDSATester`
  - both `sMathTester` and `sDSATester`
- Emits console diagnostic messages describing which tester groups are being provided.

### `App/TestEngine/sMathTester` and `App/TestEngine/sDSATester`

These classes implement `ITestRunner` and act as orchestrators for their respective domains.

#### `sMathTester`
- Builds the math test suite by creating:
  - `sCalcTester`
  - `sComplexTester`
- Implements `RunAllTests()` to:
  - print start/end separators,
  - call `Setup()` to populate the tester list,
  - iterate over the registered testers and invoke `RunAllTests()` on each.

#### `sDSATester`
- Builds the DSA test suite by creating:
  - `sHashTester`
  - `sStackTester`
  - `sListTester`
  - `sVectorTester`
  - `sQueueTester`
  - `sTuplePairTester`
  - `sStringTester`
- Implements `RunAllTests()` similarly to `sMathTester`.

### application test packages

#### `App/sMathTesters`
- Contains concrete math component testers.
- Each tester implements `RunAllTests()` and exercises an individual math-related feature or library contract.

#### `App/sDSATesters`
- Contains concrete DSA component testers.
- Each tester implements `RunAllTests()` and exercises a specific DSA component.
- For detailed DSA suite orchestration, see [sDSATest Design Document](SDSATest_Design_Document.md).

---

## 🔄 Execution Flow

```text
main() -> STestFactory::CreateTesters(ctx) -> [sMathTester | sDSATester | both] -> RunAllTests()
  -> Setup() -> create concrete testers -> for each tester: RunAllTests()
```

1. `main()` starts.
2. Version metadata is printed.
3. `helloFromDLL()` confirms DLL connectivity.
4. The chosen `TestContext` is passed to `STestFactory`.
5. `STestFactory` returns a vector of `ITestRunner` instances.
6. `main()` iterates the vector and dispatches `RunAllTests()` for each tester.
7. Each orchestrator creates and runs its specific suite of concrete testers.

---

## 📦 Dependencies

- `SMathLib`
  - Provides math library symbols and the `helloFromDLL()` entry point.
  - Linked into `App` and copied as a runtime DLL.

- `DSALib`
  - Provides data structure library symbols.
  - Linked into `App` and copied as a runtime DLL.

- `App` relies on both libraries only through the test harness and does not expose library internals directly.

---

## 🧠 Design Rationale

- **Single execution contract**: `ITestRunner` unifies all testers behind one interface, making the test execution path easy to extend.
- **Factory-based construction**: `STestFactory` centralizes context selection so `main()` remains lightweight and stable.
- **Separated orchestration**: `sMathTester` and `sDSATester` encapsulate test suite composition, keeping concrete test registration out of `main()`.
- **DLL verification**: `helloFromDLL()` in `main()` ensures application startup validates the dynamic dependency chain quickly.

---

## 🛠️ Extension Points

- Add new `TestContext` options to `TestContext` and update `STestFactory::CreateTesters()`.
- Add new tester categories by introducing new orchestrators similar to `sMathTester` and `sDSATester`.
- Add or replace concrete testers under `App/sMathTesters` or `App/sDSATesters` without changing `main()`.
- Introduce command-line parsing in `main()` to choose `TestContext` at runtime.

---

## 📍 Notes

- `App` is intentionally minimal and acts as a harness, not a library component.
- All application-side test orchestration is performed with `std::unique_ptr<ITestRunner>` to enforce ownership and avoid raw pointer lifetimes.
- The `App` module is well-suited for future test runner extensions such as selective per-test filtering or interactive mode.