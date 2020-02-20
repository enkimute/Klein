#pragma once

#include "detail/matrix.hpp"
#include "direction.hpp"
#include "entity.hpp"
#include "line.hpp"
#include "mat4x4.hpp"
#include "plane.hpp"
#include "point.hpp"
#include <cmath>

namespace kln
{
/// The rotor is an entity that represents a rigid rotation about an axis.
/// To apply the rotor to a supported entity, the call operator is available.
///
/// !!! example
///
///     ```c++
///         // Initialize a point at (1, 3, 2)
///         kln::point p{1.f, 3.f, 2.f};
///
///         // Create a normalized rotor representing a pi/2 radian
///         // rotation about the xz-axis.
///         kln::rotor r{M_PI * 0.5f, 1.f, 0.f, 1.f};
///
///         // Rotate our point using the created rotor
///         kln::point rotated = r(p);
///     ```
///     We can rotate lines and planes as well using the rotor's call operator.
///
/// Rotors can be multiplied to one another with the `*` operator to create
/// a new rotor equivalent to the application of each factor.
///
/// !!! example
///
///     ```c++
///         // Create a normalized rotor representing a $\frac{\pi}{2}$ radian
///         // rotation about the xz-axis.
///         kln::rotor r1{M_PI * 0.5f, 1.f, 0.f, 1.f};
///
///         // Create a second rotor representing a $\frac{\pi}{3}$ radian
///         // rotation about the yz-axis.
///         kln::rotor r2{M_PI / 3.f, 0.f, 1.f, 1.f};
///
///         // Use the geometric product to create a rotor equivalent to first
///         // applying r1, then applying r2. Note that the order of the
///         // operands here is significant.
///         kln::rotor r3 = r2 * r1;
///     ```
///
/// The same `*` operator can be used to compose the rotor's action with other
/// translators and motors.
struct rotor final : public entity<0b10>
{
    /// Default constructor leaves memory uninitialized.
    rotor() = default;

    /// Convenience constructor. Computes transcendentals and normalizes
    /// rotation axis.
    rotor(float ang_rad, float x, float y, float z)
    {
        float norm     = std::sqrt(x * x + y * y + z * z);
        float inv_norm = -1.f / norm;

        float half = 0.5f * ang_rad;
        // Rely on compiler to coalesce these two assignments into a single
        // sincos call at instruction selection time
        float buf[4];
        buf[0]        = std::cos(half);
        float sin_ang = std::sin(half);
        float scale   = sin_ang * inv_norm;
        buf[1]        = z * scale;
        buf[2]        = y * scale;
        buf[3]        = x * scale;
        parts[0].reg  = _mm_loadu_ps(buf);
    }

    rotor(entity<0b10> const& other)
        : entity{other}
    {}

    /// Fast load operation for packed data that is already normalized. The
    /// argument `data` should point to a set of 4 float values with layout `(a,
    /// b, c, d)` corresponding to the multivector
    /// $a + b\mathbf{e}_{12} + c\mathbf{e}_{31} + d\mathbf{e}_{23}$.
    ///
    /// !!! danger
    ///
    ///     The rotor data loaded this way *must* be normalized. That is, the
    ///     rotor $r$ must satisfy $r\widetilde{r} = 1$.
    void load_normalized(float* data) noexcept
    {
        parts[0].reg = _mm_loadu_ps(data);
    }

    /// Normalize a rotor such that $\mathbf{r}\widetilde{\mathbf{r}} = 1$.
    void normalize() noexcept
    {
        // A rotor is normalized if r * ~r is unity.
        __m128 inv_norm = _mm_rcp_ps(_mm_sqrt_ps(_mm_dp_ps(p1(), p1(), 0xff)));
        p1()            = _mm_mul_ps(p1(), inv_norm);
    }

    /// Converts the rotor to a 4x4 column-major matrix.
    mat4x4 as_matrix() const noexcept
    {
        mat4x4 out;
        mat4x4_12<false>(parts[0].reg, nullptr, out.cols);
        return out;
    }

    /// Conjugates a plane $p$ with this rotor and returns the result
    /// $rp\widetilde{r}$.
    plane KLN_VEC_CALL operator()(plane const& p) const noexcept
    {
        plane out;
        sw012<false, false>(&p.p0(), parts[0].reg, nullptr, &out.p0());
        return out;
    }

    /// Conjugates an array of planes with this rotor in the input array and
    /// stores the result in the output array. Aliasing is only permitted when
    /// `in == out` (in place motor application).
    ///
    /// !!! tip
    ///
    ///     When applying a rotor to a list of tightly packed planes, this
    ///     routine will be *significantly faster* than applying the rotor to
    ///     each plane individually.
    void KLN_VEC_CALL operator()(plane* in, plane* out, size_t count) const
        noexcept
    {
        sw012<true, false>(&in->p0(), parts[0].reg, nullptr, &out->p0(), count);
    }

    /// Conjugates a line $\ell$ with this rotor and returns the result
    /// $r\ell \widetilde{r}$.
    line KLN_VEC_CALL operator()(line const& l) const noexcept
    {
        line out;
        swMM<false, false>(&l.p1(), p1(), nullptr, &out.p1());
        return out;
    }

    /// Conjugates an array of lines with this rotor in the input array and
    /// stores the result in the output array. Aliasing is only permitted when
    /// `in == out` (in place rotor application).
    ///
    /// !!! tip
    ///
    ///     When applying a rotor to a list of tightly packed lines, this
    ///     routine will be *significantly faster* than applying the rotor to
    ///     each line individually.
    void KLN_VEC_CALL operator()(line* in, line* out, size_t count) const noexcept
    {
        swMM<true, false>(&in->p1(), parts[0].reg, nullptr, &out->p1(), count);
    }

    /// Conjugates a point $p$ with this rotor and returns the result
    /// $rp\widetilde{r}$.
    point KLN_VEC_CALL operator()(point const& p) const noexcept
    {
        point out;
        sw312<false, false>(&p.p3(), parts[0].reg, nullptr, &out.p3());
        return out;
    }

    /// Conjugates an array of points with this rotor in the input array and
    /// stores the result in the output array. Aliasing is only permitted when
    /// `in == out` (in place rotor application).
    ///
    /// !!! tip
    ///
    ///     When applying a rotor to a list of tightly packed points, this
    ///     routine will be *significantly faster* than applying the rotor to
    ///     each point individually.
    void KLN_VEC_CALL operator()(point* in, point* out, size_t count) const
        noexcept
    {
        sw312<true, false>(&in->p3(), parts[0].reg, nullptr, &out->p3(), count);
    }

    /// Conjugates a direction $d$ with this rotor and returns the result
    /// $rd\widetilde{r}$.
    direction KLN_VEC_CALL operator()(direction const& d) const noexcept
    {
        direction out;
        sw312<false, false>(&d.p3(), parts[0].reg, nullptr, &out.p3());
        return out;
    }

    /// Conjugates an array of directions with this rotor in the input array and
    /// stores the result in the output array. Aliasing is only permitted when
    /// `in == out` (in place rotor application).
    ///
    /// !!! tip
    ///
    ///     When applying a rotor to a list of tightly packed directions, this
    ///     routine will be *significantly faster* than applying the rotor to
    ///     each direction individually.
    void KLN_VEC_CALL operator()(direction* in, direction* out, size_t count) const
        noexcept
    {
        sw312<true, false>(&in->p3(), parts[0].reg, nullptr, &out->p3(), count);
    }
};
} // namespace kln