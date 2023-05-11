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
#include <stratosphere/sf.hpp>
#include <stratosphere/ncm/ncm_content_meta.hpp>

#define AMS_NCM_I_CONTENT_META_DATABASE_INTERFACE_INFO(C, H)                                                                                                                                                                                                                                                                                                                                                                                            \
    AMS_SF_METHOD_INFO(C, H,  0, Result, Set,                             (const ncm::ContentMetaKey &key, const sf::InBuffer &value),                                                                                                                                                                                      (key, value))                                                                                                               \
    AMS_SF_METHOD_INFO(C, H,  1, Result, Get,                             (sf::Out<u64> out_size, const ncm::ContentMetaKey &key, const sf::OutBuffer &out_value),                                                                                                                                                          (out_size, key, out_value))                                                                                                 \
    AMS_SF_METHOD_INFO(C, H,  2, Result, Remove,                          (const ncm::ContentMetaKey &key),                                                                                                                                                                                                                 (key))                                                                                                                      \
    AMS_SF_METHOD_INFO(C, H,  3, Result, GetContentIdByType,              (sf::Out<ncm::ContentId> out_content_id, const ncm::ContentMetaKey &key, ncm::ContentType type),                                                                                                                                                  (out_content_id, key, type))                                                                                                \
    AMS_SF_METHOD_INFO(C, H,  4, Result, ListContentInfo,                 (sf::Out<s32> out_entries_written, const sf::OutArray<ncm::ContentInfo> &out_info, const ncm::ContentMetaKey &key, s32 offset),                                                                                                                   (out_entries_written, out_info, key, offset))                                                                               \
    AMS_SF_METHOD_INFO(C, H,  5, Result, List,                            (sf::Out<s32> out_entries_total, sf::Out<s32> out_entries_written, const sf::OutArray<ncm::ContentMetaKey> &out_info, ncm::ContentMetaType meta_type, ncm::ApplicationId application_id, u64 min, u64 max, ncm::ContentInstallType install_type), (out_entries_total, out_entries_written, out_info, meta_type, application_id, min, max, install_type))                      \
    AMS_SF_METHOD_INFO(C, H,  6, Result, GetLatestContentMetaKey,         (sf::Out<ncm::ContentMetaKey> out_key, u64 id),                                                                                                                                                                                                   (out_key, id))                                                                                                              \
    AMS_SF_METHOD_INFO(C, H,  7, Result, ListApplication,                 (sf::Out<s32> out_entries_total, sf::Out<s32> out_entries_written, const sf::OutArray<ncm::ApplicationContentMetaKey> &out_keys, ncm::ContentMetaType meta_type),                                                                                 (out_entries_total, out_entries_written, out_keys, meta_type))                                                              \
    AMS_SF_METHOD_INFO(C, H,  8, Result, Has,                             (sf::Out<bool> out, const ncm::ContentMetaKey &key),                                                                                                                                                                                              (out, key))                                                                                                                 \
    AMS_SF_METHOD_INFO(C, H,  9, Result, HasAll,                          (sf::Out<bool> out, const sf::InArray<ncm::ContentMetaKey> &keys),                                                                                                                                                                                (out, keys))                                                                                                                \
    AMS_SF_METHOD_INFO(C, H, 10, Result, GetSize,                         (sf::Out<u64> out_size, const ncm::ContentMetaKey &key),                                                                                                                                                                                          (out_size, key))                                                                                                            \
    AMS_SF_METHOD_INFO(C, H, 11, Result, GetRequiredSystemVersion,        (sf::Out<u32> out_version, const ncm::ContentMetaKey &key),                                                                                                                                                                                       (out_version, key))                                                                                                         \
    AMS_SF_METHOD_INFO(C, H, 12, Result, GetPatchContentMetaId,           (sf::Out<u64> out_patch_id, const ncm::ContentMetaKey &key),                                                                                                                                                                                      (out_patch_id, key))                                                                                                        \
    AMS_SF_METHOD_INFO(C, H, 13, Result, DisableForcibly,                 (),                                                                                                                                                                                                                                               ())                                                                                                                         \
    AMS_SF_METHOD_INFO(C, H, 14, Result, LookupOrphanContent,             (const sf::OutArray<bool> &out_orphaned, const sf::InArray<ncm::ContentId> &content_ids),                                                                                                                                                         (out_orphaned, content_ids))                                                                                                \
    AMS_SF_METHOD_INFO(C, H, 15, Result, Commit,                          (),                                                                                                                                                                                                                                               ())                                                                                                                         \
    AMS_SF_METHOD_INFO(C, H, 16, Result, HasContent,                      (sf::Out<bool> out, const ncm::ContentMetaKey &key, const ncm::ContentId &content_id),                                                                                                                                                            (out, key, content_id))                                                                                                     \
    AMS_SF_METHOD_INFO(C, H, 17, Result, ListContentMetaInfo,             (sf::Out<s32> out_entries_written, const sf::OutArray<ncm::ContentMetaInfo> &out_meta_info, const ncm::ContentMetaKey &key, s32 offset),                                                                                                          (out_entries_written, out_meta_info, key, offset))                                                                          \
    AMS_SF_METHOD_INFO(C, H, 18, Result, GetAttributes,                   (sf::Out<u8> out_attributes, const ncm::ContentMetaKey &key),                                                                                                                                                                                     (out_attributes, key))                                                                                                      \
    AMS_SF_METHOD_INFO(C, H, 19, Result, GetRequiredApplicationVersion,   (sf::Out<u32> out_version, const ncm::ContentMetaKey &key),                                                                                                                                                                                       (out_version, key),                                                                                    hos::Version_2_0_0)  \
    AMS_SF_METHOD_INFO(C, H, 20, Result, GetContentIdByTypeAndIdOffset,   (sf::Out<ncm::ContentId> out_content_id, const ncm::ContentMetaKey &key, ncm::ContentType type, u8 id_offset),                                                                                                                                    (out_content_id, key, type, id_offset),                                                                hos::Version_5_0_0)  \
    AMS_SF_METHOD_INFO(C, H, 21, Result, GetCount,                        (sf::Out<u32> out_count),                                                                                                                                                                                                                         (out_count),                                                                                           hos::Version_10_0_0) \
    AMS_SF_METHOD_INFO(C, H, 22, Result, GetOwnerApplicationId,           (sf::Out<ncm::ApplicationId> out_id, const ncm::ContentMetaKey &key),                                                                                                                                                                             (out_id, key),                                                                                         hos::Version_10_0_0) \
    AMS_SF_METHOD_INFO(C, H, 23, Result, GetContentAccessibilities,       (sf::Out<u8> out_accessibilities, const ncm::ContentMetaKey &key),                                                                                                                                                                                (out_accessibilities, key),                                                                            hos::Version_15_0_0) \
    AMS_SF_METHOD_INFO(C, H, 24, Result, GetContentInfoByType,            (sf::Out<ncm::ContentInfo> out_content_info, const ncm::ContentMetaKey &key, ncm::ContentType type),                                                                                                                                              (out_content_info, key, type),                                                                         hos::Version_15_0_0) \
    AMS_SF_METHOD_INFO(C, H, 25, Result, GetContentInfoByTypeAndIdOffset, (sf::Out<ncm::ContentInfo> out_content_info, const ncm::ContentMetaKey &key, ncm::ContentType type, u8 id_offset),                                                                                                                                (out_content_info, key, type, id_offset),                                                              hos::Version_15_0_0)


AMS_SF_DEFINE_INTERFACE(ams::ncm, IContentMetaDatabase, AMS_NCM_I_CONTENT_META_DATABASE_INTERFACE_INFO, 0x58021FEC)
