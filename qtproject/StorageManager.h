#ifndef STORAGEMANAGER_H
#define STORAGEMANAGER_H
#include <iostream>
#include <unordered_map>
#include <map>
#include <memory>
#include <stdexcept>
#include <QObject>

class DuplicateItemException : public std::runtime_error {
public:
    DuplicateItemException(const std::string& msg);
};

class ItemNotFoundException : public std::runtime_error {
public:
    ItemNotFoundException(const std::string& msg);
};

class StoredItem {
private:
    std::string id;
    std::string description;
    std::string location;

public:
    StoredItem(std::string id, std::string desc, std::string loc)
        : id(id), description(desc), location(loc) {}

    std::string getId() const { return id; }
    std::string getDescription() const { return description; }
    std::string getLocation() const { return location; }
};

class StorageManager: public QObject {
    Q_OBJECT
private:
    std::unordered_map<std::string, std::shared_ptr<StoredItem>> itemById;
    std::map<std::string, std::shared_ptr<StoredItem>> itemByDescription;

public:
    StorageManager();
    ~StorageManager();
    void addItem(const std::shared_ptr<StoredItem>& item);

    std::shared_ptr<StoredItem> findById(const std::string& id) const;

    void removeItem(const std::string& id);

    void listItemsByDescription() const;
};

void testDuplicateAddition(StorageManager manager);
void testItemNotFound(StorageManager manager);
#endif // STORAGEMANAGER_H
