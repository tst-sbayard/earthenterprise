#ifndef ASSET_SERIALIZER_H
#define ASSET_SERIALIZER_H

#include "common/khxml/khxml.h"
#include "common/khxml/khdom.h"

using namespace khxml;

template<class AssetType>
class AssetSerializerLocalXML
{
  public:
    AssetSerializerLocalXML() {}
    std::shared_ptr<AssetType> Load(const std::string &boundref)
    {
      return AssetType::Load(boundref);
    }

    bool Save(std::shared_ptr<AssetType> asset, std::string filename){
      using AssetStorageType = typename AssetType::Base;
      extern void ToElement(DOMElement *elem, const AssetStorageType &self);

      std::unique_ptr<GEDocument> doc = CreateEmptyDocument(asset->GetName());
      if (!doc) {
          notify(NFY_WARN,
                "Unable to create empty document: ${name}AssetVersion");
          return false;
      }
      bool status = false;
      try {
          DOMElement *top = doc->getDocumentElement();
          if (top) {
              const AssetStorageType &storage = *asset;
              ToElement(top, storage);
              asset->SerializeConfig(top);
              status = WriteDocument(doc.get(), filename);

              if (!status && khExists(filename)) {
                  khUnlink(filename);
              }
          } else {
              notify(NFY_WARN, "Unable to create document element %s",
                    filename.c_str());
          }
      } catch (const std::exception &e) {
          notify(NFY_WARN, "%s while saving %s", e.what(), filename.c_str());
      } catch (...) {
          notify(NFY_WARN, "Unable to save %s", filename.c_str());
      }
      return status;
    }
};


#endif //ASSET_SERIALIZER_H