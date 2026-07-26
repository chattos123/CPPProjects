# Comprehensive Architecture & Technical Documentation: STestEngine

**Author:** Soumyajit C  
**Date:** 2026  
**Language:** C++ (C++14 / C++17 compatible)  
**Architecture:** Modular Test Framework utilizing **Composite** and **Factory** Design Patterns  

---

## Table of Contents
1. [Architectural Overview](#1-architectural-overview)
2. [Design Patterns Applied](#2-design-patterns-applied)
3. [Interface & Factory Specification](#3-interface--factory-specification)
   - [ITestRunner Interface](#31-itestrunner-interface)
   - [TestContext Enumeration](#32-testcontext-enumeration)
   - [STestFactory Header & Implementation](#33-stestfactory-header--implementation)
4. [Composite Test Suite Aggregators](#4-composite-test-suite-aggregators)
   - [sMathTester Suite](#41-smathtester-suite)
   - [sDSATester Suite](#42-sdsatester-suite)
5. [Concrete Leaf Test Implementations](#5-concrete-leaf-test-implementations)
   - [sCalcTester Implementation](#51-scalctester-implementation)
   - [sComplexTester Implementation](#52-scomplextester-implementation)
   - [sVectorTester Implementation](#53-svectortester-implementation)
6. [Top-Level Engine Orchestration](#6-top-level-engine-orchestration)
   - [STestEngine Header & Implementation](#61-stestengine-header--implementation)
   - [Main Entry Point Example](#62-main-entry-point-example)

---

## 2. Class Diagram

```mermaid
graph TD
    Engine[STestEngine] -->|1. Requests Testers| Factory[STestFactory]
    Factory -->|2. Instantiates| MathComposite[sMathTester]
    Factory -->|2. Instantiates| DSAComposite[sDSATester]

    subgraph Interface Level
        ITR[<<Interface>><br/>ITestRunner]
    end

    MathComposite -.->|Implements| ITR
    DSAComposite -.->|Implements| ITR

    subgraph Math Suite
        MathComposite --> Calc[sCalcTester]
        MathComposite --> Complex[sComplexTester]
    end

    subgraph DSA Suite
        DSAComposite --> Vector[sVectorTester]
        DSAComposite --> Hash[sHashTester]
        DSAComposite --> Stack[sStackTester]
        DSAComposite --> Queue[sQueueTester]
    end

    Calc -.->|Implements| ITR
    Complex -.->|Implements| ITR
    Vector -.->|Implements| ITR
    Hash -.->|Implements| ITR
    Stack -.->|Implements| ITR
    Queue -.->|Implements| ITR
```

## 1. Architectural Overview & Class Diagrams

The `STestEngine` framework provides an extensible, decoupled, and hierarchical test execution environment. Individual data structure and mathematical module tests are encapsulated into concrete leaf runners, which are then aggregated into higher-level domain suites (`sMathTester` and `sDSATester`). A static factory handles context-driven instantiation, while the top-level `STestEngine` drives full lifecycle execution.

---

### 1.1 Structural UML Class Diagram

The following class diagram details the relationships, inheritance hierarchies, aggregation bounds, and design patterns utilized across the framework:

```mermaid
classDiagram
    class ITestRunner {
        <<Interface>>
        +virtual ~ITestRunner()
        +virtual RunAllTests()* void
    }

    class TestContext {
        <<Enumeration>>
        Math
        DSA
        All
    }

    class STestFactory {
        +CreateTesters(ctx: TestContext)$ vector~unique_ptr~ITestRunner~~
    }

    class STestEngine {
        -activeTesters: vector~unique_ptr~ITestRunner~~
        +Execute(ctx: TestContext) int
    }

    class sMathTester {
        -testers: vector~unique_ptr~ITestRunner~~
        -Setup() void
        +RunAllTests() void
    }

    class sDSATester {
        -testers: vector~unique_ptr~ITestRunner~~
        -Setup() void
        +RunAllTests() void
    }

    class sCalcTester {
        -TestCalculator() void
        +RunAllTests() void
    }

    class sComplexTester {
        -TestComplex() void
        +RunAllTests() void
    }

    class sVectorTester {
        -TestVector() void
        -TestVectorT() void
        +RunAllTests() void
    }

    %% Realization (Inheritance)
    ITestRunner <|.. sMathTester : Realizes
    ITestRunner <|.. sDSATester : Realizes
    ITestRunner <|.. sCalcTester : Realizes
    ITestRunner <|.. sComplexTester : Realizes
    ITestRunner <|.. sVectorTester : Realizes

    %% Aggregation / Composition (Composite Pattern)
    sMathTester o-- "1..*" ITestRunner : Aggregates Sub-Runners
    sDSATester o-- "1..*" ITestRunner : Aggregates Sub-Runners
    STestEngine o-- "0..*" ITestRunner : Manages Active Runs

    %% Dependencies
    STestEngine ..> STestFactory : Requests Creation
    STestFactory ..> TestContext : Evaluates Scope
    STestFactory ..> sMathTester : Instantiates
    STestFactory ..> sDSATester : Instantiates
```

The test architecture provides an extensible, decoupled, and hierarchical test execution environment. Individual data structure and mathematical module tests are encapsulated into concrete leaf runners, which are then aggregated into higher-level domain suites (`sMathTester` and `sDSATester`). A static factory handles context-driven instantiation, while the top-level `STestEngine` drives full lifecycle execution.