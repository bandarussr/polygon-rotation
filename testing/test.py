import gc
import math
import os
import random
import subprocess
import sys
import time

import pandas as pd
from tqdm import tqdm

PROGRAM = "../bin/PolygonRotation"
ITERATIONS = 10
MAX = 10_000


def main():
    # Set random seed.
    seed = -1
    if len(sys.argv) >= 3:
        seed = int(sys.argv[2])
        random.seed(seed)
    else:
        seed = time.time()
        random.seed(seed)

    # Check for output path.
    if len(sys.argv) < 2:
        print(f"Usage: {sys.argv[0]} <output.csv> [seed]")
        return
    out = f"{sys.argv[1]}_{seed}.csv"

    # Check if program exists.
    if not os.path.exists(PROGRAM):
        print(f"Error: Program '{PROGRAM}' not found.")
        return

    times = []
    for n in tqdm(range(3, MAX + 1)):
        inputs = [create_input(n) for _ in range(ITERATIONS)]
        all = "".join(inputs)

        elapsed = test_input(all)
        times.append(elapsed / ITERATIONS)

    pd.DataFrame({"n": range(3, MAX + 1), "time": times}).to_csv(out)


def create_input(n: int) -> str:
    angles = sorted(random.uniform(0, 2 * math.pi) for _ in range(n))
    radius = 100

    x = [int(random.randint(1, radius) * math.cos(a)) for a in angles]
    y = [int(random.randint(1, radius) * -math.sin(a)) for a in angles]

    # Ensure top and bottom points exist on the y-axis (problem constraint).
    top = y.index(max(y))
    bot = y.index(min(y))
    x[top] = 0
    x[bot] = 0

    # Create input string.
    input = f"{n}\n"
    for i in range(n):
        input += f"{x[i]}\n"
    for i in range(n):
        input += f"{y[i]}\n"

    return input


def test_input(input: str) -> float:
    encoded = input.encode()

    p = subprocess.Popen(
        PROGRAM,
        stdin=subprocess.PIPE,
        stdout=subprocess.DEVNULL,
        stderr=subprocess.DEVNULL,
    )

    # Time
    gc.disable()
    try:
        start = time.perf_counter()
        p.communicate(encoded)
        elapsed = time.perf_counter() - start
    finally:
        gc.enable()

    return elapsed


if __name__ == "__main__":
    main()
