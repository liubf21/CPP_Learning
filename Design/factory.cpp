#include <iostream>
#include <map>
#include <string>

class Shoes
{
public:
    virtual void Show() = 0;
    virtual ~Shoes() {}
};

class NikeShoes: public Shoes
{
public:
    void Show()
    {
        std::cout << "Just do it" << std::endl;
    }
};

class Clothe
{
public:
    virtual void Show() = 0;
    virtual ~Clothe() {}
};

class UniqloClothe: public Clothe
{
public:
    void Show()
    {
        std::cout << "Uniqlo" << std::endl;
    }
};

template <class ProductType_t>
class IProductRegistrar
{
public:
    virtual ProductType_t* CreateProduct() = 0;

protected:
    // prohibit to create instance or destroy instance from outside
    IProductRegistrar() {}
    virtual ~IProductRegistrar() {}

private:
    // prohibit to copy instance or assign instance from outside
    IProductRegistrar(const IProductRegistrar&);
    const IProductRegistrar& operator=(const IProductRegistrar&);
};

template <class ProductType_t>
class ProductFactory
{
public:
    // use singleton pattern to get instance
    static ProductFactory<ProductType_t>& Instance()
    {
        static ProductFactory<ProductType_t> instance;
        return instance;
    }

    void RegisterProduct(IProductRegistrar<ProductType_t>* pRegistrar, const std::string& strProductName)
    {
        m_ProductRegistry[strProductName] = pRegistrar;
    }

    ProductType_t* CreateProduct(const std::string& strProductName)
    {
        if (m_ProductRegistry.find(strProductName) != m_ProductRegistry.end())
        {
            return m_ProductRegistry[strProductName]->CreateProduct();
        }
        std::cout << "Product " << strProductName << " not found" << std::endl;
        return nullptr;
    }

private:
    // prohibit to create instance or destroy instance from outside
    ProductFactory() {}
    ~ProductFactory() {}

    // prohibit to copy instance or assign instance from outside
    ProductFactory(const ProductFactory&);
    const ProductFactory& operator=(const ProductFactory&);

    // use map to store product name and product registrar
    std::map<std::string, IProductRegistrar<ProductType_t>*> m_ProductRegistry;
};

template <class ProductType_t, class ProductImpl_t>
class ProductRegistrar : public IProductRegistrar<ProductType_t>
{
public:
    explicit ProductRegistrar(const std::string& strProductName)
    {
        ProductFactory<ProductType_t>::Instance().RegisterProduct(this, strProductName);
    }

    ProductType_t* CreateProduct()
    {
        return new ProductImpl_t();
    }
};

int main()
{
    ProductRegistrar<Shoes, NikeShoes> nikeShoes("Nike");
    Shoes *pNikeShoes = ProductFactory<Shoes>::Instance().CreateProduct("Nike");
    pNikeShoes->Show();
    if (pNikeShoes)
    {
        delete pNikeShoes;
        pNikeShoes = nullptr;
    }

    ProductRegistrar<Clothe, UniqloClothe> uniqloClothe("Uniqlo");
    Clothe *pUniqloClothe = ProductFactory<Clothe>::Instance().CreateProduct("Uniqlo");
    pUniqloClothe->Show();
    if (pUniqloClothe)
    {
        delete pUniqloClothe;
        pUniqloClothe = nullptr;
    }

    return 0;
}