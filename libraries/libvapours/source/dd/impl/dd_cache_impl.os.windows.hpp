/*
 * Copyright (c) Atmosphère-NX
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once
#if defined(ATMOSPHERE_IS_STRATOSPHERE)
#include <stratosphere.hpp>
#else
#include <vapours.hpp>
#endif

namespace ams::dd::impl {

    void StoreDataCacheImpl(void *addr, size_t size) {
        #if defined(ATMOSPHERE_ARCH_X64) || defined(ATMOSPHERE_ARCH_X86)
            /* Don't do anything, cache maintenance isn't available/relevant to userland. */
            AMS_UNUSED(addr, size);
        #else
            #error "Unknown architecture for windows dd::StoreDataCacheImpl"
        #endif
    }

    void FlushDataCacheImpl(void *addr, size_t size) {
        #if defined(ATMOSPHERE_ARCH_X64) || defined(ATMOSPHERE_ARCH_X86)
            /* Don't do anything, cache maintenance isn't available/relevant to userland. */
            AMS_UNUSED(addr, size);
        #else
            #error "Unknown architecture for windows dd::FlushDataCacheImpl"
        #endif
    }

    void InvalidateDataCacheImpl(void *addr, size_t size) {
        #if defined(ATMOSPHERE_ARCH_X64) || defined(ATMOSPHERE_ARCH_X86)
            /* Don't do anything, cache maintenance isn't available/relevant to userland. */
            AMS_UNUSED(addr, size);
        #else
            #error "Unknown architecture for windows dd::InvalidateDataCacheImpl"
        #endif
    }

}
