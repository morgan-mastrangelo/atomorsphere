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
#include <vapours.hpp>
#include <stratosphere/fssrv/fssrv_i_file_system_creator.hpp>

namespace ams::fssrv::fscreator {

    /* ACCURATE_TO_VERSION: 13.4.0.0 */
    class LocalFileSystemCreator final : public ILocalFileSystemCreator {
        NON_COPYABLE(LocalFileSystemCreator);
        NON_MOVEABLE(LocalFileSystemCreator);
        private:
            bool m_is_development;
        public:
            explicit LocalFileSystemCreator(bool dev) : m_is_development(dev) { /* ... */ }

            virtual Result Create(std::shared_ptr<fs::fsa::IFileSystem> *out, const fs::Path &path, bool case_sensitive, bool ensure_root, Result on_path_not_found) override;
    };

}
