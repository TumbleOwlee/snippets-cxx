#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace snippets {

/**
 * Bitmask class
 *
 * \details This class provides a way to manage a bitmask with a specific number
 * of bits
 *
 * \tparam BIT_CNT Number of bits
 * \tparam CONTAINER Container type (uint8_t, uint16_t, uint32_t, uint64_t)
 */
template <size_t BIT_CNT, typename CONTAINER = uint8_t>
class bitmask {
    // Check if the number of bits is within the container size
    static_assert(BIT_CNT <= (sizeof(CONTAINER) * 8));
    // Check if the container is a valid type
    static_assert(std::is_same<CONTAINER, uint8_t>() || std::is_same<CONTAINER, uint16_t>() ||
                  std::is_same<CONTAINER, uint32_t>() || std::is_same<CONTAINER, uint64_t>());

private:
    /**
     * Generate masks for each bit
     */
    static auto gen_masks() -> std::array<CONTAINER, BIT_CNT> {
        std::array<CONTAINER, BIT_CNT> masks = {0};
        for (size_t i = 0; i < BIT_CNT; ++i) {
            masks[i] = (1 << i);
        }
        return masks;
    }

    /**
     * Masks for each bit
     *
     * \details This array contains the masks for each bit in the bitmask. It is
     * generated during compile time to avoid recalculating the masks every time
     * they are needed.
     */
    const std::array<CONTAINER, BIT_CNT> masks = gen_masks();

public:
    /**
     * Constructor (initializes all bits to 0)
     */
    bitmask() : value(0) {}

    /**
     * Destructor
     */
    ~bitmask() = default;

    /**
     * Set bit to on
     *
     * \param BIT Bit to set
     */
    template <size_t BIT>
    auto set() -> void {
        static_assert(BIT < BIT_CNT);
        _set(BIT);
    }

    /**
     * Set multiple bits to on
     *
     * \param BIT1 First bit to set
     * \param BIT2 Second bit to set
     * \param BITS Remaining bits to set
     */
    template <size_t BIT1, size_t BIT2, size_t... BITS>
    auto set() -> void {
        set<BIT1>();
        set<BIT2, BITS...>();
    }

    /**
     * Set bit to off
     *
     * \param BIT Bit to unset
     */
    template <size_t BIT>
    auto unset() -> void {
        static_assert(BIT < BIT_CNT);
        _unset(BIT);
    }

    /**
     * Set multiple bits to off
     *
     * \param BIT1 First bit to unset
     * \param BIT2 Second bit to unset
     * \param BITS Remaining bits to unset
     */
    template <size_t BIT1, size_t BIT2, size_t... BITS>
    auto unset() -> void {
        unset<BIT1>();
        unset<BIT2, BITS...>();
    }

    /**
     * Check if bit is set
     *
     * \param BIT Bit to check
     * \return True if bit is set, false otherwise
     */
    template <size_t BIT>
    auto is_set() const -> bool {
        static_assert(BIT < BIT_CNT);
        return _is_set(BIT);
    }

    /**
     * Check if multiple bits are set
     *
     * \param BIT1 First bit to check
     * \param BIT2 Second bit to check
     * \param BITS Remaining bits to check
     * \return True if all bits are set, false otherwise
     */
    template <size_t BIT1, size_t BIT2, size_t... BITS>
    auto is_set() const -> bool {
        return is_set<BIT1>() && is_set<BIT2, BITS...>();
    }

    /**
     * Check if any of the bits are set
     *
     * \param BIT Bit to check
     * \return True if any of the bits are set, false otherwise
     */
    template <size_t BIT>
    auto is_any() const -> bool {
        static_assert(BIT < BIT_CNT);
        return _is_set(BIT);
    }

    /**
     * Check if any of the bits are set
     *
     * \param BIT1 First bit to check
     * \param BIT2 Second bit to check
     * \param BITS Remaining bits to check
     * \return True if any of the bits are set, false otherwise
     */
    template <size_t BIT1, size_t BIT2, size_t... BITS>
    auto is_any() const -> bool {
        return is_any<BIT1>() || is_any<BIT2, BITS...>();
    }

    /**
     * Check if none of the bits are set
     *
     * \param BIT Bit to check
     * \return True if none of the bits are set, false otherwise
     */
    template <size_t BIT>
    auto is_none() const -> bool {
        return !_is_set(BIT);
    }

    /**
     * Check if none of the bits are set
     *
     * \param BIT1 First bit to check
     * \param BIT2 Second bit to check
     * \param BITS Remaining bits to check
     * \return True if none of the bits are set, false otherwise
     */
    template <size_t BIT1, size_t BIT2, size_t... BITS>
    auto is_none() const -> bool {
        return is_none<BIT1>() && is_none<BIT2, BITS...>();
    }

protected:
    /**
     * Bitmask value
     */
    CONTAINER value : BIT_CNT;

private:
    /**
     * Set bit
     *
     * \param bit Bit to set
     */
    auto _set(size_t bit) -> void { value |= masks[bit]; }

    /**
     * Unset bit
     *
     * \param bit Bit to unset
     */
    auto _unset(size_t bit) -> void { value &= ~masks[bit]; }

    /**
     * Check if bit is set
     *
     * \param bit Bit to check
     * \return True if bit is set, false otherwise
     */
    auto _is_set(size_t bit) const -> bool { return 0 != (value & masks[bit]); }
};

} // namespace snippets
