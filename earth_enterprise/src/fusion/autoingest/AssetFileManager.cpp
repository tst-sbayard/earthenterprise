/*
 * Copyright 2019 The Open GEE Contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

template<class AssetType>
khRefGuard<AssetType> LoadAssetVersionResource(const std::string &boundref){
 return AssetVersionImpl::Load(boundref);
}

template<class AssetType>
khRefGuard<AssetType> LoadAssetResource(const std::string &boundref) {
  return AssetImpl::Load(boundref);
}
