#!/usr/bin/env python3
"""
A practical number is a positive integer N such that all smaller positive integers can be represented as sums of distinct divisors of N. For example, 12 is a practical number because all the numbers from 1 to 11 can be expressed as sums of the divisors of 12, which are 1, 2, 3, 4, and 6. (Wikipedia.) However, 10 is not a practical number, because 4 and 9 cannot be expressed as a sum of 1, 2, and 5. For more detailed explanation and examples, see this recent Numberphile video.

Challenge
Write a function that returns whether a given positive integer is a practical number.

practical(1) => true
practical(2) => true
practical(3) => false
practical(10) => false
practical(12) => true

1, 2, 4, 6, 8, 12, 16, 18, 24, 28, ... 100

14 divisors 1, 7  <- need to be able to get to next divisor
for each prime p, if you can make p-1 it's practical

You should be able to handle numbers up to 10,000 efficiently. The sum of all practical numbers up to 10,000 inclusive is 6,804,107. Test your code by verifying this value.

Optional bonus challenge
Consider the numbers X in the range 1 to 10,000 inclusive. The sum of all X such that 1019 + X is a practical number is 1,451,958. Find the sum of all X such that 1020 + X is a practical number. I found the section Characterization of practical numbers in the Wikipedia article useful here.
"""
import math

def prime_factors(number: int) -> list[int]:
    factors = []
    n = number
    while n % 2 == 0:
        #factors[2] = factors.get(2, 0) + 1
        factors.append(2)
        n //= 2

    for i in range(3, int(math.sqrt(n)+1), 2):
        while n % i == 0:
            # factors[i] = factors.get(i, 0) + 1
            factors.append(i)
            n //= i

    if n > 2:
        # factors[n] = factors.get(n, 0) + 1
        factors.append(n)

    return factors

def all_divisors(number: int) -> list[int]:
    # https://mail.python.org/pipermail/python-list/2005-March.txt
    # search for "math - need divisors algorithm"
    return [x for x in range(1, number-2) if not divmod(number, x)[1]]

def all_divisors2(prime_factors: list[int]):
    # https://mail.python.org/pipermail/python-list/2005-March.txt
    # search for "math - need divisors algorithm"

    primes = sorted(set(prime_factors))
    num_primes = len(primes)

    # Split on the number of copies of primes[i].
    def gen_inner(i):
        if i >= num_primes:
            yield 1
            return
        
        factor = primes[i]
        factor_count = prime_factors.count(factor)

        # powers <- [thiselt**i for i in range(thismax+1)],
        # but using only thismax multiplications.
        powers = [1]
        for j in range(factor_count):
            powers.append(powers[-1] * factor)

        for d in gen_inner(i+1):
            for prime_power in powers:
                yield prime_power * d

    return list(gen_inner(0))

def all_divisors3(prime_factors: list[int]):
    # https://mail.python.org/pipermail/python-list/2005-March.txt
    # search for "math - need divisors algorithm"
    primes = sorted(set(prime_factors))
    num_primes = len(primes)

    for i in primes:
        count = primes.count(i)
        

    # Split on the number of copies of primes[i].
    def gen_inner(i):
        if i >= num_primes:
            yield 1
            return
        
        factor = primes[i]
        factor_count = prime_factors.count(factor)

        # powers <- [thiselt**i for i in range(thismax+1)],
        # but using only thismax multiplications.
        powers = [1]
        for j in range(factor_count):
            powers.append(powers[-1] * factor)

        for d in gen_inner(i+1):
            for prime_power in powers:
                yield prime_power * d

    return list(gen_inner(0))


def practical(number: int) -> bool:
    if number == 1 or number == 2:
        return True

    print(f'Number: {number}')
    primes = prime_factors(number)
    print(f'\tprimes:{primes}')

    #divisors = all_divisors(number)
    # 2.48s user 0.08s system 85% cpu 2.985 total
    # 2.39s user 0.04s system 89% cpu 2.718 total

    divisors = all_divisors2(primes)
    # 0.11s user 0.05s system 31% cpu 0.524 total
    # 0.08s user 0.02s system 32% cpu 0.320 total
    print(f'\tdivisors:{divisors}')

    if 2 not in divisors:
        return False

    for prime in set(primes):
        if prime > 2 and prime != number: 
            smaller = list(filter(lambda x: x < prime, divisors))
            d_sum = sum(smaller) + 1
            print(f'\tfactor: {prime}')
            print(f'\t\tsmaller {smaller} = {d_sum}')

            if not prime <= d_sum:
                return False

    return True

def test_report(name, expected, result):
    if result == expected:
        print(f"Test {name}: PASSED")
    else:
        print(f"Test {name}: FAILED expected \"{expected}\" got \"{result}\"")
        
def test_practical():
    #test_report("1", True, practical(1))
    #est_report("2", True, practical(2))
    #test_report("3", False, practical(3))
    #test_report("10", False, practical(10))
    test_report("12", True, practical(12))
    test_report("429606", True, practical(429606))
    for i in range(1, 10000):
        practical(i)

test_practical()