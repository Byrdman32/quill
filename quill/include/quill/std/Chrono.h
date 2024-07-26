/**
 * Copyright(c) 2020-present, Odysseas Georgoudis & quill contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 */

#pragma once

#include "quill/core/Codec.h"
#include "quill/core/DynamicFormatArgStore.h"

#include "quill/bundled/fmt/chrono.h"
#include "quill/bundled/fmt/format.h"

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <vector>

namespace quill
{
/***/
template <typename Clock, typename Duration>
struct ArgSizeCalculator<std::chrono::time_point<Clock, Duration>>
{
  static size_t calculate(std::vector<size_t>&, std::chrono::time_point<Clock, Duration> const& arg) noexcept
  {
    return sizeof(arg);
  }
};

/***/
template <typename Clock, typename Duration>
struct Encoder<std::chrono::time_point<Clock, Duration>>
{
  static void encode(std::byte*& buffer, std::vector<size_t> const&, uint32_t&,
                     std::chrono::time_point<Clock, Duration> arg) noexcept
  {
    std::memcpy(buffer, &arg, sizeof(arg));
    buffer += sizeof(arg);
  }
};

/***/
template <typename Clock, typename Duration>
struct Decoder<std::chrono::time_point<Clock, Duration>>
{
  static std::chrono::time_point<Clock, Duration> decode_arg(std::byte*& buffer)
  {
    std::chrono::time_point<Clock, Duration> arg;
    std::memcpy(&arg, buffer, sizeof(arg));
    buffer += sizeof(arg);
    return arg;
  }

  static void decode_and_store_arg(std::byte*& buffer, DynamicFormatArgStore* args_store)
  {
    args_store->push_back(decode_arg(buffer));
  }
};

/***/
template <typename Rep, typename Period>
struct ArgSizeCalculator<std::chrono::duration<Rep, Period>>
{
  static size_t calculate(std::vector<size_t>&, std::chrono::duration<Rep, Period> const& arg) noexcept
  {
    return sizeof(arg);
  }
};

/***/
template <typename Rep, typename Period>
struct Encoder<std::chrono::duration<Rep, Period>>
{
  static void encode(std::byte*& buffer, std::vector<size_t> const&, uint32_t&,
                     std::chrono::duration<Rep, Period> arg) noexcept
  {
    std::memcpy(buffer, &arg, sizeof(arg));
    buffer += sizeof(arg);
  }
};

/***/
template <typename Rep, typename Period>
struct Decoder<std::chrono::duration<Rep, Period>>
{
  static std::chrono::duration<Rep, Period> decode_arg(std::byte*& buffer)
  {
    std::chrono::duration<Rep, Period> arg;
    std::memcpy(&arg, buffer, sizeof(arg));
    buffer += sizeof(arg);
    return arg;
  }

  static void decode_and_store_arg(std::byte*& buffer, DynamicFormatArgStore* args_store)
  {
    args_store->push_back(decode_arg(buffer));
  }
};
} // namespace quill