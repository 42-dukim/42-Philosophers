# Philosophers

멀티스레딩 환경에서의 교착 상태(Deadlock)와 경쟁 상태(Race Condition)를 다루는 '철학자들의 저녁 식사' 시뮬레이션입니다. 데이터 레이스 없는 동작, 정확한 타임스탬프, 로그 일관성에 중점을 두었습니다.

<img width="700" height="700" alt="image" src="https://github.com/user-attachments/assets/9153e7c5-a921-48e1-aee4-07c7cb26dde9" />

-----

## ✨ 핵심 과제

### 문제

철학자 수(n)만큼 포크(뮤텍스)가 있고, 각 철학자는 두 포크를 잡아야 식사할 수 있습니다. 각 철학자는 eat-sleep-think를 반복하며, 일정 시간 내 식사를 시작하지 못하면 사망합니다.

### 목표

데이터 레이스 없이 동작하고, 사망 로그는 실제 사망 시점 ±10ms 내로 출력되어야 합니다. 모든 로그는 시뮬레이션 시작 시각 기준 ms 단위 타임스탬프를 가집니다.

### 핵심 문제와 해결 전략

- 경쟁 상태: 포크마다 뮤텍스를 두어 상호 배제를 보장합니다.
- 교착 상태: 
  - N이 짝수일 때는 짝수/홀수 철학자가 각각 왼쪽→오른쪽, 오른쪽→왼쪽 순으로 포크를 집어 순환 대기를 깨뜨립니다.
  - N이 홀수일 때는 초기 지연(홀수 ID 10ms)으로 경합을 낮춥니다.

### 내 솔루션의 차별점

1.  공정한 시작
    - 철학자 스레드를 생성 전에 `main`에서 `opt_mutex`를 lock합니다.
    - 먼저 생성된 스레드는 `opt_mutex`를 선점하지 못 하므로 `routine`을 시작하지 못 합니다.
    - 모든 철학자 스레드를 생성 후, `main`에서 `opt_mutex` unlock합니다.
    -> 누가 먼저 생성됐느냐에 따른 유리함이 사라지고, 로그의 시간 비교가 공정하고 일관됩니다.
2. 깔끔한 로그(출력 직렬화 + 사망 후 억제)
    - `printf` 함수는 멀티 스레드환경에서 출력이 서로 섞이지 않을 거라고 보장 X 
    - 한 번에 한 스레드만 출력하도록 `print_mutex`에 잠금을 걸어 줄 단위로 출력 순서를 보장합니다.
    - 누군가 사망하면 ‘died’ 메시지를 딱 한 번만 남기고 `printflag=false`로 전환하여 이후 모든 로그를 hard-block합니다.
3. 시간 정확도(ms 기준 + 가벼운 폴링)
    - 모든 시간 표시는 “시작 시각”을 기준으로 밀리초 단위로 계산합니다.
    - 기다릴 때는 한 번에 오래 sleep 하지 않고 짧게 여러 번 확인하며(가벼운 폴링, `ms_sleep_withchecking()`) 지터를 줄이고 종료 플래그를 확인합니다.
    - 모니터는 `1ms`마다 생존을 확인해 사망 로그가 실제 시점에서 크게 벗어나지 않도록 합니다.

## 🛠️ 시작하기 (Getting Started)

### 빌드

```bash
cd philo/
make -C
# 개발(스레드 sanitizer)
make -C dev
```

### 실행

```bash
./philo [철학자 수] [죽음까지의 시간] [식사 시간] [수면 시간] [선택: 각 철학자의 최소 식사 횟수]
```

> 예시 1: 5명의 철학자, 800ms 안에 식사 못하면 사망, 식사 200ms, 수면 200ms

`./philo 5 800 200 200`

<img width="500" alt="image" src="https://github.com/user-attachments/assets/2520fe7e-3c47-44bd-a93c-6db113d14bdb" />

> 예시 2: 6명의 철학자, 600ms 안에 식사 못하면 사망, 식사 200ms, 수면 200ms, 최소 식사 횟수 2

`./philo 6 600 200 200 2`

<img width="500" alt="image" src="https://github.com/user-attachments/assets/93e9a4e3-239f-4654-974f-694e3aa68518" />

> 예시 3(edge case): 1명의 철학자, 410ms 안에 식사 못하면 사망, 식사 200ms, 수면 200ms

`./philo 1 410 200 200`

<img width="500" alt="image" src="https://github.com/user-attachments/assets/1c35aaa0-cac2-4142-bc3d-983cd4832b4f" />

