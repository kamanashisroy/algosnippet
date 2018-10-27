


System of Congruence
======================

#### Chinese remainder theorem

TODO make a proof by animation.


Modular Multiplicative inverse
===============================

Quoted from wikipedia

- Existence: there exists an integer denoted a<sup>–1</sup> such that aa<sup>–1</sup> ≡ 1 (mod n) if and only if a is coprime with n. This integer a<sup>–1</sup> is called a modular multiplicative inverse of a modulo n.
- If a ≡ b (mod n) and a<sup>–1</sup> exists, then a<sup>–1</sup> ≡ b<sup>–1</sup> (mod n) (compatibility with multiplicative inverse, and, if a = b, uniqueness modulo n)
- If a x ≡ b (mod n) and a is coprime to n, the solution to this linear congruence is given by x ≡ a<sup>–1</sup>b (mod n)

Extended Euclid algorithm
==========================

Extended Euclid algorithm is used to solve the linear congruence.

Fermat's Little theorem
=======================

It is a theorem of modular exponentiation.

k<sup>p-1</sup> ≡ 1 (mod p)

This can be used to retrieve the multiplicative inverse.


k<sup>p-2</sup>k ≡ 1 (mod p)

Note that k<sup>p-2</sup> is multiplicative inverse of `k`.

Relative Primality theorem
===========================

Euler's theorem (Euler totient function)
=========================================

For any number n, if p1, p2 .. pj are the unique prime factors then, **number of relatively prime numbers of `n` smaller than `n`** can be calculated from Euler's totient function.

```
Euler's totient function (n) = n(1-1/p1)(1-1/p2)(1-1/p3)...(1-1/pj)
```

For example, when n = 300, the prime factors are 2,3 and 5 and,

```
Euler's totient function (300) = 300*(1-1/2)*(1-1/3)*(1-1/5)
                               = 300*(1/2)*(2/3)(4/5) = 80
```

And from Fermat's Little theorem,

k<sup>Euler's totient function(n)</sup> ≡ 1 (mod n)


We can also get the multiplicative inverse from Euler's totient function.

k<sup>Euler's totient function(n)-1</sup> ≡ 1 (mod n)

RSA Cryptosystem
===================

TODO

DH-Key exchange
================

Links
=======

- [System of Congruence](https://www.youtube.com/watch?v=LInNgWMtFEs)
- [Solving linear congruence](https://www.youtube.com/watch?v=4-HSjLXrfPs&t=719s)
- [MIT-OCW lecture](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-042j-mathematics-for-computer-science-fall-2010/readings/MIT6_042JF10_chap04.pdf)


