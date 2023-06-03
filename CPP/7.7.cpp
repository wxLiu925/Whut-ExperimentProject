#include <iostream>
#include <string>

class Document {
protected:
    std::string name;
    
public:
    Document(const std::string& docName) : name(docName) {}
    
    void setName(const std::string& newName) {
        name = newName;
    }
    std::string getName() const {
        return name;
    }
};

class Book : public Document {
private:
    int pageCount;
    
public:
    Book(const std::string& bookName, int pageCount) : Document(bookName), pageCount(pageCount) {}
    
    void setPageCount(int newPageCount) {
        pageCount = newPageCount;
    }
    int getPageCount() const {
        return pageCount;
    }
};

int main() {
    // 创建一个Document对象并设置名称
    Document doc("My Document");
    std::cout << "Document name: " << doc.getName() << std::endl;
    
    // 创建一个Book对象并设置名称和页数
    Book book("My Book", 100);
    std::cout << "Book name: " << book.getName() << std::endl;
    std::cout << "Page count: " << book.getPageCount() << std::endl;
    
    // 修改Book对象的名称和页数
    book.setName("New Book");
    book.setPageCount(200);
    std::cout << "Modified book name: " << book.getName() << std::endl;
    std::cout << "Modified page count: " << book.getPageCount() << std::endl;
    
    return 0;
}