// Copyright 2020 The Open GEE Contributors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef COMMON_FILEACCESSORPLUGINLOADER_H_
#define COMMON_FILEACCESSORPLUGINLOADER_H_

#include <string>
#include <vector>
#include <dlfcn.h>
#include <mutex>
#include <boost/filesystem.hpp>
#include "FileAccessor.h"

class FileAccessorFactory {
friend class FileAccessorPluginLoader;
protected:
    virtual AbstractFileAccessor* GetAccessor(const std::string &fileName) = 0;
};

typedef FileAccessorFactory* (*get_factory_t)();

class FileAccessorPluginLoader {
public:
    using PluginHandle = void*;
    using PluginFactory = std::pair<PluginHandle,FileAccessorFactory*>;
    using LoadPluginFunc = std::function<void(std::vector<PluginFactory> &)>;
    using UnloadPluginFunc = std::function<void(PluginHandle)>;

    ~FileAccessorPluginLoader();
    void LoadPlugins();
    std::unique_ptr<AbstractFileAccessor> GetAccessor(std::string file_path);

    static void DefaultLoadPluginsImpl (std::vector<PluginFactory> &factories);
    static FileAccessorPluginLoader& Get();

protected:
    FileAccessorPluginLoader(LoadPluginFunc LoadImpl = nullptr, UnloadPluginFunc UnloadImpl = nullptr);

private:
    bool loaded = false;
    std::vector<PluginFactory> factories;
    std::mutex loadMutex;
    LoadPluginFunc loadPluginFunc;
    UnloadPluginFunc unloadPluginFunc;
};

#endif // COMMON_FILEACCESSORPLUGINLOADER_H_