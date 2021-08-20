/*
 *
 * Tencent is pleased to support the open source community by making
 * Hippy available.
 *
 * Copyright (C) 2019 THL A29 Limited, a Tencent company.
 * All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#pragma once

#include <android/asset_manager.h>

#include <map>

#include "core/core.h"
#include "jni/scoped_java_ref.h"

class ADRLoader : public hippy::base::UriLoader {
 public:
  using unicode_string_view = tdf::base::unicode_string_view;
  ADRLoader();
  virtual ~ADRLoader() {}

  inline void SetBridge(std::shared_ptr<JavaRef> bridge) { bridge_ = bridge; }
  virtual unicode_string_view GetScheme(const unicode_string_view& uri);
  virtual void GetContent(const unicode_string_view& uri,
                          std::function<void(RetCode, bytes)> cb);
  virtual RetCode GetContent(
      const unicode_string_view& uri,
      bytes& content);

  std::function<void(RetCode, bytes)> GetRequestCB(int64_t request_id);
  int64_t SetRequestCB(std::function<void(UriLoader::RetCode, UriLoader::bytes)> cb);

 private:
  bool LoadByJNI(const unicode_string_view& uri,
                  std::function<void(RetCode, bytes)> cb);

  std::shared_ptr<JavaRef> bridge_;
  std::unordered_map<int64_t, std::function<void(UriLoader::RetCode, UriLoader::bytes)>>
      request_map_;
};
