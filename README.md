# Simulation Mentoring: LaTeX and Practice Codes (KSA 2026-1)

이 저장소는 **KSA 2026-1 Simulation Mentoring** 강의를 위한 시뮬레이션 C++ 예제 코드와 LaTeX 강의 자료를 포함하고 있습니다.

## 프로젝트 목적 (Objective)

본 프로젝트의 목표는 물리 시뮬레이션의 기초부터 성능 최적화까지의 과정을 C++ 코드로 구현하고, 해당 코드의 수학적/컴퓨터 과학적 원리를 LaTeX 문서로 정리하여 교육 자료를 구축하는 것입니다.

## 주요 강의 주제 (Lecture Topics)

1.  **p1: 수치 적분의 수렴성 (Numerical Integration Convergence)**
    *   오일러 방법(Euler Method)을 이용한 속도 및 위치 업데이트의 수렴성 증명.
    *   저항력($F = -kv$) 모델에서의 해석적 해와의 비교.
2.  **p2: 제어 흐름 성능 (Control Flow Performance)**
    *   `if-else` 체인과 `switch` 문(Jump Table)의 성능 비교 및 CPU 분기 예측 분석.
3.  **p3: 물리 시뮬레이션과 이산화 (Physics Simulation Discretization)**
    *   원운동 시뮬레이션에서의 Semi-implicit Euler 방법의 안정성.
    *   격자 기반 열 전도 방정식(Heat Equation)의 수치 해석.
4.  **p4: 시뮬레이션 성능 실험 (Simulation Performance Experiments)**
    *   제약 조건 처리(삼항 연산자 vs `if-else`).
    *   메모리 구조 최적화 (SOA vs AOS).
    *   메모리 할당 전략 (Stack vs Heap).
5.  **p5: 테일러 급수 수치 근사 (Taylor Series Approximation)**
    *   지수 함수($e^x$)의 테일러 전개를 통한 수치 근사 및 오차 분석.

## 프로젝트 구조 (Structure)

*   `cpp_files/`: 각 주제별 시뮬레이션 C++ 소스 코드.
*   `latex/`: LaTeX 기반 강의 자료 원본 및 레이아웃 설정 파일.
*   `gemini-guideline.md`: 프로젝트 개발 가이드라인.

## 빌드 및 실행 (How to Run)

### C++ 예제 실행
```bash
g++ -O3 cpp_files/p2_jump_table.cpp -o p2_test
./p2_test
```

### LaTeX 문서 컴파일
`latex/main.tex` 파일을 LaTeX 컴파일러(pdflatex, xelatex 등)를 사용하여 컴파일하십시오.

---
**Mentors:** 홍준서, 백재원
