## struct `kln::plane` {#structkln_1_1plane}

```
struct kln::plane
  : public kln::entity< 0b1 >
```  

In projective geometry, planes are the fundamental element through which all other entities are constructed. Lines are the meet of two planes, and points are the meet of three planes (equivalently, a line and a plane).

The plane multivector in PGA looks like $d\mathbf{e}_0 + a\mathbf{e}_1 + b\mathbf{e}_2 + c\mathbf{e}_3$. Points that reside on the plane satisfy the familiar equation $d + ax + by + cz = 0$.

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  ` [`plane`](#structkln_1_1plane_1a0ab245bca0c1ad3aca86b9ceeab3fe42)`() = default`  | The default constructor leaves memory uninitialized.
`public  ` [`plane`](#structkln_1_1plane_1a51933d8d8853797034621ce41ad34a8e)`(float a,float b,float c,float d) noexcept`  | The constructor performs the rearrangement so the plane can be specified in the familiar form: ax + by + cz + d
`public  explicit ` [`plane`](#structkln_1_1plane_1a29dbb1804fa3ec402f901ca8049d60bc)`(float * data) noexcept`  | Data should point to four floats with memory layout `(d, a, b, c)`  where `d`  occupies the lowest address in memory.
`public  explicit ` [`plane`](#structkln_1_1plane_1a4fe52a0426bc881947909d0d9b1745d0)`(` [`entity`](../../api/kln_entity#structkln_1_1entity)`< 0b1001 > const & other) noexcept`  | Point/plane to plane cast.
`public void ` [`load`](#structkln_1_1plane_1a5a00871dbe19d7658b7e8cda71b326f2)`(float * data) noexcept`  | Unaligned load of data. The `data`  argument should point to 4 floats corresponding to the `(d, a, b, c)`  components of the plane multivector where `d`  occupies the lowest address in memory.
`public void ` [`normalize`](#structkln_1_1plane_1ae5e1e0af05e84799d27d7b8782fe5f22)`() noexcept`  | Normalize this plane $p$ such that $p \cdot p = 1$.
`public float ` [`norm`](#structkln_1_1plane_1a2f86598e6a327c72201e68615bd10384)`() const noexcept`  | Compute the plane norm, which is often used to compute distances between points and lines.
`public ` [`plane`](#structkln_1_1plane)` KLN_VEC_CALL ` [`operator()`](#structkln_1_1plane_1a1c7a11e35d91c2aee88a4152b1799ca9)`(` [`plane`](#structkln_1_1plane)` const & p) const noexcept`  | Reflect another plane $p_2$ through this plane $p_1$. The operation performed via this call operator is an optimized routine equivalent to the expression $p_1 p_2 p_1$.
`public ` [`line`](../../api/kln_line#structkln_1_1line)` KLN_VEC_CALL ` [`operator()`](#structkln_1_1plane_1a782e4e0b1b93ab5bffb2c972f6d7acfa)`(` [`line`](../../api/kln_line#structkln_1_1line)` const & l) const noexcept`  | Reflect line $\ell$ through this plane $p$. The operation performed via this call operator is an optimized routine equivalent to the expression $p \ell p$.
`public ` [`point`](../../api/kln_point#structkln_1_1point)` KLN_VEC_CALL ` [`operator()`](#structkln_1_1plane_1a20b6577f6d1717e1ec086314d3ebd497)`(` [`point`](../../api/kln_point#structkln_1_1point)` const & p) const noexcept`  | Reflect the point $P$ through this plane $p$. The operation performed via this call operator is an optimized routine equivalent to the expression $p P p$.
`public float ` [`x`](#structkln_1_1plane_1ad2a57bafbd388d4ca9ca98d0074fee0a)`() const noexcept`  | 
`public float & ` [`x`](#structkln_1_1plane_1a42cc26e2b8d3f4d620a9719716583e93)`() noexcept`  | 
`public float ` [`y`](#structkln_1_1plane_1adce64826f47e1a017fba8fefab69c174)`() const noexcept`  | 
`public float & ` [`y`](#structkln_1_1plane_1a0b2a9a4f94160e11ff06b24f359c2b3f)`() noexcept`  | 
`public float ` [`z`](#structkln_1_1plane_1a2a01bee79dfb0c11414dc5a936397987)`() const noexcept`  | 
`public float & ` [`z`](#structkln_1_1plane_1ab96ef6c2adc0a90f4d6c2dcb835c6928)`() noexcept`  | 
`public float ` [`d`](#structkln_1_1plane_1ab3aa088fdf83091809bb7e08ace460bb)`() const noexcept`  | 
`public float & ` [`d`](#structkln_1_1plane_1a1014e9dc46a9ff5ff4ae5496ca78eba2)`() noexcept`  | 

### Members

####   [plane](#structkln_1_1plane_1a0ab245bca0c1ad3aca86b9ceeab3fe42)() = default  {#structkln_1_1plane_1a0ab245bca0c1ad3aca86b9ceeab3fe42}

The default constructor leaves memory uninitialized.

####   [plane](#structkln_1_1plane_1a51933d8d8853797034621ce41ad34a8e)(float a,float b,float c,float d) noexcept  {#structkln_1_1plane_1a51933d8d8853797034621ce41ad34a8e}

The constructor performs the rearrangement so the plane can be specified in the familiar form: ax + by + cz + d

####  explicit  [plane](#structkln_1_1plane_1a29dbb1804fa3ec402f901ca8049d60bc)(float * data) noexcept  {#structkln_1_1plane_1a29dbb1804fa3ec402f901ca8049d60bc}

Data should point to four floats with memory layout `(d, a, b, c)`  where `d`  occupies the lowest address in memory.

####  explicit  [plane](#structkln_1_1plane_1a4fe52a0426bc881947909d0d9b1745d0)( [entity](../../api/kln_entity#structkln_1_1entity)< 0b1001 > const & other) noexcept  {#structkln_1_1plane_1a4fe52a0426bc881947909d0d9b1745d0}

Point/plane to plane cast.

!!! danger 
    When constructing a plane with points using the regressive product,
    data leaks into the 3rd partition so this explicit constructor is
    made available. For example, if you had three `point` entities `p1`,
    `p2`, and `p3`, the plane containing all three points could be
    constructed via `plane p{p1 & p2 & p3}`.
    
    If the third partition contains data, this cast will *truncate* that
    data so this constructor should only be used when the caller *knows*
    that the entity passed as the argument is a plane.

#### void  [load](#structkln_1_1plane_1a5a00871dbe19d7658b7e8cda71b326f2)(float * data) noexcept  {#structkln_1_1plane_1a5a00871dbe19d7658b7e8cda71b326f2}

Unaligned load of data. The `data`  argument should point to 4 floats corresponding to the `(d, a, b, c)`  components of the plane multivector where `d`  occupies the lowest address in memory.

!!! tip 
    This is a faster mechanism for setting data compared to setting
    components one at a time.

#### void  [normalize](#structkln_1_1plane_1ae5e1e0af05e84799d27d7b8782fe5f22)() noexcept  {#structkln_1_1plane_1ae5e1e0af05e84799d27d7b8782fe5f22}

Normalize this plane $p$ such that $p \cdot p = 1$.

In order to compute the cosine of the angle between planes via the inner product operator `|` , the planes must be normalized. Producing a normalized rotor between two planes with the geometric product `*`  also requires that the planes are normalized.

!!! tip 
    Normalization here is done using the `rsqrtps`
    instruction with a maximum relative error of $1.5\times 2^{-12}$.

#### float  [norm](#structkln_1_1plane_1a2f86598e6a327c72201e68615bd10384)() const noexcept  {#structkln_1_1plane_1a2f86598e6a327c72201e68615bd10384}

Compute the plane norm, which is often used to compute distances between points and lines.

Given a normalized point $P$ and normalized line $\ell$, the plane $P\vee\ell$ containing both $\ell$ and $P$ will have a norm equivalent to the distance between $P$ and $\ell$.

####  [plane](#structkln_1_1plane) KLN_VEC_CALL  [operator()](#structkln_1_1plane_1a1c7a11e35d91c2aee88a4152b1799ca9)( [plane](#structkln_1_1plane) const & p) const noexcept  {#structkln_1_1plane_1a1c7a11e35d91c2aee88a4152b1799ca9}

Reflect another plane $p_2$ through this plane $p_1$. The operation performed via this call operator is an optimized routine equivalent to the expression $p_1 p_2 p_1$.

####  [line](../../api/kln_line#structkln_1_1line) KLN_VEC_CALL  [operator()](#structkln_1_1plane_1a782e4e0b1b93ab5bffb2c972f6d7acfa)( [line](../../api/kln_line#structkln_1_1line) const & l) const noexcept  {#structkln_1_1plane_1a782e4e0b1b93ab5bffb2c972f6d7acfa}

Reflect line $\ell$ through this plane $p$. The operation performed via this call operator is an optimized routine equivalent to the expression $p \ell p$.

####  [point](../../api/kln_point#structkln_1_1point) KLN_VEC_CALL  [operator()](#structkln_1_1plane_1a20b6577f6d1717e1ec086314d3ebd497)( [point](../../api/kln_point#structkln_1_1point) const & p) const noexcept  {#structkln_1_1plane_1a20b6577f6d1717e1ec086314d3ebd497}

Reflect the point $P$ through this plane $p$. The operation performed via this call operator is an optimized routine equivalent to the expression $p P p$.

#### float  [x](#structkln_1_1plane_1ad2a57bafbd388d4ca9ca98d0074fee0a)() const noexcept  {#structkln_1_1plane_1ad2a57bafbd388d4ca9ca98d0074fee0a}

#### float &  [x](#structkln_1_1plane_1a42cc26e2b8d3f4d620a9719716583e93)() noexcept  {#structkln_1_1plane_1a42cc26e2b8d3f4d620a9719716583e93}

#### float  [y](#structkln_1_1plane_1adce64826f47e1a017fba8fefab69c174)() const noexcept  {#structkln_1_1plane_1adce64826f47e1a017fba8fefab69c174}

#### float &  [y](#structkln_1_1plane_1a0b2a9a4f94160e11ff06b24f359c2b3f)() noexcept  {#structkln_1_1plane_1a0b2a9a4f94160e11ff06b24f359c2b3f}

#### float  [z](#structkln_1_1plane_1a2a01bee79dfb0c11414dc5a936397987)() const noexcept  {#structkln_1_1plane_1a2a01bee79dfb0c11414dc5a936397987}

#### float &  [z](#structkln_1_1plane_1ab96ef6c2adc0a90f4d6c2dcb835c6928)() noexcept  {#structkln_1_1plane_1ab96ef6c2adc0a90f4d6c2dcb835c6928}

#### float  [d](#structkln_1_1plane_1ab3aa088fdf83091809bb7e08ace460bb)() const noexcept  {#structkln_1_1plane_1ab3aa088fdf83091809bb7e08ace460bb}

#### float &  [d](#structkln_1_1plane_1a1014e9dc46a9ff5ff4ae5496ca78eba2)() noexcept  {#structkln_1_1plane_1a1014e9dc46a9ff5ff4ae5496ca78eba2}

