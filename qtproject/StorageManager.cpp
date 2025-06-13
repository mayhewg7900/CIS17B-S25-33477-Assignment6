#include "StorageManager.h"


DuplicateItemException::DuplicateItemException(const std::string& msg) : std::runtime_error(msg) {}

ItemNotFoundException::ItemNotFoundException(const std::string& msg) : std::runtime_error(msg) {}

std::shared_ptr<StoredItem> StorageManager::findById(const std::string& id) const {
    // TODO: Return item if found or throw ItemNotFoundException
    auto foundId = itemById.find(id);
    try {
        if (foundId != itemById.end()) {
            return foundId->second;
        }
        else {
            throw ItemNotFoundException("Item not found, cannot be removed");
        }
    }
    catch(ItemNotFoundException& e) {
        std::cout << "Error: " << e.what() << std::endl;
        return nullptr;
    }
}

void StorageManager::addItem(const std::shared_ptr<StoredItem>& item) {
    // TODO: Add item to both maps, throw if ID already exists
    try {
        for (const auto& map_item : itemById) {
            if (map_item.first == item->getId()) {
                throw DuplicateItemException("Error, duplicate items");
            }
        }
        itemById.insert({ item->getId(), item });
        itemByDescription.insert({ item->getDescription(), item });
    }
    catch (DuplicateItemException &e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void StorageManager::removeItem(const std::string& id) {
    // TODO: Remove from both maps, throw if not found
    auto foundId = itemById.find(id);
    try {
        if (foundId == itemById.end()) {
            throw ItemNotFoundException("Item not found, cannot be removed");
        }
        std::shared_ptr<StoredItem> item = foundId->second;
        itemById.erase(foundId);
        for (auto& map_item : itemByDescription) {
            if (item == map_item.second) {
                itemByDescription.erase(map_item.first);
                break;
            }
        }
    }
    catch (ItemNotFoundException& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void StorageManager::listItemsByDescription() const {
    // TODO: Iterate over itemByDescription and print info
    std::cout << "List of items in description order:" << std::endl;
    for (const auto& map_item : itemByDescription) {
        std::cout << map_item.first << " at " << map_item.second->getLocation() << std::endl;
    }
}

StorageManager::StorageManager() {}
StorageManager::~StorageManager() {}
